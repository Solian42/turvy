#ifndef LIZARD_HIGHSCORE_STATE
#define LIZARD_HIGHSCORE_STATE

#include "State.h"

class HighScoreState : public State {
public:
    int getMyState() { return STATE_HIGHSCORE; }
    HighScoreState(SDL_Renderer *r, int width, int height,
                   ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic();

    ~HighScoreState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *title;
    SDL_Rect titleRect;

    SDL_Texture *highScore;
    SDL_Rect highScoreRect;

    SDL_Texture *backToMenu;
    SDL_Rect backToMenuRect;

    std::string titleTitle = "Your high score is:";
    std::string highScoreTitle = "42";
    std::string backToMenuTitle = "[Press space to go back to menu!]";

    SDL_Renderer *renderer;
    ResourceManager *resources;
};

#endif