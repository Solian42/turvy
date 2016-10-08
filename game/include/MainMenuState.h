#ifndef LIZARD_MAINMENU_STATE
#define LIZARD_MAINMENU_STATE

#include "State.h"

class MainMenuState : public State {
public:
    int getMyState() { return STATE_MAINMENU; }
    MainMenuState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~MainMenuState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *newGame = nullptr;
    SDL_Rect newGameRect;

    SDL_Texture *highScore = nullptr;
    SDL_Rect highScoreRect;

    SDL_Texture *quitGame = nullptr;
    SDL_Rect quitGameRect;

    SDL_Texture *adjustBright = nullptr;
    SDL_Rect adjustBrightRect;

    SDL_Texture *adjustVol = nullptr;
    SDL_Rect adjustVolRect;

    std::string titleTitle = "Menu";
    std::string newGameTitle = "[Press space to begin new game!]";
    std::string highScoreTitle = "[Press H to view high score!]";
    std::string quitGameTitle = "[Press ESC to quit game!]";
    std::string adjustBrightTitle = "[Press B to adjust brightness!]";
    std::string adjustVolTitle = "[Press V to adjust volume!]";
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
