#pragma once

#ifdef _MSC_VER
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

#include <memory>
#include <string>
#include "SDLDisplayParameters.hpp"

// Renders text on an SDL texture, given a renderer, spritesheet, and 
// location information.
class SDLRender
{
  public:
    SDLRender(const SDLDisplayParameters& new_params);

    void set_display_parameters(const SDLDisplayParameters& new_display_params);
    SDLDisplayParameters get_display_parameters() const;

    void fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, SDL_Rect* dst_rect);
    void render_spritesheet(int y, int x, SDL_Renderer* renderer, SDL_Texture* spritesheet_texture, SDL_Texture* target_texture, SDL_Rect* clip, SDL_Rect* dst_rect);
    void render_text(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const std::string& text);
    void render_text(SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const char c);
    
  protected:
    std::pair<int, int> get_glyph_location_from_spritesheet(const char x);

    SDLDisplayParameters display_params;
};

using SDLRenderPtr = std::shared_ptr<SDLRender>;
