#ifndef INPUT_COMPONENT_LIZARD
#define INPUT_COMPONENT_LIZARD

#include "GameObject.h"
#include "World.h"
class InputComponent
{
public:
  virtual ~InputComponent() {}
  virtual void update(GameObject& obj, World& world) = 0;
};

#endif
