#ifndef SOUND_COMPONENT_LIZARD
#define SOUND_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL_mixer.h>
class GameObject;

class SoundComponent {
public:
    virtual ~SoundComponent() {}
    void update(GameObject *obj);
};

#endif
