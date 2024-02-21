// System includes
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef DEBUG_STATEMENTS
#include <unistd.h>
#endif
// SDL2 includes
#include <SDL2/SDL.h>
// Macros
#define GB_HEIGHT 144
#define GB_WIDTH  160
#define SCREEN_INT_SCALE 3
#define FRAMES_PER_SECOND 30.00
// Functions
void init_sdl(int flags){
	if(SDL_Init(flags)){ // if SDL_Init returns non-zero, run 
        printf("[ERROR] SDL_Init: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void cleanup_sdl(SDL_Renderer * render, SDL_Window * win){
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
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
        printf("[ERROR] SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void check_sdl_surface(SDL_Surface * face, SDL_Renderer * rend, SDL_Window * win){
    if(!face){
        printf("[ERROR] SDL_Surface: %s\n", SDL_GetError());
        cleanup_sdl(rend, win);
        exit(EXIT_FAILURE);
    }
}

uint8_t * get_keyboard_state(void){
    SDL_PumpEvents();
    return SDL_GetKeyboardState(NULL);
}

int main(void){
    uint8_t * curr_keyboard_state = NULL;
    uint8_t * prev_keyboard_state = NULL;

    init_sdl(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SDL_Window * window = SDL_CreateWindow(
        "Car Simulator 1990",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GB_WIDTH * SCREEN_INT_SCALE, GB_HEIGHT * SCREEN_INT_SCALE,
        SDL_WINDOW_SHOWN
    );

    check_sdl_window(window);

    SDL_Renderer * renderer = SDL_CreateRenderer(
        window,
        -1,
        (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );

    check_sdl_renderer(renderer, window);
    
    SDL_Event event;
    int quit = 0;
    int frames = 0;

    int game_start = clock();
    do{
        clock_t frame_start = clock();

        do{ // This *should* be a single frame
            printf("Frame %d\n", ++frames);
            #ifdef DEBUG_STATEMENTS
            printf("Total time elapsed: %.2f\n", (clock() - game_start) / 1000.00);
            #endif
        } while((clock() - frame_start) / 1000 < (1000 / FRAMES_PER_SECOND));
        #ifdef DEBUG_STATEMENTS
        if((clock() - game_start) >= 30000)
            quit = 1;
        #endif
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = 1;
                    break;
                default:
                    break;
            }
        }
        // TODO: game loop
    } while(!quit);

    cleanup_sdl(renderer, window);

    return EXIT_SUCCESS;
}

