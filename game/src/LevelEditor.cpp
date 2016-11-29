#include "../include/LevelEditor.h"

// const int SCROLLSIZE = 50;

LevelEditor::LevelEditor(SDL_Renderer *r, int width, int height,
                         ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getFont("manaspc60", titleTitle);
    junk = 0;
    mx = 0;
    my = 0;
    dim = {0, 0, 0, 0, 0};
    direction = 0;
    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.16), w, h};

    // cursorRect = {50, 50, 50, 50};
    cursorTexture = resources->getTexture("baseplatcursor");
    currentCursorType = PLATFORM;
    baseSize = platBaseSize;
    currType = &platforms;
    SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
    cursorRect = {mx, my, cw, ch};
}

int LevelEditor::handleEvent(SDL_Event *e, int dt) {
    int supressWarning = dt;
    supressWarning++;
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            Mix_HaltMusic();
            SDL_ShowCursor(SDL_ENABLE);
            filename = "../data/levels/level_editor.xml";
            makeXML(filename);
            return STATE_MAINMENU;
            break;
        case SDLK_c:
            viewMouseCoord = !viewMouseCoord;
            break;
        case SDLK_1:
            currentCursorType = PLATFORM;
            currType = &platforms;
            baseSize = platBaseSize;
            cursorTexture = resources->getTexture("baseplatcursor");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_2:
            currentCursorType = SPIKE;
            currType = &spikes;
            baseSize = spikeBaseSize;
            cursorTexture = resources->getTexture("spike1");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_3:
            currentCursorType = CHECKPOINT;
            currType = &checkpoints;
            cursorTexture = resources->getTexture("checkpoint1");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_4:
            currentCursorType = COIN;
            currType = &coins;
            cursorTexture = resources->getTexture("coin1");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_5:
            currentCursorType = TRAMPOLINE;
            currType = &trampolines;
            cursorTexture = resources->getTexture("trampoline1");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            lockMode = 1;
            break;
        case SDLK_6:
            currentCursorType = ENEMY;
            currType = &enemies;
            cursorTexture = resources->getTexture("es1");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_7:
            currentCursorType = TROPHY;
            currType = &trophies;
            cursorTexture = resources->getTexture("ts0");
            SDL_QueryTexture(cursorTexture, NULL, NULL, &cw, &ch);
            break;
        case SDLK_x:
            lockMode = 1;
            break;
        case SDLK_z:
            lockMode = -1;
            break;
        case SDLK_r:
            lockMode = 0;
            break;
        case SDLK_w:
            direction = 0;
            break;
        case SDLK_s:
            direction = 1;
            break;
        case SDLK_d:
            direction = 2;
            break;
        case SDLK_a:
            direction = 3;
            break;
        case SDLK_UP:
            worldView.y += SCROLLSIZE;
            break;
        case SDLK_RIGHT:
            worldView.x += SCROLLSIZE;
            break;
        case SDLK_DOWN:
            if (worldView.y > 0)
                worldView.y -= SCROLLSIZE;
            break;
        case SDLK_LEFT:
            if (worldView.x > 0)
                worldView.x -= SCROLLSIZE;
            break;
        default:
            break;
        }
    }
    if (e->type ==
        SDL_MOUSEMOTION /*|| e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP*/) {
        // Get mouse position
        int trash;
        if (lock && lockMode == -1)
            SDL_GetMouseState(&trash, &my);
        else if (lock && lockMode == 1)
            SDL_GetMouseState(&mx, &trash);
        else
            SDL_GetMouseState(&mx, &my);
    }
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        lock = true;
        SDL_GetMouseState(&dim.x, &dim.y);
    }
    if (e->type == SDL_MOUSEBUTTONUP) {
        lock = false;
        renderPiece = true;
        int nx, ny;
        SDL_GetMouseState(&nx, &ny);

        //
        translate(nx, ny);

        currType->push_back(dim);

        dim = {0, 0, 0, 0, 0};
    }
    return getMyState();
}

void LevelEditor::doSound() { return; }

