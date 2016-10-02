#include "../include/main.h"

int main() {
    setup("Lizard Games Assignment 1");
    
    load();
    
    run();
    
    cleanup();
    
    return 0;
}


void run() {

    std::vector<State *> states = std::vector<State *>(4);
    states[STATE_GAME] = new GameState(mainRenderer, width, height, resources);
    states[STATE_TITLE] =
        new TitleState(mainRenderer, width, height, resources);
    State *currState = states[STATE_TITLE];
    int currStateType = STATE_TITLE;
    currState->startMusic();
    SDL_Event e;
    bool running = true;
    unsigned int lastTime = 0;
    unsigned int currentTime;
    unsigned int dt = 0;
    lastTime = SDL_GetTicks();

    bool changeState = false;
    bool renderFPS = false;
    std::chrono::high_resolution_clock nano =
        std::chrono::high_resolution_clock();
    std::chrono::duration<double> dtNano;
    std::chrono::high_resolution_clock::time_point ctp = nano.now();
    std::chrono::high_resolution_clock::time_point ltp = nano.now();

    while (running) {
        changeState = false;
        currentTime = SDL_GetTicks();
        ctp = nano.now();
        dtNano = std::chrono::duration_cast<std::chrono::duration<double>>(ltp -
                                                                           ctp);
        dt = currentTime - lastTime;
        ltp = ctp;
        lastTime = currentTime;
        // Input stage
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if ((e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE) ||
                e.type == SDL_QUIT) {
                running = false;
            }
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f) {
                renderFPS = !renderFPS;
            }
            // Handle input for the player
            int stateChange = currState->handleEvent(&e, dt);
            if (stateChange != currStateType) {
                std::cout << stateChange << " " << currStateType << "\n";
                switch (stateChange) {
                case STATE_GAME:
                    currState = states[STATE_GAME];
                    currStateType = STATE_GAME;
                    currState->startMusic();
                    break;
                case STATE_MAINMENU:
                    currState = states[STATE_MAINMENU];
                    currStateType = STATE_MAINMENU;
                    currState->startMusic();
                    break;
                case STATE_HIGHSCORE:
                    currState = states[STATE_HIGHSCORE];
                    currStateType = STATE_HIGHSCORE;
                    currState->startMusic();
                    break;
                default:
                    break;
                }
                changeState = true;
            }
        }
        if (changeState)
            continue;
        // Physics stage
        currState->doPhysics(dt);
        // sounds!
        currState->doSound();
        // draw stuffff!
                SDL_RenderClear(mainRenderer);

        currState->render(dt);
        if(renderFPS) printFPS(dtNano);
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


void setup(const char *title) {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "oops. Failed to init: " << SDL_GetError() << "\n";
    }
    
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error:"
        << Mix_GetError() << "\n";
    }
    Mix_Volume(-1, 64);
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

void printFPS(std::chrono::duration<double> dtNano) {
    double framerate = -1.0 / dtNano.count();
    std::ostringstream strs;
    strs << framerate;
    std::string str = strs.str();
    SDL_Color white = {255, 255, 255, 255};
    SDL_Texture *fps = resources->getFont(
                                          std::string("manaspc30"), std::string("FPS = ") + str, white);
    int w, h;
    SDL_QueryTexture(fps, NULL, NULL, &w, &h);
    SDL_Rect temp = {0, 0, w, h};
    SDL_RenderCopy(mainRenderer, fps, NULL, &temp);
}



void load() {
    resources = new ResourceManager(mainRenderer);
    
    return;
}
