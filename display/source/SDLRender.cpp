#ifdef ENABLE_SDL
#include "SDLRender.hpp"

using namespace std;

SDLRender::SDLRender(const SDLDisplayParameters& new_display_params)
: display_params(new_display_params)
{
}

void SDLRender::set_display_parameters(const SDLDisplayParameters& new_params)
{
  display_params = new_params;
}

SDLDisplayParameters SDLRender::get_display_parameters() const
{
  return display_params;
}

pair<int, int> SDLRender::get_glyph_location_from_spritesheet(const unsigned char x)
{
  int glyphs_per_line = display_params.get_glyphs_per_line();
  return { x / glyphs_per_line, x % glyphs_per_line };
}

void SDLRender::render_spritesheet(SDL_Renderer* renderer, SDL_Texture* spritesheet_texture, SDL_Texture* target_texture, SDL_Rect* clip, SDL_Rect* dst_rect, const SDL_Color& color)
{
  SDL_SetRenderTarget(renderer, target_texture);
  SDL_SetTextureColorMod(spritesheet_texture, color.r, color.g, color.b);
  SDL_RenderCopy(renderer, spritesheet_texture, clip, dst_rect);  
}

void SDLRender::render_text(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* text_spritesheet, SDL_Texture* texture, const int row, const int col, const string& text, const SDL_Color& fg, const SDL_Color& bg)
{
  int rcol = col;

  if (renderer != nullptr)
  {
    for (size_t i = 0; i < text.size(); i++)
    {
      render_text(cursor_location, renderer, text_spritesheet, texture, row, rcol, text[i], fg, bg);
      rcol++;
    }
  }
}

void SDLRender::render_text(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* text_spritesheet, SDL_Texture* texture, const int row, const int col, const char c, const SDL_Color& fg, const SDL_Color& bg)
{
  unsigned char uc = static_cast<unsigned char>(c);

  // Look up the letter
  if (uc > display_params.get_num_glyphs())
  {
    uc = '?';
  }

  std::pair<int, int> ss_coords = get_glyph_location_from_spritesheet(uc);
  draw_glyph(cursor_location, renderer, text_spritesheet, texture, ss_coords, col, row, fg, bg);
}

void SDLRender::render_glyph(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const int row, const int col, const int spritesheet_y, const int spritesheet_x, const SDL_Color& fg, const SDL_Color& bg)
{
  draw_glyph(cursor_location, renderer, spritesheet, texture, make_pair(spritesheet_y, spritesheet_x), col, row, fg, bg);
}

void SDLRender::draw_glyph(SDLCursorLocation& cursor_location, SDL_Renderer* renderer, SDL_Texture* spritesheet, SDL_Texture* texture, const pair<int, int>& ss_coords, const int col, const int row, const SDL_Color& fg, const SDL_Color& bg)
{
  SDL_Rect font_clip;
  int glyph_height = display_params.get_glyph_height();
  int glyph_width = display_params.get_glyph_width();

  // Set the proper coords
  font_clip.y = ss_coords.first * glyph_height;
  font_clip.x = ss_coords.second * glyph_width;
  font_clip.w = glyph_width;
  font_clip.h = glyph_height;

  SDL_Rect dst_rect = { 0, 0, 0, 0 };

  dst_rect.y = row * glyph_height;
  dst_rect.x = col * glyph_width;
  dst_rect.h = font_clip.h;
  dst_rect.w = font_clip.w;

  // Clear out what was in the text's area before
  fill_area(renderer, texture, &dst_rect, bg);

  cursor_location.set_y(row);
  cursor_location.set_x(col);
  cursor_location.incr();

  // Render the text.
  render_spritesheet(renderer, spritesheet, texture, &font_clip, &dst_rect, fg);
}

// Fills an entire texture based on the SDL display parameters.
void SDLRender::fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, const SDL_Color& colour)
{
  fill_area(renderer, target_texture, NULL, colour);
}

void SDLRender::fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, SDL_Rect* dst_rect, const SDL_Color& colour)
{
  SDL_SetRenderTarget(renderer, target_texture);
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderFillRect(renderer, dst_rect);

  if (false)
  {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, target_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

#endif