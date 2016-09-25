#ifndef SOUND_COMPONENT_LIZARD
#define SOUND_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
#include <SDL_mixer.h>
class SoundComponent
{
public:
  virtual ~SoundComponent() {}
  virtual void update(GameObject& obj) = 0;
};

#endif
