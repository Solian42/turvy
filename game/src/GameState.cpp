#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res,
                     std::vector<std::vector<std::string>> levelData,
                     int levels) {
    windowHeight = height;
    windowWidth = width;
    numLevels = levels;
    currLevel = 1;
    numEntities = 1;
    renderer = r;
    resources = res;
    this->levelNames = levelData[0];
    this->levelMusic = levelData[1];
    this->backgrounds = levelData[2];
    loadNewLevel(levelNames[0]);
}

void GameState::loadNewLevel(std::string levelName) {
    if (!(levelName == std::string("level1"))) {
        cleanCurrentLevel();
    }
    XmlParser *parser = new XmlParser(resources->getLevel(levelName));
    world = new World(
        1280 * 5, 720 * 10, numEntities, parser->parsedPlatforms.size(),
        parser->parsedSpikes.size(), parser->parsedCheckpoints.size(),
        parser->parsedCoins.size(), parser->parsedTrampolines.size(),
        parser->parsedEnemies.size(), parser->parsedTeleports.size(),
        parser->parsedDialogues.size());
    scoreMgr =
        new ScoreManager(renderer, resources, world, numDeaths, numCoins);

    player = createPlayer(0, scoreMgr,
                          {"rps0",  "rps1",  "rps2",  "rps3",  "ulps0",
                           "ulps1", "ulps2", "ulps3", "lps0",  "lps1",
                           "lps2",  "lps3",  "urps0", "urps1", "urps2",
                           "urps3", "pdsl",  "pdsr",  "pdsul", "pdsur",
                           "ptsl",  "ptsr",  "ptsul", "ptsur"});
    platforms = std::vector<PlatformObject *>();
    spikes = std::vector<SpikesObject *>();
    backgroundObjects = std::vector<GameObject *>();
    checkpoints = std::vector<CheckpointObject *>();
    coins = std::vector<CoinObject *>();
    trampolines = std::vector<TrampolineObject *>();
    enemies = std::vector<EnemyObject *>();
    teleports = std::vector<TeleportObject *>();
    dialogues = std::vector<DialogueObject *>();
    entities = std::vector<GameObject *>(1);
    statics = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, windowWidth * 5,
                                (windowHeight * 10));
    SDL_SetTextureBlendMode(statics, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, statics);
    SDL_RenderClear(renderer);
    entities[0] = player;
    int j = 0;
    world->setCameraY(0.0);
    for (std::pair<std::string, SDL_Rect> pair : parser->parsedPlatforms) {
        for (int i = 0; i < pair.second.w / MIN_TILE_SIZE; i++) {
            for (int k = 0; k < pair.second.h / MIN_TILE_SIZE; k++) {
                if (i == 0) {
                    if (k == 0) {
                        // bottom left corner
                        std::string platString = pair.first + "plat6";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                        // top left corner
                        std::string platString = pair.first + "plat0";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else {
                        // left side
                        std::string platString = pair.first + "plat3";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    }

                } else if (i == (pair.second.w / MIN_TILE_SIZE) - 1) {
                    if (k == 0) {
                        // bottom right corner
                        std::string platString = pair.first + "plat8";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                        // top right corner
                        std::string platString = pair.first + "plat2";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    } else {
                        // right side
                        std::string platString = pair.first + "plat5";
                        PlatformGraphicsComponent *g =
                            new PlatformGraphicsComponent(renderer, resources,
                                                          {platString});
                        PlatformObject *platform = new PlatformObject(
                            pair.second.x + (MIN_TILE_SIZE * i),
                            pair.second.y + (MIN_TILE_SIZE * k), MIN_TILE_SIZE,
                            MIN_TILE_SIZE, j, g);
                        platforms.push_back(platform);
                    }

                } else if (k == 0) {
                    // bottom (not corner)
                    std::string platString = pair.first + "plat7";
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {platString});
                    PlatformObject *platform =
                        new PlatformObject(pair.second.x + (MIN_TILE_SIZE * i),
                                           pair.second.y + (MIN_TILE_SIZE * k),
                                           MIN_TILE_SIZE, MIN_TILE_SIZE, j, g);
                    platforms.push_back(platform);
                } else if (k == (pair.second.h / MIN_TILE_SIZE) - 1) {
                    // top (not corner)
                    std::string platString = pair.first + "plat1";
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {platString});
                    PlatformObject *platform =
                        new PlatformObject(pair.second.x + (MIN_TILE_SIZE * i),
                                           pair.second.y + (MIN_TILE_SIZE * k),
                                           MIN_TILE_SIZE, MIN_TILE_SIZE, j, g);
                    platforms.push_back(platform);
                } else {
                    // inside
                    std::string platString = pair.first + "plat4";
                    PlatformGraphicsComponent *g =
                        new PlatformGraphicsComponent(renderer, resources,
                                                      {platString});
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
            for (int k = 0; k < (pair.second[3] / (MIN_TILE_SIZE * 2)); k++) {
                SpikesGraphicsComponent *s = new SpikesGraphicsComponent(
                    renderer, resources, {pair.first});
                s->scaleCurrentSprite(2);
                SpikesObject *spike =
                    new SpikesObject((pair.second[0] + (MIN_TILE_SIZE * 2) * i),
                                     (pair.second[1] + (MIN_TILE_SIZE * 2) * k),
                                     pair.second[4], j, s);
                spikes.push_back(spike);
            }
        }
        SDL_Rect temp = {pair.second[0], pair.second[1], pair.second[2],
                         pair.second[3]};
        world->spikeVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::vector<std::string>, std::vector<int>> pair :
         parser->parsedCheckpoints) {
        CheckpointGraphicsComponent *c = new CheckpointGraphicsComponent(
            renderer, resources, {pair.first[0], pair.first[1]});
        CheckpointObject *checkpoint =
            new CheckpointObject(pair.second[0], pair.second[1], j, c);
        checkpoints.push_back(checkpoint);
        SDL_Rect temp = {pair.second[0], pair.second[1], c->getCurrW(),
							c->getCurrH()};
        world->checkpointVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair : parser->parsedCoins) {
        CoinGraphicsComponent *co =
            new CoinGraphicsComponent(renderer, resources, {pair.first});
        CoinPhysicsComponent *ph = new CoinPhysicsComponent();
        CoinObject *coin =
            new CoinObject(pair.second[0], pair.second[1], j, co, ph, player);
        co->myCoin = coin;
        ph->myCoin = coin;
        coins.push_back(coin);
        SDL_Rect temp = {pair.second[0], pair.second[1], co->getCurrW(),
                         co->getCurrH()};
        world->coinVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair :
         parser->parsedTrampolines) {
        for (int i = 0; i < (pair.second[2] / (MIN_TILE_SIZE)); i++) {
            TrampolineGraphicsComponent *t = new TrampolineGraphicsComponent(
                renderer, resources, {pair.first});
            TrampolineObject *trampoline = new TrampolineObject(
                pair.second[0] + (MIN_TILE_SIZE * i), pair.second[1], j, t);
            trampolines.push_back(trampoline);
        }
        SDL_Rect temp = {pair.second[0], pair.second[1], pair.second[2],
                         MIN_TILE_SIZE - 2};
        world->trampolineVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::vector<std::string>, std::vector<int>> pair :
         parser->parsedEnemies) {
        EnemyGraphicsComponent *e = new EnemyGraphicsComponent(
            renderer, resources,
            {pair.first[0], pair.first[1], pair.first[2], pair.first[3]});
        EnemyPhysicsComponent *ph = new EnemyPhysicsComponent();
        EnemyInputComponent *in = new EnemyInputComponent();
        EnemyObject *enemy = new EnemyObject(pair.second[0], pair.second[1],
                                             pair.second[2], in, e, ph, j);
		if(world->collideWithPlatform(enemy).returnResult != 0) {
			enemy->setY(enemy->getY() - 10);
		}
        enemies.push_back(enemy);
    }
    j = 0;
    for (std::pair<std::vector<std::string>, std::vector<int>> pair :
         parser->parsedTeleports) {
        TeleportGraphicsComponent *te = new TeleportGraphicsComponent(
            renderer, resources, {pair.first[0], pair.first[1], pair.first[2]});
        TeleportPhysicsComponent *ph = new TeleportPhysicsComponent();
        TeleportObject *teleport =
            new TeleportObject(pair.second[0], pair.second[1], pair.second[2],
                               pair.second[3], j, te, ph, player);
        te->myTeleport = teleport;
        ph->myTeleport = teleport;
        teleports.push_back(teleport);
        SDL_Rect temp = {pair.second[0], pair.second[1], te->getCurrW(),
                         te->getCurrH()};
        world->teleportVolumes[j] = temp;
        j++;
    }
    j = 0;
    for (std::pair<std::string, std::vector<int>> pair :
         parser->parsedDialogues) {
        DialogueGraphicsComponent *d =
            new DialogueGraphicsComponent(renderer, resources, {pair.first});
        DialogueInputComponent *in = new DialogueInputComponent(world);
        DialogueObject *dialogue =
            new DialogueObject(pair.second[0], pair.second[1], pair.second[2],
                               pair.second[3], j, d, in);
        d->myDialogue = dialogue;
        in->setDialogue(dialogue);
        dialogues.push_back(dialogue);
        SDL_Rect temp = {pair.second[0], pair.second[1], pair.second[2],
                         pair.second[3]};
        world->dialogueVolumes[j] = temp;
        j++;
    }

    backgroundObjects = std::vector<GameObject *>(1);

    backgroundObjects[0] = createSetpiece((1280 * 4) - (2 * 19) - 50,
                                          720 - (2 * 18) - 50, {"tl0"});
    backgroundObjects[0]->graphics->scaleCurrentSprite(2);
    background = resources->getTexture(backgrounds[currLevel - 1]);
    backgroundMusic = levelMusic[currLevel - 1];
    for (PlatformObject *p : platforms) {
        p->graphics->update(world);
    }
    for (SpikesObject *s : spikes) {
        s->graphics->update(world);
    }
    for (TrampolineObject *t : trampolines) {
        t->graphics->update(world);
    }
    SDL_SetRenderTarget(renderer, NULL);
    delete parser;
    world->setCameraY(-360.0 + 50);
    world->setCameraH(720);
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
            world->setCameraY(-360.0 + player->getCheckY());
            player->setYVel(-.5);
            player->graphics->setUpsideDown(false);
            player->graphics->setCurrState(0);
            world->updateVolume(player->entityNum, player->getX(),
                                player->getY(), player->getW(), player->getH());
            break;
        case SDLK_2:
            currLevel = 2;
            if (player->getXVel() > 0) {
                SDL_Event user_event;
                user_event.type = SDL_KEYDOWN;
                user_event.key.keysym.sym = SDLK_RIGHT;
                user_event.key.repeat = 0;
                SDL_PushEvent(&user_event);
            }
            loadNewLevel(levelNames[1]);
            return STATE_LEVELTWOBEGIN;
            break;
        case SDLK_3:
            currLevel = 3;
            if (player->getXVel() > 0) {
                SDL_Event user_event;
                user_event.type = SDL_KEYDOWN;
                user_event.key.keysym.sym = SDLK_RIGHT;
                user_event.key.repeat = 0;
                SDL_PushEvent(&user_event);
            }
            loadNewLevel(levelNames[2]);
            return STATE_LEVELTHREEBEGIN;
            break;
        case SDLK_4:
            currLevel = 4;
            if (player->getXVel() > 0) {
                SDL_Event user_event;
                user_event.type = SDL_KEYDOWN;
                user_event.key.keysym.sym = SDLK_RIGHT;
                user_event.key.repeat = 0;
                SDL_PushEvent(&user_event);
            }
            loadNewLevel(levelNames[3]);
            return STATE_LEVELFOURBEGIN;
            break;

        case SDLK_l:
            currLevel = 5;
            if (player->getXVel() > 0) {
                SDL_Event user_event;
                user_event.type = SDL_KEYDOWN;
                user_event.key.keysym.sym = SDLK_RIGHT;
                user_event.key.repeat = 0;
                SDL_PushEvent(&user_event);
            }
            loadNewLevel(levelNames[4]);
            break;

        case SDLK_c:
            player->setCheckX(checkpoints[checkpoints.size() - 1]->getX());
            player->setCheckY(checkpoints[checkpoints.size() - 1]->getY());
            player->setX(player->getCheckX());
            player->setY(player->getCheckY());
            world->setCameraX(-640 + player->getCheckX());
            world->setCameraY(-360.0 + player->getCheckY());
            player->setYVel(-.5);
            player->graphics->setUpsideDown(false);
            player->graphics->setCurrState(0);
            world->updateVolume(player->entityNum, player->getX(),
                                player->getY(), player->getW(), player->getH());
            break;
        }
    }
    if (hasWon) {
        if (currLevel == (numLevels - 1)) {
            return STATE_HIGHSCORE;
        }

        if (player->getXVel() > 0) {
            SDL_Event user_event;
            user_event.type = SDL_KEYDOWN;
            user_event.key.keysym.sym = SDLK_RIGHT;
            user_event.key.repeat = 0;
            SDL_PushEvent(&user_event);
        }
        Mix_HaltMusic();
        currLevel++;
        loadNewLevel(levelNames[currLevel - 1]);
        hasWon = false;
        if (currLevel == 2) {
            return STATE_LEVELTWOBEGIN;
        }
        if (currLevel == 3) {
            return STATE_LEVELTHREEBEGIN;
        }
        if (currLevel == 4) {
            return STATE_LEVELFOURBEGIN;
        }
    }

    player->input->update(e, dt);
    for (DialogueObject *d : dialogues) {
        d->input->update(e, dt);
    }

    return getMyState();
}

