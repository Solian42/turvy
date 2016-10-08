#ifndef LIZARD_HIGHSCORE_STATE
#define LIZARD_HIGHSCORE_STATE

#include "State.h"

class HighScoreState : public State {
public:
    int getMyState() { return STATE_HIGHSCORE; }
    HighScoreState(SDL_Renderer *r, int width, int height,
                   ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    std::string getHighScore();
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic();
    void setCurrScore(int score);
    void setHighScore(int score);

    ~HighScoreState();

private:
    int width, height;
    int time = 0;
    int currScoreInt = 0;

    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *currTitle = nullptr;
    SDL_Rect currTitleRect;

    SDL_Texture *currScore = nullptr;
    SDL_Rect currScoreRect;

    SDL_Texture *highScore = nullptr;
    SDL_Rect highScoreRect;

    SDL_Texture *backToMenu = nullptr;
    SDL_Rect backToMenuRect;

    std::string titleTitle = "Your high score is:";
    std::string currTitleTitle = "Your last score was:";
    std::string highScoreTitle = "No high scores found";
    std::string backToMenuTitle = "[Press space to go back to menu!]";

    SDL_Renderer *renderer;
    ResourceManager *resources;
};

#endif
