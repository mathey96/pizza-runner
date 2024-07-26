#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#include "./stb_image.h"
// TODO: add config file reading
// TODO: usage function  and command line parsing
// TODO: add an icecream cursor
// TODO: SHOWER ORC WITH PIZZA
// TODO: dynamically resize cursor

#define TOTAL_FRAMES 40
#define FRAME_COLS 10
#define FRAME_ROWS 4
#define FRAME_WIDTH 400
#define FRAME_HEIGHT 160


typedef struct {
  SDL_Texture *spritesheet;
  SDL_Rect glyph_table[TOTAL_FRAMES];
} frame;

void *secp(void *ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "SDL pooped itself: %s\n", SDL_GetError());
        abort();
    }

return ptr;
}

void secc(int code)
{
  if (code < 0) {
    fprintf(stderr, "SDL pooped itself: %s\n", SDL_GetError());
    abort();
  }
}

void scc(int code)
{
  if(code < 0){
    fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    exit(1);
  }
}

void *scp(void *ptr)
{
  if (ptr == NULL) {
    fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    exit(1);
    }

    return ptr;
}

SDL_Surface *surface_from_file(const char *file_path)
{
  int width, height, n;
  unsigned char *pixels = stbi_load(file_path, &width, &height, &n, STBI_rgb_alpha);
  if (pixels == NULL) {
    exit(1);
  }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  const Uint32 rmask = 0xff000000;
  const Uint32 gmask = 0x00ff0000;
  const Uint32 bmask = 0x0000ff00;
  const Uint32 amask = 0x000000ff;
#else // little endian, like x86
  const Uint32 rmask = 0x000000ff;
  const Uint32 gmask = 0x0000ff00;
  const Uint32 bmask = 0x00ff0000;
  const Uint32 amask = 0xff000000;
#endif

  const int depth = 32;
  const int pitch = 4*width;

  return scp(SDL_CreateRGBSurfaceFrom(
                                      (void*)pixels, width, height, depth, pitch,
                                      rmask, gmask, bmask, amask));
}

frame frame_load_from_file(SDL_Renderer *renderer, const char *file_path)
{
  frame font = {0};

  SDL_Surface *font_surface = surface_from_file(file_path);
  scc(SDL_SetColorKey(font_surface, SDL_TRUE, 0xFF000000));
  font.spritesheet = scp((renderer, font_surface));
  SDL_FreeSurface(font_surface);

  for (size_t frame_index = 0; frame_index < TOTAL_FRAMES; ++frame_index) {
    const size_t col = frame_index % FRAME_COLS;
    const size_t row = frame_index / FRAME_COLS;
    font.glyph_table[frame_index] = (SDL_Rect) {
      .x = col * FRAME_WIDTH,
      .y = row * FRAME_HEIGHT,
      .w = FRAME_WIDTH,
      .h = FRAME_HEIGHT,
    };
  }

  return font;
}


