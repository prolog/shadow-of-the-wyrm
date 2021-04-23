#pragma once
#ifdef ENABLE_SDL

#include "sdl.hpp"

#include <memory>
#include <string>
#include "SDLCursorLocation.hpp"
#include "SDLDisplayParameters.hpp"

// Renders text on an SDL texture, given a renderer, spritesheet, and 
// location information.
class SDLRender
{
  public:
    SDLRender(const SDLDisplayParameters& new_params);

    void set_display_parameters(const SDLDisplayParameters& new_display_params);
    SDLDisplayParameters get_display_parameters() const;

    void fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, const SDL_Color& colour);
    void fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, SDL_Rect* dst_rect, const SDL_Color& colour);
    void render_spritesheet(int y, int x, SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet_texture, SDL_Texture* target_texture, SDL_Rect* clip, SDL_Rect* dst_rect, const SDL_Color& colour);
    void render_text(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const std::string& text, const SDL_Color& fg, const SDL_Color& bg);
    void render_text(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const char c, const SDL_Color& fg, const SDL_Color& bg);
    void render_glyph(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const int spritesheet_y, const int spritesheet_x, const SDL_Color& fg, const SDL_Color& bg);

  protected:
    std::pair<int, int> get_glyph_location_from_spritesheet(const unsigned char x);
    void draw_glyph(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const std::pair<int, int>& ss_coords, const int col, const int row, const SDL_Color& fg, const SDL_Color& bg);

    SDLDisplayParameters display_params;
};

#endif
