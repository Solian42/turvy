#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res) {
    windowHeight = height;
    windowWidth = width;
    XmlParser *parser = new XmlParser();
    numEntities = 1;
    renderer = r;
    resources = res;
    entities = std::vector<GameObject *>(1);
    world = new World(numEntities, parser->parsedPlatforms.size(),
                      parser->parsedSpikes.size(),
                      parser->parsedCheckpoints.size());

    entities[0] =
        createPlayer(0, {"rps0", "rps1", "rps2", "rps3", "ulps0", "ulps1",
                         "ulps2", "ulps3", "lps0", "lps1", "lps2", "lps3",
                         "urps0", "urps1", "urps2", "urps3"});
    int j = 0;
    for (std::pair<std::string, SDL_Rect> pair : parser->parsedPlatforms) {
        for (int i = 0; i < pair.second.w / 20; i++) {
            for (int k = 0; k < pair.second.h / 20; k++) {
                if (i == 0 && k == 0) {
                    // bottom left corner
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat1"});
                    PlatformObject *platform = new PlatformObject(
                        pair.second.x + (20 * i), pair.second.y + (20 * j), 20,
                        20, j, g);
                    platforms.push_back(platform);
                } else if ((i == (pair.second.w / 20) - 1) && (k == 0)) {
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat2"});
                    PlatformObject *platform = new PlatformObject(
                        pair.second.x + (20 * i), pair.second.y + (20 * j), 20,
                        20, j, g);
                    // bottom right corner
                    platforms.push_back(platform);
                } else if ((i == 0) && (k == (pair.second.h / 20) - 1)) {
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat3"});
                    PlatformObject *platform = new PlatformObject(
                        pair.second.x + (20 * i), pair.second.y + (20 * j), 20,
                        20, j, g);
                    // top left corner
                    platforms.push_back(platform);
                } else if ((i == (pair.second.w / 20) - 1) &&
                           (k == (pair.second.h / 20) - 1)) {
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat4"});
                    PlatformObject *platform = new PlatformObject(
                        pair.second.x + (20 * i), pair.second.y + (20 * j), 20,
                        20, j, g);
                    // top right corner
                    platforms.push_back(platform);
                } else {

                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat5"});
                    PlatformObject *platform = new PlatformObject(
                        pair.second.x + (20 * i), pair.second.y + (20 * j), 20,
                        20, j, g);
                    platforms.push_back(platform);
                }
            }
        }
        world->platformVolumes[j] = pair.second;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair : parser->parsedSpikes) {
        for (int i = 0; i < (pair.second[2] / 20); i++) {
            SpikesGraphicsComponent *s =
                new SpikesGraphicsComponent(renderer, resources, {pair.first});
            s->scaleCurrentSprite(2);
            SpikesObject *spike =
                new SpikesObject((pair.second[0] + 20 * i), pair.second[1],
                                 pair.second[3], j, s);
            spikes.push_back(spike);
        }
        SDL_Rect temp = {pair.second[0], pair.second[1], pair.second[2], 20};
        world->spikeVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair :
         parser->parsedCheckpoints) {
        CheckpointGraphicsComponent *c =
            new CheckpointGraphicsComponent(renderer, resources, {pair.first});
        CheckpointObject *checkpoint =
            new CheckpointObject(pair.second[0], pair.second[1], j, c);
        checkpoints.push_back(checkpoint);
        SDL_Rect temp = {pair.second[0], pair.second[1], 20, 20};
        world->checkpointVolumes[j] = temp;
        j++;
    }

    player = (PlayerObject *)entities[0];

    backgroundObjects = std::vector<GameObject *>(1);

    backgroundObjects[0] = createSetpiece((1280 * 4) - (2 * 19) - 50,
                                          720 - (2 * 18) - 50, {"ts0"});
    backgroundObjects[0]->graphics->scaleCurrentSprite(2);
    backgroundMusic = std::string("game");
    scoreMgr = new ScoreManager(renderer, resources,
                                world); /*added score manager by Anthony*/

    background = resources->getTexture("background");
}

