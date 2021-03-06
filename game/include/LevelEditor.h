#ifndef LIZARD_LEVEL_EDITOR
#define LIZARD_LEVEL_EDITOR

#include "State.h"
enum { PLATFORM, SPIKE, CHECKPOINT, COIN, TRAMPOLINE, ENEMY, TROPHY };
class LevelEditor : public State {
public:
    const int SCROLLSIZE = 50;
    const int platBaseSize = 20;
    const int spikeBaseSize = 20;
    const int checkpointBaseSize = 20;
    const int coinBaseSize = 40;
    const int trampolineBaseSize = 10;
    struct DIMENSION {
        int x, y, w, h, dir;
    };
    struct WORLDVIEW {
        int x, y;
    };
    int getMyState() { return STATE_LEVELEDITOR; }
    LevelEditor(SDL_Renderer *r, int width, int height, ResourceManager *res);
    int handleEvent(SDL_Event *e, int dt);
    // std::string getHighScore();
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);
    void printMouseCoord();
    void followMouseCursor();
    void makeXML(std::string &filename);
    void curate();
    void translate(int nx, int ny);

    ~LevelEditor();

private:
    std::vector<DIMENSION> platforms;
    std::vector<DIMENSION> spikes;
    std::vector<DIMENSION> checkpoints;
    std::vector<DIMENSION> coins;
    std::vector<DIMENSION> trampolines;
    std::vector<DIMENSION> enemies;
    std::vector<DIMENSION> trophies;

    std::vector<DIMENSION> *currType;
    DIMENSION dim;
    WORLDVIEW worldView = {0, 0};
    SDL_Rect tempRect = {10, 10, 20, 20};
    std::string filename;
    int currentCursorType;
    int baseSize, direction;
    int junk, mx, my, cw, ch;
    int width, height;
    bool viewMouseCoord = false;
    bool lock = false;
    int lockMode = 0;
    bool renderPiece = false;
    SDL_Texture *title = nullptr;
    SDL_Rect titleRect;

    SDL_Texture *cursorTexture = nullptr;
    SDL_Rect cursorRect;

    std::string titleTitle = "Level Editor";

    SDL_Renderer *renderer;
    ResourceManager *resources;
};

#endif
