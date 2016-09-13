//
//  main.cpp
//  Game
//
//  Created by Tristan Orton-Urbina on 9/7/16.
//  Copyright © 2016 Tristan. All rights reserved.
//

/*Very simple SDL demo in C++
 *
 * Made by Tristan Orton-Urbina tortonu1 for
 * 600.255 FA 2016
 *
 *
 */


int center(int large, int small) {
    return (large /2 - small / 2);
}

SDL_Rect * centeredRect(int largeW, int largeH, int smallW, int smallH) {
    SDL_Rect centered;
    centered.x = center(largeW, smallW);
    centered.y = center(largeH, largeW);
    centered.w = smallW;
    centered.h = smallH;
    std::cout<< centered.x << centered.y << centered.w << centered.h;
    return  &centered;
}

double tweak(double t) {
    return 1 + sin(t)*.1;
}

double radToDegs(double r) {
    return r * radToDeg;
}

void textureSize(SDL_Texture * t, int* w, int* h) {
    std::cout<< SDL_QueryTexture(t, NULL, NULL, w, h) << "\n";
    return;
}

void setup() {
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    
    if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 ) {
        std::cerr<<"SDL_mixer could not initialize! SDL_mixer Error:"<< Mix_GetError() << "\n";
    }
    
    TTF_Init();
    
    gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    
    return;
}

void load() {
    gMusic = Mix_LoadMUS("abstract_tracking.wav");
    
    SDL_Surface * image = IMG_Load("johns-hopkins-university-logo.png");
    if(!image) {
        printf("IMG_Load: %s\n", IMG_GetError());
        // handle error
    }
    
    gTexture = SDL_CreateTextureFromSurface(gRenderer, image);
    std::cout<< SDL_GetError() <<"\n";
    gFont = TTF_OpenFont("CaesarDressing-Regular.ttf", 72);
    
    gFont2 = TTF_OpenFont("CaesarDressing-Regular.ttf", 74);
    
    return;
}

void cleanup() {
    TTF_CloseFont(gFont2);
    TTF_CloseFont(gFont);
    Mix_FreeMusic(gMusic);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void run() {
    SDL_Event event;
    bool running = true;
    int lastTime = 0;
    int currentTime;
    double time = 0.0;
    SDL_Color white = {255,255,255,255};
    SDL_Surface* text = TTF_RenderUTF8_Blended(gFont, title, white);
    SDL_Texture* textex =  SDL_CreateTextureFromSurface(gRenderer, text);
    SDL_Color black ={0,0,0,255};
    SDL_Surface* shadow = TTF_RenderUTF8_Blended(gFont2, title, black);
    SDL_SetSurfaceAlphaMod(shadow, 128);
    SDL_Texture* shadowex =  SDL_CreateTextureFromSurface(gRenderer, shadow);
    int textureW;
    int textureH;
    textureSize(gTexture, &textureW, &textureH);
    SDL_Rect * textureRect = centeredRect(width, height, textureW, textureH);
    SDL_Rect * shadowRect = centeredRect(width, height, shadow->w, shadow->h);
    SDL_Rect * textRect = centeredRect(width, height, text->w, text->h);
    
    while(running) {
        currentTime = SDL_GetTicks();
        int dt = currentTime - lastTime;
        time = (double) dt / 1000.00;
        lastTime = currentTime;
        
        if( time > twoPi) {
            time -= twoPi;
        }
        
        for( SDL_PollEvent(&event); &event != NULL; SDL_PollEvent(&event)) {
            switch(event.type) {
                    
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
            }
            
        }
        
        std::cout << "Halp\n";
        SDL_RenderClear(gRenderer);
        SDL_RenderCopyEx(gRenderer, gTexture, NULL, textureRect, radToDegs(sin(time)), NULL, SDL_FLIP_NONE);
        SDL_RenderCopy(gRenderer, shadowex, NULL, shadowRect);
        SDL_RenderCopy(gRenderer, textex, textRect, NULL);
        SDL_RenderPresent(gRenderer);
        
    }
    
    return;
}

int main() {
    std::cout << "Starting Setup\n";
    setup();
    std::cout << "Starting loading\n";
    load();
    std::cout << "Starting music\n";
    Mix_PlayMusic(gMusic, -1);
    std::cout << "Starting running\n";
    run();
    std::cout << "Starting done\n";
    
    cleanup();
    
    return 0;
}
