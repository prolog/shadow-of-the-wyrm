#pragma once

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include <memory>
#include <string>
#include "SDLDisplayParameters.hpp"
#include "SDLTexture.hpp"

// Renders text on an SDL texture, given a renderer, spritesheet, and 
// location information.
class SDLTextRenderer
{
  public:
    SDLTextRenderer();
    SDLTextRenderer(const SDLDisplayParameters& new_params, SDL_Renderer* new_renderer, const SDLTexture& text_spritesheet, SDL_Texture* new_texture);

    void set_display_parameters(const SDLDisplayParameters& new_display_params);
    SDLDisplayParameters get_display_parameters() const;

    void set_renderer(SDL_Renderer* new_renderer);
    SDL_Renderer* get_renderer();

    void set_text_spritesheet(const SDLTexture& new_text_spritesheet);
    SDLTexture get_text_spritesheet() const;

    void set_texture(SDL_Texture* new_texture);
    SDL_Texture* get_texture();

    void render_text(const int row, const int col, const std::string& text);
    void render_text(const int row, const int col, const char c);

  protected:
    std::pair<int, int> get_glyph_location_from_spritesheet(const char x);

    SDLDisplayParameters display_params;
    SDL_Renderer* renderer;
    SDLTexture text_spritesheet;
    SDL_Texture* texture;
};

using SDLTextRendererPtr = std::shared_ptr<SDLTextRenderer>;