#ifndef LIZARD_LEVELONEINSTRUCT_STATE
#define LIZARD_LEVELONEINSTRUCT_STATE

#include "State.h"

class LevelOneInstructState : public State {
public:
    int getMyState() { return STATE_LEVELONEINSTRUCT; }
    LevelOneInstructState(SDL_Renderer *r, int width, int height,
                          ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);

    ~LevelOneInstructState();

private:
    int width, height;
    int time = 0;

    SDL_Texture *spikeInfo = nullptr;
    SDL_Rect spikeInfoRect;

    SDL_Texture *checkInfo = nullptr;
    SDL_Rect checkInfoRect;

    SDL_Texture *mechInfo = nullptr;
    SDL_Rect mechInfoRect;

    SDL_Texture *startInfo = nullptr;
    SDL_Rect startInfoRect;

    std::string spikeInfoTitle = "Avoid spikes";
    std::string checkInfoTitle = "Checkpoints are there to help";
    std::string mechInfoTitle = "Use gravity to your advantage!";
    std::string startInfoTitle = "Press space to start.";
    int titleAlpha = 0;
    bool fadein = false;
    SDL_Renderer *renderer;
    ResourceManager *resources;

    void floatingMove(int speed, int dt);
};

#endif
