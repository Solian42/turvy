#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res, std::vector<std::string> levelNames,
                     int levels) {
    windowHeight = height;
    windowWidth = width;
    numLevels = levels;
    currLevel = 1;
    numEntities = 1;
    renderer = r;
    resources = res;
    this->levelNames = levelNames;
    loadNewLevel(levelNames[0]);
}

void GameState::loadNewLevel(std::string levelName) {
    if (!(levelName == std::string("level1"))) {
        cleanCurrentLevel();
    }
    XmlParser *parser = new XmlParser(resources->getLevel(levelName));
    world = new World(numEntities, parser->parsedPlatforms.size(),
                      parser->parsedSpikes.size(),
                      parser->parsedCheckpoints.size());
    player = createPlayer(0, {"rps0", "rps1", "rps2", "rps3", "ulps0", "ulps1",
                              "ulps2", "ulps3", "lps0", "lps1", "lps2", "lps3",
                              "urps0", "urps1", "urps2", "urps3"});
    platforms = std::vector<PlatformObject *>();
    spikes = std::vector<SpikesObject *>();
    backgroundObjects = std::vector<GameObject *>();
    checkpoints = std::vector<CheckpointObject *>();
    entities = std::vector<GameObject *>(1);
    entities[0] = player;
    int j = 0;
    for (std::pair<std::string, SDL_Rect> pair : parser->parsedPlatforms) {
        for (int i = 0; i < pair.second.w / MIN_TILE_SIZE; i++) {
            for (int k = 0; k < pair.second.h / MIN_TILE_SIZE; k++) {
                if (i == 0) {
                    if (k == 0) {
                        // bottom left corner
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat7"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                        // top left corner
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat1"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else {
                        // left side
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat8"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    }

                } else if (i == (pair.second.w / MIN_TILE_SIZE) - 1) {
                    if (k == 0) {
                        // bottom right corner
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat5"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                        // top right corner
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat3"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else {
                        // right side
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {"plat4"});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    }

                } else if (k == 0) {
                    // bottom (not corner)
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat6"});
                    PlatformObject *platform =
                        new PlatformObject(pair.second.x + (MIN_TILE_SIZE * i),
                                           pair.second.y + (MIN_TILE_SIZE * k),
                                           MIN_TILE_SIZE, MIN_TILE_SIZE, j, g);
                    platforms.push_back(platform);
                } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                    // top (not corner)
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat2"});
                    PlatformObject *platform =
                        new PlatformObject(pair.second.x + (MIN_TILE_SIZE * i),
                                           pair.second.y + (MIN_TILE_SIZE * k),
                                           MIN_TILE_SIZE, MIN_TILE_SIZE, j, g);
                    platforms.push_back(platform);
                } else {
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {"plat9"});
                    PlatformObject *platform =
                        new PlatformObject(pair.second.x + (MIN_TILE_SIZE * i),
                                           pair.second.y + (MIN_TILE_SIZE * k),
                                           MIN_TILE_SIZE, MIN_TILE_SIZE, j, g);
                    platforms.push_back(platform);
                }
            }
        }
        world->platformVolumes[j] = pair.second;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair : parser->parsedSpikes) {
        for (int i = 0; i < (pair.second[2] / (MIN_TILE_SIZE * 2)); i++) {
            SpikesGraphicsComponent *s =
                new SpikesGraphicsComponent(renderer, resources, {pair.first});
            s->scaleCurrentSprite(2);
            SpikesObject *spike =
                new SpikesObject((pair.second[0] + (MIN_TILE_SIZE * 2) * i),
                                 pair.second[1], pair.second[3], j, s);
            spikes.push_back(spike);
        }
        SDL_Rect temp = {pair.second[0], pair.second[1], pair.second[2],
                         (MIN_TILE_SIZE * 2)};
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
        SDL_Rect temp = {pair.second[0], pair.second[1], MIN_TILE_SIZE,
                         MIN_TILE_SIZE};
        world->checkpointVolumes[j] = temp;
        j++;
    }

    backgroundObjects = std::vector<GameObject *>(1);

    backgroundObjects[0] = createSetpiece((1280 * 4) - (2 * 19) - 50,
                                          720 - (2 * 18) - 50, {"ts0"});
    backgroundObjects[0]->graphics->scaleCurrentSprite(2);
    backgroundMusic = std::string("game");
    scoreMgr = new ScoreManager(renderer, resources,
                                world); /*added score manager by Anthony*/

    background = resources->getTexture("background");
    delete parser;
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
        case SDLK_2:
            loadNewLevel(levelNames[currLevel]);
            currLevel++;
            break;
        }
    }
    if (hasWon) {
        if (currLevel == numLevels) {
            reset();
            return STATE_HIGHSCORE;
        }
        loadNewLevel(levelNames[currLevel]);
        currLevel++;
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
    SDL_Rect intersect = {0, 0, 0, 0};
    for (PlatformObject *p : platforms) {
        if (world->intersectCamera(p->getLocation())) {
            p->graphics->update(world);
        }
    }
    for (SpikesObject *s : spikes) {
        if (world->intersectCamera(s->getLocation())) {
            s->graphics->update(world);
        }
    }
    for (CheckpointObject *c : checkpoints) {
        if (world->intersectCamera(c->getLocation())) {
            c->graphics->update(world);
        }
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
    world->setCameraX(world->getCameraX() + 50);
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
    currLevel = 1;
    loadNewLevel(levelNames[0]);
    scoreMgr->resetScore();
    hasWon = false;
    Mix_HaltMusic();
}

void GameState::cleanCurrentLevel() {
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

    for (GameObject *g : entities) {
        delete g;
    }
    for (PlatformObject *p : platforms) {
        delete p;
    }
    for (SpikesObject *s : spikes) {
        delete s;
    }
    for (CheckpointObject *c : checkpoints) {
        delete c;
    }
    for (GameObject *o : backgroundObjects) {
        delete o;
    }
    delete world;
}
GameState::~GameState() {
    for (GameObject *g : entities) {
        delete g;
    }
    for (PlatformObject *p : platforms) {
        delete p;
    }
    for (SpikesObject *s : spikes) {
        delete s;
    }
    for (CheckpointObject *c : checkpoints) {
        delete c;
    }
    for (GameObject *o : backgroundObjects) {
        delete o;
    }
    delete world;
    delete scoreMgr;
    SDL_DestroyTexture(background);
}