void GameState::doSound() { player->sound->update(world); }

void GameState::doPhysics(int dt) {
    world->setCoinCollision(false);
    world->setSpikeCollision(world->checkSpikeCollisions());
    world->setEnemyCollision(world->checkEnemyCollisions());
    world->setTeleportCollision(world->checkTeleportCollisions());
    player->physics->update(player, world, dt);
    for (EnemyObject *e : enemies) {
        e->physics->update(e, world, dt);
    }
    for (CoinObject *co : coins) {
        co->physics->update(world, dt);
    }
    for (TeleportObject *te : teleports) {
        te->physics->update(world, dt);
    }

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
    numDeaths = scoreMgr->getDeaths();
    numCoins = scoreMgr->getCoins();
    scoreMgr->update();
}

void GameState::render(int dt) {
    SDL_Rect temp;
    SDL_RenderCopy(renderer, background, NULL, NULL);
    int h, w;
    SDL_QueryTexture(statics, NULL, NULL, &w, &h);
    temp = {world->transformXtoCamera(0), world->transformYtoCamera(h),
            5 * 1280, 7200};

    for (CheckpointObject *c : checkpoints) {
        if (world->intersectCamera(c->getLocation())) {
            c->graphics->update(world);
        }
    }
    for (TeleportObject *te : teleports) {
        te->graphics->update(world, dt);
    }

    SDL_RenderCopy(renderer, statics, NULL, &temp);
    player->graphics->update(world, dt);
    int j = 0;
    for (CoinObject *co : coins) {
        if (world->intersectCamera(co->getLocation())) {
            co->graphics->update(world);
        }
    }
    for (EnemyObject *e : enemies) {
        e->graphics->update(world, dt);
        SDL_Rect eTemp = {(int)e->getX(), (int)e->getY(), 25, 25};
        world->enemyVolumes[j] = eTemp;
        j++;
    }
    backgroundObjects[0]->graphics->update(world, dt);
    for (DialogueObject *d : dialogues) {
        d->graphics->update(world);
    }
    scoreMgr->printScore(1280, 0);
}

