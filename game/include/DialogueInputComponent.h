#ifndef DIALOGUE_INPUT_COMPONENT_LIZARD
#define DIALOGUE_INPUT_COMPONENT_LIZARD

#include "DialogueObject.h"
#include "InputComponent.h"
#include <iostream>
#include <string>
class DialogueObject;

class DialogueInputComponent : public InputComponent {
public:
    DialogueInputComponent(World *world);
    void setDialogue(DialogueObject *d);
    void update(SDL_Event *event, int dt);
    ~DialogueInputComponent();
    

private:
    World *world; 
    DialogueObject *myDialogue;   
};

#endif
