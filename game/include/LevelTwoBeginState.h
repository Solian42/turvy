#ifndef LIZARD_LEVELTWOBEGIN_STATE
#define LIZARD_LEVELTWOBEGIN_STATE

#include "State.h"

class LevelTwoBeginState : public State {
public:
    int getMyState() { return STATE_LEVELTWOBEGIN; }
    LevelTwoBeginState(SDL_Renderer *r, int width, int height,
                       ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~LevelTwoBeginState();

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

    std::string titleTitle = "LEVEL TWO";
    std::string readyTitle = "[Press space to start!]";
    std::string dialogueTitle = "\"Wait, where's my ship? Anybody there?\"";
    std::string dialogueTwoTitle = "(Get a coin for a HS boost!)";
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif