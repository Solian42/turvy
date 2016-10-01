#include "../include/GameState.h"

GameState::GameState(SDL_Renderer *r, int width, int height,
                     ResourceManager *res) {

    numEntities = 10;
    renderer = r;
    resources = res;
    entities = std::vector<GameObject *>(10);
    world = new World(numEntities);

    entities[0] = createPlayer(0, {std::string("defaultPlayerSprite")});

    for (int i = 1; i < 10; i++) {
        int randX = std::rand() % width;
        int randY = std::rand() % height;
        entities[i] =
            createEnemy(randX, randY, i, {std::string("defaultEnemySprite")});
    }
    player = (PlayerObject *)entities[0];
    enemies = std::vector<EnemyObject *>(9);
    for (int i = 0; i < 9; i++) {
        enemies[i] = (EnemyObject *)entities[i + 1];
        enemies[i]->input->update(enemies[i]);
    }

    backgroundMusic = std::string("abstract_tracking");
}

void GameState::startMusic() {
    Mix_PlayMusic(resources->getMusic(backgroundMusic), -1);
}

int GameState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_q) {
        return STATE_MAINMENU;
    }

    player->input->update(e, dt);

    return STATE_GAME;
}

void GameState::doSound() { player->sound->update(world); }

void GameState::doPhysics(int dt) {
    player->physics->update(player, world, dt);
    for (int i = 0; i < 9; i++) {
        enemies[i]->physics->update(enemies[i], world, dt);
    }
    world->collision = world->checkCollisions();
}

void GameState::render(int dt) {
    for (int i = 0; i < 9; i++) {
        enemies[i]->graphics->GraphicsComponent::update(renderer, world);
    }
    player->graphics->GraphicsComponent::update(renderer, world);
}

GameState::~GameState() {
    for (GameObject *g : entities) {
        delete g;
    }
    delete world;
}

PlayerObject *GameState::createPlayer(int entityNum,
                                      std::vector<std::string> spriteNames) {
    PlayerInputComponent *i = new PlayerInputComponent();
    PlayerGraphicsComponent *g =
        new PlayerGraphicsComponent(renderer, resources, spriteNames);
    PlayerPhysicsComponent *p = new PlayerPhysicsComponent();
    std::vector<std::string> chunks = {std::string("bonk")};
    PlayerSoundComponent *s = new PlayerSoundComponent(chunks, resources);
    PlayerObject *player = new PlayerObject((world->x / 2), (world->y / 2), 0,
                                            0, i, g, s, p, entityNum);
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
