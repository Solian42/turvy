#ifndef LIZARD_TITLE_STATE
#define LIZARD_TITLE_STATE

#include "State.h"

class TitleState : public State {
public:
    const int STATETYPE = STATE_TITLE;
    TitleState(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic();

    ~TitleState();

private:
    int width, height;

    SDL_Texture *titleFont;
    SDL_Rect titleRect;

    SDL_Texture *msgFont;
    SDL_Rect msgRect;

    std::string title = std::string("Lizard Games");
    std::string titleMessage = std::string("Press any key to begin");
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