int main(){

  secc(SDL_Init(SDL_INIT_VIDEO));
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
    secp(SDL_CreateWindow(
                          "kindest sweetest runner",
                          0, 0, 1000, 1000,
                          SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer =
      secp(SDL_CreateRenderer(
                              window, -1,
                              SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));
    SDL_DisplayMode dm;

    frame i =  frame_load_from_file(renderer, "./animation.jpeg");
    SDL_Surface* surface = surface_from_file("./animation.jpeg");
    SDL_Texture* texture = scp(SDL_CreateTextureFromSurface(renderer, surface));

    SDL_Rect imgPartRect[TOTAL_FRAMES];
    int increment = 0;
    for(int index=0;index<40;index++){
		const size_t col = index  % FRAME_COLS; //+ 1;
		const size_t row = index  / FRAME_COLS; //+ 1;
        imgPartRect[index].x = 0 + (400 * col);
        imgPartRect[index].y = 0 + (400 * row);
        imgPartRect[index].w = FRAME_WIDTH;
        imgPartRect[index].h = FRAME_WIDTH;
    }

    //    SDL_RenderDrawRect(renderer, &i.glyph_table[30]);

    SDL_Event event = {0};
    int quit = 0;
    int pause = 0;
    int current_frame = 0;


	//cursor
	int run_from_pizza = 0;
    SDL_Surface* cursorSurface = SDL_LoadBMP("pizzaslice2.bmp");
    SDL_Surface* cursorSurfaceIcecream = SDL_LoadBMP("pizzaslice2.bmp");
	SDL_Surface* newcursorSurface = SDL_CreateRGBSurface(0, 256, 322, 0, 0, 0, 0, 0);
	SDL_BlitSurface(newcursorSurface, NULL, cursorSurface, NULL);
	SDL_Cursor* cursor2 = SDL_CreateColorCursor(newcursorSurface, 0, 0);
    //SDL_Surface* newcursorSurface = SDL_CreateRGBSurface(0, 256, 332, 32, 0, 0, 0, 0);
    if (cursorSurface == NULL) {
        fprintf(stderr, "Failed to load cursor image! SDL_Error: %s " ,SDL_GetError());
        return 1;
    }

    // Create a cursor from the surface
    SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    if (cursor == NULL ) {
        fprintf(stderr, "Failed to create cursor! SDL_Error: %s ", SDL_GetError());
        SDL_FreeSurface(cursorSurface);
        return 1;
    }

    // Set the created cursor as the active cursor for the window
    SDL_SetCursor(cursor);

    while (!quit){

		//    if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
		//        fprintf(stderr,"SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
		//        return 1;
		//    }

		//	fprintf(stderr,"ovo su vrednosti pozicija: %d, %d \n",wWidth,wHeight);

        if (current_frame >= 39)
            current_frame = 0;
        while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				quit = 1;
			} break;
			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
				case SDLK_q: {
					quit=1;
				} break;
				case SDLK_SPACE: {
					if (pause == 0)
						pause = 1;
					else
						pause = 0;
				} break;
				case SDLK_c: {
					SDL_SetCursor(NULL);
					SDL_SetCursor(cursor2);
				} break;
				case SDLK_r: {
					if (run_from_pizza == 0) run_from_pizza = 1;
					else run_from_pizza = 0;
				} break;
				}
			} break;
            }
        }

		int wWidth, wHeight;
		int xMouse, yMouse;
		SDL_GetWindowSize(window, &wWidth, &wHeight);
		SDL_GetMouseState(&xMouse,&yMouse);
		switch(run_from_pizza ){
		case 0:
			{
				if(xMouse - wWidth/2 < 0 ){
					SDL_RenderCopyEx(renderer,
									texture,
									&imgPartRect[current_frame],
									NULL,
									0,
									NULL,
									SDL_FLIP_NONE);
				}
				else {
					SDL_RenderCopyEx(renderer,
									texture,
									&imgPartRect[current_frame],
									NULL,
									0,
									NULL,
									SDL_FLIP_HORIZONTAL);
				} ;
			} break;
		case 1: // fallthrough
		default:
			{
				if(xMouse - wWidth/2 >= 0 ){
					SDL_RenderCopyEx(renderer,
									texture,
									&imgPartRect[current_frame],
									NULL,
									0,
									NULL,
									SDL_FLIP_NONE);
				}
				else {
					SDL_RenderCopyEx(renderer,
									texture,
									&imgPartRect[current_frame],
									NULL,
									0,
									NULL,
									SDL_FLIP_HORIZONTAL);
				} ;
		} break;
	}


        if (pause == 0){
			//    SDL_RenderCopy(renderer, texture , &imgPartRect[current_frame], NULL);
            SDL_RenderPresent(renderer);
            current_frame++;
        }
		else {

				SDL_RenderPresent(renderer);
			}
    }
	// TODO:close sdl window and clean other stuff
}

