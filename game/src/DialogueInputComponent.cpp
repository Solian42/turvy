#include "../include/DialogueInputComponent.h"

DialogueInputComponent::DialogueInputComponent(World *w) { world = w; }

void DialogueInputComponent::update(SDL_Event *event, int dt) {
    SDL_Event e = *event;
    int supressWarning = dt;
    supressWarning++;
    while(!myDialogue->skip){
        // If a key was pressed
        if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            switch (e.key.keysym.sym) {
            case SDLK_s:
                if (world->intersectCamera(myDialogue->getLocation())) {
                    myDialogue->skip = true;
                }
                break;
            }
        }
    }
    
}

void DialogueInputComponent::setDialogue(DialogueObject *d) { myDialogue = d; }

DialogueInputComponent::~DialogueInputComponent() {}
