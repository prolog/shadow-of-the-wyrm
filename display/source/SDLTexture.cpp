#include <iostream>
#include "SDL_image.h"
#include "SDLTexture.hpp"

using namespace std;

SDLTexture::SDLTexture()
{
  //Initialize
  texture = NULL;
  texture_width = 0;
  texture_height = 0;
}

SDLTexture::~SDLTexture()
{
  free();
}

bool SDLTexture::load_from_file(const string& path, SDL_Renderer* renderer)
{
  free();

  if (renderer == nullptr)
  {
    return false;
  }

  SDL_Texture* new_texture = NULL;

  // Load image from path
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == NULL)
  {
    cout << "Unable to load SDL surface " << path << " - error: " << IMG_GetError();
  }
  else
  {
    //Color key image
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

    //Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (new_texture == NULL)
    {
      cout << "Unable to create texture from " << path << " - error: " << SDL_GetError();
    }
    else
    {
      //Get the texture's dimensions
      texture_width = surface->w;
      texture_height = surface->h;
    }

    // Free up the old surface, which we no longer need.
    SDL_FreeSurface(surface);
  }

  //Return success
  texture = new_texture;
  return texture != nullptr;
}

void SDLTexture::free()
{
  if (texture != nullptr)
  {
    SDL_DestroyTexture(texture);
    texture = nullptr;
    texture_width = 0;
    texture_height = 0;
  }
}

void SDLTexture::set_color(Uint8 r, Uint8 g, Uint8 b)
{
  //Modulate texture rgb
  SDL_SetTextureColorMod(texture, r, g, b);
}

void SDLTexture::render(int y, int x, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  //Set rendering space and render to screen
  SDL_Rect render_rect = { x, y, texture_width, texture_height };

  //Set clip rendering dimensions
  if (clip != NULL)
  {
    render_rect.w = clip->w;
    render_rect.h = clip->h;
  }

  //Render to screen
  SDL_RenderCopyEx(renderer, texture, clip, &render_rect, angle, center, flip);
}

int SDLTexture::get_width() const
{
  return texture_width;
}

int SDLTexture::get_height() const
{
  return texture_height;
}
