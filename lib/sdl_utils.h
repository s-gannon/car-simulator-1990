#include <SDL2/SDL.h>

#ifndef SDL_UTILS_H
#define SDL_UTILS_H

void sdl_init(int flags);
void sdl_cleanup(SDL_Renderer * rend, SDL_Window * win);
void sdl_check_window(SDL_Window * win);
void sdl_check_renderer(SDL_Renderer * rend);
void sdl_check_surface(SDL_Surface * face);

#endif

#ifndef SDL_UTILS_SRC
#define SDL_UTILS_SRC

void std_innit(int flags);



#endif
