#ifndef DIALOGUE_GRAPHICS_COMPONENT_LIZARD
#define DIALOGUE_GRAPHICS_COMPONENT_LIZARD

#include "DialogueObject.h"
#include "GraphicsComponent.h"
#include <iostream>
#include <string>
#include <vector>

class DialogueObject;

class DialogueGraphicsComponent : public GraphicsComponent {
public:
    DialogueGraphicsComponent(SDL_Renderer *ren, ResourceManager *r,
                              std::vector<std::string> spritenames);
    void update(World *world);
    ~DialogueGraphicsComponent();
    void setCurrState(int state);
    DialogueObject *myDialogue = nullptr;

private:
    int currState = 0;
    void updateCurrentSprite();
};

#endif
