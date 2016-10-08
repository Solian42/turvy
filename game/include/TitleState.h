#ifndef LIZARD_TITLE_STATE
#define LIZARD_TITLE_STATE

#include "State.h"

class TitleState : public State {
public:
    int getMyState() { return STATE_TITLE; }
    TitleState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~TitleState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *titleFont = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *msgFont = nullptr;
    SDL_Rect msgRect;

    SDL_Texture *gameTitle = nullptr;
    SDL_Rect gameTitleRect;

    std::string title = std::string("Lizard Games presents:");
    std::string gameName = "Turvy";
    std::string titleMessage = std::string("Press any key to begin");
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
