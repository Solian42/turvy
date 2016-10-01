#include "../include/main.h"

// This is a bad idea for later.
int numEntities = 10;
World *mainWorld = new World(numEntities);
int width = mainWorld->x;
int height = mainWorld->y;
SDL_Window *mainWindow;
SDL_Renderer *mainRenderer;
ResourceManager *resources;

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
    resources = new ResourceManager(mainRenderer);

    return;
}

PlayerObject *createPlayer(int entityNum,
                           std::vector<std::string> spriteNames) {
    PlayerInputComponent *i = new PlayerInputComponent();
    PlayerGraphicsComponent *g =
        new PlayerGraphicsComponent(mainRenderer, resources, spriteNames);
    PlayerPhysicsComponent *p = new PlayerPhysicsComponent();
    std::vector<std::string> chunks = {std::string("bonk")};
    PlayerSoundComponent *s = new PlayerSoundComponent(chunks, resources);
    PlayerObject *player = new PlayerObject((width / 2), (height / 2), 0, 0, i,
                                            g, s, p, entityNum);
    return player;
}

EnemyObject *createEnemy(int x, int y, int entityNum,
                         std::vector<std::string> spriteNames) {
    EnemyInputComponent *i = new EnemyInputComponent();
    EnemyGraphicsComponent *g =
        new EnemyGraphicsComponent(mainRenderer, resources, spriteNames);
    EnemyPhysicsComponent *p = new EnemyPhysicsComponent();
    EnemyObject *e = new EnemyObject(x, y, 0, 0, i, g, p, entityNum);
    return e;
}

void run(std::vector<GameObject *> *entitiesPtr, std::string music) {

    std::vector<GameObject *> entities = *entitiesPtr;
    // Separate out the player
    PlayerObject *player = (PlayerObject *)entities[0];

    // grab the enemies
    std::vector<EnemyObject *> enemies = std::vector<EnemyObject *>(10);

    for (int i = 0; i < 9; i++) {
        enemies[i] = (EnemyObject *)entities[i + 1];
        enemies[i]->input->update(enemies[i]);
    }

    Mix_PlayMusic(resources->getMusic(music), -1);
    SDL_Event e;
    bool running = true;
    unsigned int lastTime = 0;
    unsigned int currentTime;

    unsigned int dt = 0;
    lastTime = SDL_GetTicks();

    while (running) {
        currentTime = SDL_GetTicks();
        dt = currentTime - lastTime;
        lastTime = currentTime;
        // Input stage
        // while (dt > 16) {
        // dt -= 16;
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if ((e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ||
                e.type == SDL_QUIT) {
                running = false;
            }

            // Handle input for the player
            player->input->update(player, &e, dt);
        }
        // Physics stage
        player->physics->update(player, mainWorld, dt);
        for (int i = 0; i < 9; i++) {
            enemies[i]->physics->update(enemies[i], mainWorld, dt);
        }
        mainWorld->collision = mainWorld->checkCollisions();
        // sounds!
        player->sound->update(mainWorld);

        // draw stuffff!
        SDL_RenderClear(mainRenderer);
        for (int i = 0; i < 9; i++) {
            enemies[i]->graphics->GraphicsComponent::update(mainRenderer,
                                                            mainWorld);
        }
        player->graphics->GraphicsComponent::update(mainRenderer, mainWorld);
        SDL_RenderPresent(mainRenderer);
    }

    return;
}

void cleanup(std::vector<GameObject *> entities) {
    delete resources;
    for (GameObject *g : entities) {
        delete g;
    }
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    Mix_Quit();
    SDL_Quit();
}

int main() {
    setup("Lizard Games Assignment 1");
    load();

    std::vector<GameObject *> entities(10);
    entities[0] = createPlayer(0, {std::string("defaultPlayerSprite")});
    for (int i = 1; i < 10; i++) {
        int randX = std::rand() % width;
        int randY = std::rand() % height;
        entities[i] =
            createEnemy(randX, randY, i, {std::string("defaultEnemySprite")});
    }

    run(&entities, std::string("abstract_tracking"));

    cleanup(entities);
    return 0;
}
