#ifndef INPUT_COMPONENT_LIZARD
#define INPUT_COMPONENT_LIZARD

#include "GameObject.h"
#include <SDL.h>

class GameObject;

class InputComponent {
public:
    virtual ~InputComponent() {}
    void update(GameObject *obj);
};

#endif