PlayerObject *GameState::createPlayer(int entityNum, ScoreManager *score,
                                      std::vector<std::string> spriteNames) {
    PlayerInputComponent *i = new PlayerInputComponent(world);
    PlayerGraphicsComponent *g =
        new PlayerGraphicsComponent(renderer, resources, spriteNames);
    PlayerPhysicsComponent *p = new PlayerPhysicsComponent();
    std::vector<std::string> chunks = {std::string("bonk")};
    PlayerSoundComponent *s = new PlayerSoundComponent(chunks, resources);
    PlayerObject *player =
        new PlayerObject(50, 50, 0, -.5, i, g, s, p, entityNum, score);
    world->setCameraX(world->getCameraX() + 50);
    world->setCameraY(world->getCameraY() + 50);
    i->setPlayer(player);
    s->setPlayerObj(player);
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
    world->setCameraY(-360 + 50);
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
    numDeaths = 0;
    numCoins = 0;
    hasWon = false;
    Mix_HaltMusic();
}

void GameState::cleanCurrentLevel() {
    player->setX(50.0);
    player->setY(50.0);
    world->setCameraX(-640.0 + 50);
    world->setCameraY(-360 + 50);
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
    for (CoinObject *co : coins) {
        delete co;
    }
    for (TrampolineObject *t : trampolines) {
        delete t;
    }
    for (EnemyObject *e : enemies) {
        delete e;
    }
    for (TeleportObject *te : teleports) {
        delete te;
    }
    for (DialogueObject *d : dialogues) {
        delete d;
    }
    for (GameObject *o : backgroundObjects) {
        delete o;
    }
    SDL_DestroyTexture(statics);
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
    for (CoinObject *co : coins) {
        delete co;
    }
    for (TrampolineObject *t : trampolines) {
        delete t;
    }
    for (EnemyObject *e : enemies) {
        delete e;
    }
    for (TeleportObject *te : teleports) {
        delete te;
    }
    for (DialogueObject *d : dialogues) {
        delete d;
    }
    for (GameObject *o : backgroundObjects) {
        delete o;
    }
    delete world;
    delete scoreMgr;
    SDL_DestroyTexture(statics);
    SDL_DestroyTexture(background);
}
