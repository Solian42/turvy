#include "../include/main.h"

// This is a bad idea for later.
int numEntities = 6;
World *mainWorld = new World(numEntities);
int width = mainWorld->x;
int height = mainWorld->y;
Mix_Music *backgroundMusic;
SDL_Window *mainWindow;
SDL_Renderer *mainRenderer;

int center(int large, int small) { return large / 2 - small / 2; }

void setup(const char *title) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "oops. Failed to init: " << SDL_GetError() << "\n";
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error:"
                  << Mix_GetError() << "\n";
    }

    mainWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, width, height,
                                  SDL_WINDOW_SHOWN);
    if (mainWindow == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mainRenderer == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    return;
}

void load() {

    backgroundMusic = Mix_LoadMUS("../data/sounds/abstract_tracking.xm");
    if (backgroundMusic == NULL) {
        std::cerr << "SDL_mixer Error:" << Mix_GetError() << "\n";
    }

    return;
}

PlayerObject *createPlayer(int entityNum) {
    PlayerInputComponent *i = new PlayerInputComponent();
    PlayerGraphicsComponent *g = new PlayerGraphicsComponent(
        std::string("../data/images/player_sprite.png"), mainRenderer);
    PlayerPhysicsComponent *p = new PlayerPhysicsComponent();
    std::vector<std::string> chunks = {std::string("../data/sounds/bonk.ogg")};
    PlayerSoundComponent *s = new PlayerSoundComponent(chunks);
    PlayerObject *player = new PlayerObject((width / 2), (height / 2), 0, 0, i,
                                            g, s, p, entityNum);
    return player;
}

EnemyObject *createEnemy(int x, int y, int entityNum) {
    EnemyInputComponent *i = new EnemyInputComponent();
    EnemyGraphicsComponent *g = new EnemyGraphicsComponent(
        std::string("../data/images/evil_sprite.png"), mainRenderer);
    EnemyPhysicsComponent *p = new EnemyPhysicsComponent();

    EnemyObject *e = new EnemyObject(x, y, 0, 0, i, g, p, entityNum);

    return e;
}

void run(std::vector<GameObject *> *entitiesPtr) {

    std::vector<GameObject *> entities = *entitiesPtr;
    // Separate out the player
    PlayerObject *player = (PlayerObject *)entities[0];

    // grab the enemies
    std::vector<EnemyObject *> enemies = std::vector<EnemyObject *>(5);

    for (int i = 0; i < 5; i++) {
        enemies[i] = (EnemyObject *)entities[i + 1];
        enemies[i]->input->update(enemies[i]);
    }

    Mix_PlayMusic(backgroundMusic, -1);
    SDL_Event e;
    bool running = true;
    unsigned int lastTime = 0;
    unsigned int currentTime;

    unsigned int dt = 0;
    lastTime = SDL_GetTicks();

    while (running) {
        currentTime = SDL_GetTicks();
        dt += currentTime - lastTime;
        lastTime = currentTime;
        // Input stage
        while (dt > 16) {
            dt -= 16;
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if ((e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ||
                    e.type == SDL_QUIT) {
                    running = false;
                }

                // Handle input for the player
                player->input->update(player, &e);
            }
            // Physics stage
            player->physics->update(player, mainWorld);
            for (int i = 0; i < 5; i++) {
                enemies[i]->physics->update(enemies[i], mainWorld);
            }
            mainWorld->collision = mainWorld->checkCollisions();
            // sounds!
            player->sound->update(mainWorld);

            SDL_RenderClear(mainRenderer);
            for (int i = 0; i < 5; i++) {
                enemies[i]->graphics->update(enemies[i], mainRenderer,
                                             mainWorld);
            }
            player->graphics->update(player, mainRenderer, mainWorld);
            SDL_RenderPresent(mainRenderer);
        }
    }

    return;
}

void cleanup() {
    Mix_FreeMusic(backgroundMusic);
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    Mix_Quit();
    SDL_Quit();
}

int main() {
    setup("Lizard Games Assignment 1");
    load();

    std::vector<GameObject *> entities(6);
    entities[0] = createPlayer(0);
    for (int i = 1; i < 6; i++) {
        entities[i] =
            createEnemy((std::rand() % width), (std::rand() % height), i);
    }

    run(&entities);

    cleanup();
    return 0;
}
