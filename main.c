#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void init_sdl(){
	if(SDL_Init(SDL_INIT_VIDEO)){ // if SDL_Init returns non-zero or != 0
        printf("[ERROR] SDL_Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void check_sdl_window(SDL_Window * win){
    if(!win){
        printf("[ERROR] SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void check_sdl_renderer(SDL_Renderer * render, SDL_Window * win){
    if(!render){
        SDL_DestroyWindow(win);
        printf("[ERROR] SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void cleanup_sdl(SDL_Renderer * render, SDL_Window * win){
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

int main(){
	SDL_Window * window = SDL_CreateWindow(
        "Keyboard Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_SHOWN
    );

    check_sdl_window(window);

    SDL_Renderer * renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    check_sdl_renderer(renderer, window);

    SDL_Event event;
    int quit = 0;
    while(!quit){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym = SDLK_SPACE)
                        printf("Space bar was pressed\n");
                    break;
                case SDL_KEYUP:
                    if(event.key.keysym.sym == SDLK_SPACE)
                        printf("Space bar was released\n");
                    break;
                default:
                    break;
            }
        }
    }

    cleanup_sdl(renderer, window);

    return EXIT_SUCCESS;
}

