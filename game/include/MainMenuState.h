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
    int currSelect = 0;
    int width, height;
    int time = 0;

    SDL_Texture *title[2] = {NULL, NULL};
    SDL_Rect titleRect;

    SDL_Texture *newGame[2] = {NULL, NULL};
    SDL_Rect newGameRect;

    SDL_Texture *highScore[2] = {NULL, NULL};
    SDL_Rect highScoreRect;

    SDL_Texture *quitGame[2] = {NULL, NULL};
    SDL_Rect quitGameRect;

    SDL_Texture *adjustBright[2] = {NULL, NULL};
    SDL_Rect adjustBrightRect;

    SDL_Texture *navigation = nullptr;
    SDL_Rect navigationRect;

    std::string titleTitle = "Main Menu";
    std::string newGameTitle = "New Game";
    std::string highScoreTitle = "High Scores";
    std::string quitGameTitle = "Quit";
    std::string adjustBrightTitle = "Options";
    std::string navigationTitle = "[Up/Down] to navigate, [Enter] to select";
    SDL_Renderer *renderer;

    void floatingMove(int speed, int dt);
};

#endif
