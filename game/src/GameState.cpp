#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res) {

    numEntities = 30;
    renderer = r;
    resources = res;
    entities = std::vector<GameObject *>(numEntities);
    world = new World(numEntities);

    entities[0] =
        createPlayer(0, {"rps0", "rps1", "rps2", "rps3", "ulps0", "ulps1",
                         "ulps2", "ulps3", "lps0", "lps1", "lps2", "lps3",
                         "urps0", "urps1", "urps2", "urps3"});

    for (int i = 1; i < numEntities; i++) {
        int randX = (std::rand() % (width - 240)) + 120;
        int randY = (std::rand() % (height - 144)) + 72;
        entities[i] = createEnemy(randX, randY, i,
                                  {"es1", "es2", "es3", "es4", "es3", "es2"});
    }
    player = (PlayerObject *)entities[0];
    enemies = std::vector<EnemyObject *>(numEntities - 1);
    for (int i = 0; i < numEntities - 1; i++) {
        enemies[i] = (EnemyObject *)entities[i + 1];
        enemies[i]->input->update(enemies[i]);
    }

    backgroundMusic = std::string("treadmill");
    scoreMgr = new ScoreManager(renderer, resources, world);    /*added score manager by Anthony*/
}

void GameState::startMusic() {
    Mix_PlayMusic(resources->getMusic(backgroundMusic), -1);
}

int GameState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_q) {
        return STATE_MAINMENU;
    }

    player->input->update(e, dt);

    return getMyState();
}

void GameState::doSound() { player->sound->update(world); }

void GameState::doPhysics(int dt) {
    player->physics->update(player, world, dt);
    for (int i = 0; i < numEntities - 1; i++) {
        enemies[i]->physics->update(enemies[i], world, dt);
    }
    world->collision = world->checkCollisions();
}

void GameState::render(int dt) {
    for (int i = 0; i < numEntities - 1; i++) {
        enemies[i]->graphics->update(renderer, world, dt);
    }
    player->graphics->update(renderer, world, dt);
    scoreMgr->update();
    scoreMgr->printScore(500, 0);                              /*added printscore upon width&height of screen*/
}

GameState::~GameState() {
    for (GameObject *g : entities) {
        delete g;
    }
    delete world;
    delete scoreMgr;
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
EnemyObject *GameState::createEnemy(int x, int y, int entityNum,
                                    std::vector<std::string> spriteNames) {
    EnemyInputComponent *i = new EnemyInputComponent();
    EnemyGraphicsComponent *g =
        new EnemyGraphicsComponent(renderer, resources, spriteNames);
    EnemyPhysicsComponent *p = new EnemyPhysicsComponent();
    EnemyObject *e = new EnemyObject(x, y, 0, 0, i, g, p, entityNum);
    return e;
}
