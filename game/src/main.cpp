#include "../include/main.h"
const int width = 1280;
const int height = 720;
SDL_Window *mainWindow;
SDL_Renderer *mainRenderer;
ResourceManager *resources;

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

    TTF_Init();

    return;
}

void load() {
    resources = new ResourceManager(mainRenderer);

    return;
}

void run() {

    std::vector<State *> states = std::vector<State *>(4);
    states[STATE_GAME] = new GameState(mainRenderer, width, height, resources);
    states[STATE_TITLE] =
        new TitleState(mainRenderer, width, height, resources);
    State *currState = states[STATE_TITLE];
    currState->startMusic();
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
            int stateChange = currState->handleEvent(&e, dt);
            if (stateChange != currState->STATETYPE) {
                switch (stateChange) {
                case STATE_GAME:
                    currState = states[STATE_GAME];
                    break;
                case STATE_MAINMENU:
                    currState = states[STATE_MAINMENU];
                    break;
                case STATE_HIGHSCORE:
                    currState = states[STATE_HIGHSCORE];
                default:
                    break;
                }
                continue;
            }
        }
        // Physics stage
        currState->doPhysics(dt);
        // sounds!
        currState->doSound();
        // draw stuffff!
        SDL_RenderClear(mainRenderer);
        currState->render(dt);
        SDL_RenderPresent(mainRenderer);
    }
    for (State *s : states) {
        delete s;
    }

    return;
}

void cleanup() {
    delete resources;
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    Mix_Quit();
    SDL_Quit();
}

int main() {
    setup("Lizard Games Assignment 1");

    load();

    run();

    cleanup();
    return 0;
}
