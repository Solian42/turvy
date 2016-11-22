#ifndef DIALOGUE_OBJECT_LIZARD
#define DIALOGUE_OBJECT_LIZARD

#include "GameObject.h"
#include "DialogueGraphicsComponent.h"
#include "DialogueInputComponent.h"

class DialogueGraphicsComponent;
class DialogueInputComponent;

class DialogueObject : public GameObject {

public:
    DialogueObject(int x, int y, int w, int h, int checkNum, DialogueGraphicsComponent *g,
                   DialogueInputComponent *i);

    ~DialogueObject();

    DialogueGraphicsComponent *graphics;
    DialogueInputComponent *input;
    int checkNum;
    bool skip = false;

private:
};

#endif