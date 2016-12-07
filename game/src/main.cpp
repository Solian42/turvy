#include "../include/main.h"

int main() {
    setup("Turvy");

    load();

    run();

    cleanup();

    return 0;
}

void run() {

    std::vector<State *> states = std::vector<State *>(10);
    states[STATE_GAME] =
        new GameState(mainRenderer, width, height, resources,
                      {{"level1", "level2", "level3", "level4", "level_editor"},
                       {"level1", "level2", "level3", "level4", "level_editor"},
                       {"background1", "background2", "background3",
                        "background4", "background1"}},
                      5);
    states[STATE_TITLE] =
        new TitleState(mainRenderer, width, height, resources);
    states[STATE_MAINMENU] =
        new MainMenuState(mainRenderer, width, height, resources);
    states[STATE_LEVELONEBEGIN] =
        new LevelOneBeginState(mainRenderer, width, height, resources);
    states[STATE_LEVELONEINSTRUCT] =
        new LevelOneInstructState(mainRenderer, width, height, resources);
    states[STATE_LEVELTWOBEGIN] =
        new LevelTwoBeginState(mainRenderer, width, height, resources);
    states[STATE_LEVELTHREEBEGIN] =
        new LevelThreeBeginState(mainRenderer, width, height, resources);
    states[STATE_LEVELFOURBEGIN] =
        new LevelFourBeginState(mainRenderer, width, height, resources);
    states[STATE_HIGHSCORE] =
        new HighScoreState(mainRenderer, width, height, resources);
    states[STATE_LEVELEDITOR] =
        new LevelEditor(mainRenderer, width, height, resources);
    State *currState = states[STATE_TITLE];
    int currStateType = STATE_TITLE;
    currState->startMusic(32);
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
        dtNano = std::chrono::duration_cast<std::chrono::duration<double>>(ctp -
                                                                           ltp);
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
            if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_p &&
                e.key.repeat == 0) {
                std::string test;
                while (!(std::cin >> test)) {
                }
                currentTime = SDL_GetTicks();
                lastTime = currentTime;
            }
            // Handle input for the player
            int stateChange = currState->handleEvent(&e, dt);
            if (stateChange != currStateType) {

                switch (stateChange) {
                case STATE_GAME:
                    currState = states[STATE_GAME];
                    currStateType = STATE_GAME;
                    currState->startMusic(32);
                    continue;
                    break;
                case STATE_MAINMENU:
                    currState = states[STATE_MAINMENU];
                    currStateType = STATE_MAINMENU;
                    currState->startMusic(32);
                    break;
                case STATE_HIGHSCORE: {
                    int highScore = -1;
                    if (currStateType == STATE_GAME) {
                        GameState *game = (GameState *)currState;
                        highScore = game->getHighScore();
                        game->reset();
                    }
                    currState = states[STATE_HIGHSCORE];
                    currStateType = STATE_HIGHSCORE;
                    HighScoreState *hs = (HighScoreState *)currState;
                    hs->setCurrScore(highScore);
                    currState->startMusic(32);
                } break;
                case STATE_LEVELONEBEGIN: {
                    currState = states[STATE_LEVELONEBEGIN];
                    currStateType = STATE_LEVELONEBEGIN;
                    break;
                }
                case STATE_LEVELONEINSTRUCT: {
                    currState = states[STATE_LEVELONEINSTRUCT];
                    currStateType = STATE_LEVELONEINSTRUCT;
                    break;
                }
                case STATE_LEVELTWOBEGIN: {
                    currState = states[STATE_LEVELTWOBEGIN];
                    currStateType = STATE_LEVELTWOBEGIN;
                    break;
                }
                case STATE_LEVELTHREEBEGIN: {
                    currState = states[STATE_LEVELTHREEBEGIN];
                    currStateType = STATE_LEVELTHREEBEGIN;
                    break;
                }
                case STATE_LEVELFOURBEGIN: {
                    currState = states[STATE_LEVELFOURBEGIN];
                    currStateType = STATE_LEVELFOURBEGIN;
                    break;
                }
                case STATE_LEVELEDITOR: {
                    currState = states[STATE_LEVELEDITOR];
                    currStateType = STATE_LEVELEDITOR;
                    break;
                }
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
        if (renderFPS)
            printFPS(dtNano);
        SDL_RenderPresent(mainRenderer);
    }
    for (State *s : states) {
        delete s;
    }

    return;
}

void setup(const char *title) {

    std::srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "oops. Failed to init: " << SDL_GetError() << "\n";
    }

    int code = Mix_Init(MIX_INIT_MOD | MIX_INIT_OGG);

    if (code == (MIX_INIT_MOD | MIX_INIT_OGG)) {
        std::cout << "MP3 libraries loaded fine: " << code << "\n";
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

    mainRenderer = SDL_CreateRenderer(
        mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (mainRenderer == NULL) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    TTF_Init();

    return;
}

void cleanup() {
    delete resources;
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void printFPS(std::chrono::duration<double> dtNano) {
    double framerate = 1.0 / dtNano.count();
    std::ostringstream strs;
    strs << framerate;
    std::string str = strs.str();
    SDL_Texture *fps =
        resources->getFont(std::string("manaspc30"), std::string("FPS:") + str);
    int w, h;
    SDL_QueryTexture(fps, NULL, NULL, &w, &h);
    SDL_Rect temp = {0, 0, w, h};
    SDL_RenderCopy(mainRenderer, fps, NULL, &temp);
    SDL_DestroyTexture(fps);
}

void load() {
    resources = new ResourceManager(mainRenderer);

    return;
}
