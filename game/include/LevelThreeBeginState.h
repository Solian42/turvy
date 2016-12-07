#ifndef LIZARD_LEVELTHREEBEGIN_STATE
#define LIZARD_LEVELTHREEBEGIN_STATE

#include "State.h"

class LevelThreeBeginState : public State {
public:
    int getMyState() { return STATE_LEVELTHREEBEGIN; }
    LevelThreeBeginState(SDL_Renderer *r, int width, int height,
                         ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~LevelThreeBeginState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *ready = nullptr;
    SDL_Rect readyRect;

    SDL_Texture *dialogue = nullptr;
    SDL_Rect dialogueRect;

    SDL_Texture *dialogueTwo = nullptr;
    SDL_Rect dialogueTwoRect;

    std::string titleTitle = "LEVEL THREE";
    std::string readyTitle = "[Press any key to start!]";
    std::string dialogueTitle = "\"I guess I've been abducted...\"";
    std::string dialogueTwoTitle =
        "Avoid aliens, Use gravity shifters to bounce!";
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