void LevelEditor::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelEditor::printMouseCoord() {
    std::string str = std::to_string(mx) + ", " + std::to_string(my);
    SDL_Texture *mouseCoord = resources->getFont(std::string("manaspc30"),
                                                 std::string("Coord:") + str);
    SDL_Texture *dimCoord = resources->getFont(
        std::string("manaspc30"), std::string("dim:") + std::to_string(dim.x) +
                                      ", " + std::to_string(dim.y) + ", " +
                                      std::to_string(dim.w) + ", " +
                                      std::to_string(dim.h));
    int w, h;
    SDL_QueryTexture(mouseCoord, NULL, NULL, &w, &h);
    SDL_Rect temp = {0, 0, w, h};
    SDL_Rect temp2 = {100, 100, w, h};
    SDL_RenderCopy(renderer, mouseCoord, NULL, &temp);
    SDL_RenderCopy(renderer, dimCoord, NULL, &temp2);
    SDL_DestroyTexture(mouseCoord);
}
void LevelEditor::followMouseCursor() {
    int angle = 0;
    switch (direction) {
    case 1:
        angle = 180;
        break;
    case 2:
        angle = 90;
        break;
    case 3:
        angle = 270;
        break;
    default:
        break;
    }
    cursorRect = {mx /*-cw*/, my /*-ch*/, cw, ch};
    if (SDL_RenderCopyEx(renderer, cursorTexture, NULL, &cursorRect, angle,
                         NULL, SDL_FLIP_NONE) < 0) {
        std::cout << "cursor rendercopy broke: " << SDL_GetError();
    }
}
void LevelEditor::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "title rendercopy broke: " << SDL_GetError();
    }
    if (viewMouseCoord)
        printMouseCoord();
    followMouseCursor();
    if (renderPiece) {
        SDL_RenderCopy(renderer, cursorTexture, NULL, &cursorRect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 170, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &tempRect);
    curate();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    int supressWarning = dt;
    supressWarning++;
}
void LevelEditor::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("highscore"), -1);
    Mix_VolumeMusic(vol);
    return;
}
void LevelEditor::curate() {
    for (DIMENSION d : platforms) {
        if ((d.x + d.w > worldView.x && d.x < 1280 + worldView.x) &&
            (d.y + d.h > worldView.y && d.y < 720 + worldView.y)) {
            SDL_Rect temp;
            if (d.h != platBaseSize)
                temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            else
                temp = {d.x, 720 - d.y, d.w, d.h};
            // curatedPlatforms.push_back(temp);
            temp.x -= worldView.x;
            temp.y += worldView.y;
            SDL_SetRenderDrawColor(renderer, 255, 255, 170, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &temp);
        }
    }
    /* TODO: COVER MORE OBJ!*/

    for (DIMENSION d : spikes) {
        if ((d.x + d.w > worldView.x && d.x < 1280 + worldView.x) &&
            (d.y + d.h > worldView.y && d.y < 720 + worldView.y)) {
            SDL_Rect temp;
            if (d.h != spikeBaseSize)
                temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            else
                temp = {d.x, 720 - d.y, d.w, d.h};
            // curatedPlatforms.push_back(temp);
            temp.x -= worldView.x;
            temp.y += worldView.y;
            SDL_SetRenderDrawColor(renderer, 246, 66, 104, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &temp);
        }
    }

    for (DIMENSION d : checkpoints) {
        if ((d.x + checkpointBaseSize > worldView.x &&
             d.x < 1280 + worldView.x) &&
            (d.y + checkpointBaseSize > worldView.y &&
             d.y < 720 + worldView.y)) {
            SDL_Rect temp;
            // if(d.h != spikeBaseSize) temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            // else temp = {d.x, 720 - d.y, d.w, d.h};
            temp = {d.x, 720 - d.y, checkpointBaseSize, checkpointBaseSize};
            // curatedPlatforms.push_back(temp);
            temp.x -= worldView.x;
            temp.y += worldView.y;
            SDL_SetRenderDrawColor(renderer, 191, 229, 239, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &temp);
        }
    }

    for (DIMENSION d : coins) {
        if ((d.x + coinBaseSize > worldView.x && d.x < 1280 + worldView.x) &&
            (d.y + coinBaseSize > worldView.y && d.y < 720 + worldView.y)) {
            SDL_Rect temp;
            // if(d.h != spikeBaseSize) temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            // else temp = {d.x, 720 - d.y, d.w, d.h};
            temp = {d.x, 720 - d.y, coinBaseSize, coinBaseSize};
            // curatedPlatforms.push_back(temp);
            temp.x -= worldView.x;
            temp.y += worldView.y;
            SDL_SetRenderDrawColor(renderer, 252, 209, 35, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &temp);
        }
    }

    for (DIMENSION d : trampolines) {
        if ((d.x + trampolineBaseSize > worldView.x &&
             d.x < 1280 + worldView.x) &&
            (d.y + trampolineBaseSize > worldView.y &&
             d.y < 720 + worldView.y)) {
            SDL_Rect temp;
            // if(d.h != spikeBaseSize) temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            // else temp = {d.x, 720 - d.y, d.w, d.h};
            // temp = {d.x, 720 - d.y, coinBaseSize, coinBaseSize};
            if (d.h != trampolineBaseSize)
                temp = {d.x, 720 - d.y - d.h, d.w, d.h};
            else
                temp = {d.x, 720 - d.y, d.w, d.h};
            // curatedPlatforms.push_back(temp);
            temp.x -= worldView.x;
            temp.y += worldView.y;
            SDL_SetRenderDrawColor(renderer, 0, 255, 165, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &temp);
        }
    }
}
void LevelEditor::makeXML(std::string &filename) {
    int count = 1;

    std::ofstream xmlfile;
    xmlfile.open(filename);
    xmlfile << std::string("<rectangles>\n");
    xmlfile << std::string("    <platforms>\n");
    for (DIMENSION d : platforms) {
        xmlfile << std::string("        <p") << count << '>' << '\n';

        xmlfile << std::string("            <x> ") << d.x
                << std::string(" </x>\n");
        xmlfile << std::string("            <y> ") << d.y
                << std::string(" </y>\n");
        xmlfile << std::string("            <width> ") << d.w
                << std::string(" </width>\n");
        xmlfile << std::string("            <height> ") << d.h
                << std::string(" </height>\n");
        xmlfile << std::string("            <texture> base")
                << std::string(" </texture>\n");
        xmlfile << std::string("        </p") << count << '>' << '\n';
        count++;
    }
    xmlfile << std::string("    </platforms>\n");
    count = 1;
    xmlfile << std::string("    <spikes>\n");
    for (DIMENSION d : spikes) {
        xmlfile << std::string("        <s") << count << '>' << '\n';

        xmlfile << std::string("            <x> ") << d.x
                << std::string(" </x>\n");
        xmlfile << std::string("            <y> ") << d.y
                << std::string(" </y>\n");
        xmlfile << std::string("            <w> ") << d.w
                << std::string(" </w>\n");
        xmlfile << std::string("            <h> ") << d.h
                << std::string(" </h>\n");
        xmlfile << std::string("            <direction> ") << d.dir
                << std::string(" </direction>\n");
        xmlfile << std::string("            <texture> spike1")
                << std::string(" </texture>\n");
        xmlfile << std::string("        </s") << count << '>' << '\n';
        count++;
    }
    xmlfile << std::string("    </spikes>\n");
    count = 1;

    xmlfile << std::string("    <checkpoints>\n");
    for (DIMENSION d : checkpoints) {
        xmlfile << std::string("        <c") << count << '>' << '\n';

        xmlfile << std::string("            <x> ") << d.x
                << std::string(" </x>\n");
        xmlfile << std::string("            <y> ") << d.y
                << std::string(" </y>\n");
        xmlfile << std::string("            <texture> checkpoint1 ")
                << std::string(" </texture>\n");
        xmlfile << std::string("            <texture> checkpoint2 ")
                << std::string(" </texture>\n");
        xmlfile << std::string("        </c") << count << '>' << '\n';
        count++;
    }
    xmlfile << std::string("    </checkpoints>\n");
    count = 1;

    xmlfile << std::string("    <coins>\n");
    for (DIMENSION d : coins) {
        xmlfile << std::string("        <coin") << count << '>' << '\n';

        xmlfile << std::string("            <x> ") << d.x
                << std::string(" </x>\n");
        xmlfile << std::string("            <y> ") << d.y
                << std::string(" </y>\n");
        xmlfile << std::string("            <texture> coin1 ")
                << std::string(" </texture>\n");
        xmlfile << std::string("        </coin") << count << '>' << '\n';
        count++;
    }
    xmlfile << std::string("    </coins>\n");
    count = 1;

    xmlfile << std::string("    <trampolines>\n");
    for (DIMENSION d : trampolines) {
        xmlfile << std::string("        <t") << count << '>' << '\n';

        xmlfile << std::string("            <x> ") << d.x
                << std::string(" </x>\n");
        xmlfile << std::string("            <y> ") << d.y
                << std::string(" </y>\n");
        xmlfile << std::string("            <w> ") << d.w
                << std::string(" </w>\n");
        xmlfile << std::string("            <texture> trampoline1 ")
                << std::string(" </texture>\n");
        xmlfile << std::string("        </t") << count << '>' << '\n';
        count++;
    }
    xmlfile << std::string("    </trampolines>\n");
    count = 1;
    // TODO: MORE!

    xmlfile << std::string("</rectangles>\n");
    xmlfile.close();
}

void LevelEditor::translate(int nx, int ny) {
    dim.dir = direction;
    if (lockMode == -1) {
        dim.h = ny - dim.y;
    } else if (lockMode == 1) {
        dim.w = nx - dim.x;
    } else {
        dim.w = nx - dim.x;
        dim.h = ny - dim.y;
    }
    //
    if (dim.h > 0) {
        dim.y = ny;
    }
    if (dim.w < 0) {
        dim.x = nx;
    }
    if (dim.w == 0 && dim.h != 0)
        dim.w = baseSize;
    if (dim.h == 0 && dim.w != 0)
        dim.h = baseSize;
    dim.y = 720 - dim.y;
    //

    if (dim.h < 0) {
        dim.h = 0 - dim.h;
        // dim.y = dim.y + dim.h;
    }
    if (dim.w < 0) {
        dim.w = 0 - dim.w;
        //
    }
    dim.x += worldView.x;
    dim.y += worldView.y;
}
LevelEditor::~LevelEditor() {
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(cursorTexture);

    // SDL_DestroyTexture(currTitle);
}
