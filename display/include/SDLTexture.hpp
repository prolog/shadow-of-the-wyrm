#pragma once
#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#include <string>

class SDLTexture
{
  public:
    SDLTexture();
    ~SDLTexture();

    bool load_from_file(const std::string& path, SDL_Renderer* renderer);

    // deallocates texture
    void free();

    //Set color modulation
    void set_color(Uint8 red, Uint8 green, Uint8 blue);

    //Renders texture at given point
    void render(int y, int x, SDL_Renderer* renderer, SDL_Texture* target_texture, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    // image info
    int get_width() const;
    int get_height() const;

  private:
    SDL_Texture* texture;

    //Image dimensions
    int texture_width;
    int texture_height;
};