void GameState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic(backgroundMusic), -1);
    Mix_VolumeMusic(vol);
}

int GameState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_q:
            reset();
            return STATE_MAINMENU;
            break;
        case SDLK_r:
            player->setX(player->getCheckX());
            player->setY(player->getCheckY());
            world->setCameraX(-640 + player->getCheckX());
            player->setYVel(-.5);
            player->graphics->setUpsideDown(false);
            player->graphics->setCurrState(0);
            world->updateVolume(player->entityNum, player->getX(),
                                player->getY(), player->getW(), player->getH());
            break;
        }
    }
    if (hasWon) {
        return STATE_HIGHSCORE;
    }

    player->input->update(e, dt);

    return getMyState();
}

void GameState::doSound() { player->sound->update(world); }

void GameState::doPhysics(int dt) {
    world->collision = world->checkCollisions();
    player->physics->update(player, world, dt);
    if (world->testCollide(*player->getLocation(),
                           *backgroundObjects[0]->getLocation())) {
        hasWon = true;
        SDL_Event user_event;

        user_event.type = SDL_USEREVENT;
        user_event.user.code = 2;
        user_event.user.data1 = NULL;
        user_event.user.data2 = NULL;
        SDL_PushEvent(&user_event);
    }
}

void GameState::render(int dt) {

    SDL_RenderCopy(renderer, background, NULL, NULL);
    for (PlatformObject *p : platforms) {
        p->graphics->update(world);
    }
    for (SpikesObject *s : spikes) {
        s->graphics->update(world);
    }
    for (CheckpointObject *c : checkpoints) {
        c->graphics->update(world);
    }
    player->graphics->update(world, dt);
    backgroundObjects[0]->graphics->update(world, dt);
    scoreMgr->update();
    scoreMgr->printScore(1280,
                         0); /*added printscore upon width&height of screen*/
}

PlayerObject *GameState::createPlayer(int entityNum,
                                      std::vector<std::string> spriteNames) {
    PlayerInputComponent *i = new PlayerInputComponent(world);
    PlayerGraphicsComponent *g =
        new PlayerGraphicsComponent(renderer, resources, spriteNames);
    PlayerPhysicsComponent *p = new PlayerPhysicsComponent();
    std::vector<std::string> chunks = {std::string("bonk")};
    PlayerSoundComponent *s = new PlayerSoundComponent(chunks, resources);
    PlayerObject *player =
        new PlayerObject(50, 50, 0, -.5, i, g, s, p, entityNum);
    i->setPlayer(player);
    return player;
}

GameObject *GameState::createSetpiece(int x, int y,
                                      std::vector<std::string> sprites) {
    GraphicsComponent *g = new GraphicsComponent(renderer, resources, sprites);

    GameObject *game = new GameObject();
    game->setX((float)x);
    game->setY((float)y);
    game->graphics = g;
    g->setCurrentState(0);
    g->setGameObject(game);

    return game;
}

int GameState::getHighScore() { return scoreMgr->getScore(); }

void GameState::reset() {
    player->setX(50.0);
    player->setY(50.0);
    world->setCameraX(-640.0 + 50);
    world->setCurrCheckX(50.0);
    world->setCurrCheckY(50.0);
    player->setCheckX(50.0);
    player->setCheckY(50.0);
    player->setXVel(0.0);
    player->setYVel(-.5);
    player->graphics->setCurrState(0);
    player->graphics->setUpsideDown(false);
    scoreMgr->resetScore();
    hasWon = false;
    Mix_HaltMusic();
}

GameState::~GameState() {
    for (GameObject *g : entities) {
        delete g;
    }
    delete world;
    delete scoreMgr;
    SDL_DestroyTexture(background);
}
