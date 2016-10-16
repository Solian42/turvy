#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res) {
    // This control difficulty. I have found that 50 is tough, but not
    // impossible.
    // 30 = easy, 40=medium, 50=hard, 60=insane 70=impossible
    XmlParser *parser = new XmlParser();
    numEntities = 1;
    renderer = r;
    resources = res;
    entities = std::vector<GameObject *>(1);
    world = new World(numEntities);

    entities[0] =
        createPlayer(0, {"rps0", "rps1", "rps2", "rps3", "ulps0", "ulps1",
                         "ulps2", "ulps3", "lps0", "lps1", "lps2", "lps3",
                         "urps0", "urps1", "urps2", "urps3"});
    for (std::pair<std::string, SDL_Rect> pair : parser->parsedPlatforms) {
        PlatformGraphicsComponent* g = new PlatformGraphicsComponent(renderer, resources, {pair.first});
        PlatformObject *platform = new PlatformObject(pair.second.x, pair.second.y, pair.second.w, pair.second.h, g);
        platforms.push_back(platform);
    }
    for (std::pair<std::string, std::vector<int>> pair : parser->parsedSpikes) {
        for (int i = 0; i < pair.second[2]; i++) {
            SpikesGraphicsComponent *s = new SpikesGraphicsComponent(renderer, resources, {pair.first});
            SpikesObject * spike = new SpikesObject(pair.second[0], (pair.second[1] + 20 * i), pair.second[3], s);
            spikes.push_back(spike);
        }
        
    }

    player = (PlayerObject *)entities[0];
 

    backgroundObjects = std::vector<GameObject *>(1);


    backgroundObjects[0] = createSetpiece(1280 - (2 * 19), 720 - (2 * 18), {"ts0"});
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
    if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_q) {
        reset();
        return STATE_MAINMENU;
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
    for ( PlatformObject * p : platforms) {
        p->graphics->update(world);
    }
    for (SpikesObject * s : spikes) {
        s->graphics->update(world, s);
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
    PlayerObject *player = new PlayerObject(0, 0, 0, 0, i, g, s, p, entityNum);
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
    player->setX(0.0);
    player->setY(0.0);
    world->setCameraX(-640.0);
    player->setXVel(0.0);
    player->setYVel(0.0);
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
