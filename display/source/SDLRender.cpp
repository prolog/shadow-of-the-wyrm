#include "SDLRender.hpp"

using namespace std;

SDLRender::SDLRender()
{
}

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

pair<int, int> SDLRender::get_glyph_location_from_spritesheet(char x)
{
  int glyphs_per_line = display_params.get_glyphs_per_line();
  return { x / glyphs_per_line, x % glyphs_per_line };
}

void SDLRender::render_spritesheet(int y, int x, SDL_Renderer* renderer, SDL_Texture* spritesheet_texture, SDL_Texture* target_texture, SDL_Rect* clip, SDL_Rect* dst_rect)
{
  SDL_SetRenderTarget(renderer, target_texture);
  SDL_RenderCopy(renderer, spritesheet_texture, clip, dst_rect);
}

void SDLRender::render_text(SDL_Renderer* renderer, SDL_Texture* text_spritesheet, SDL_Texture* texture, const int row, const int col, const string& text)
{
  int rcol = col;

  if (renderer != nullptr)
  {
    for (size_t i = 0; i < text.size(); i++)
    {
      render_text(renderer, text_spritesheet, texture, row, rcol, text[i]);
      rcol++;
    }
  }
}

void SDLRender::render_text(SDL_Renderer* renderer, SDL_Texture* text_spritesheet, SDL_Texture* texture, const int row, const int col, const char c)
{
  SDL_Rect font_clip;
  int glyph_height = display_params.get_glyph_height();
  int glyph_width = display_params.get_glyph_width();

  // Look up the letter
  std::pair<int, int> ss_coords = get_glyph_location_from_spritesheet(c);

  // Set the proper coords
  font_clip.y = ss_coords.first * glyph_height;
  font_clip.x = ss_coords.second * glyph_width;
  font_clip.w = glyph_width;
  font_clip.h = glyph_height;

  int render_x = col * glyph_width;
  int render_y = row * glyph_height;

  SDL_Rect dst_rect = {0, 0, 0, 0};

  dst_rect.y = row * glyph_height;
  dst_rect.x = col * glyph_width;
  dst_rect.h = font_clip.h;
  dst_rect.w = font_clip.w;

  // Clear out what was in the text's area before
  fill_area(renderer, texture, &dst_rect);

  // Render the text.
  render_spritesheet(render_y, render_x, renderer, text_spritesheet, texture, &font_clip, &dst_rect);
}

void SDLRender::fill_area(SDL_Renderer* renderer, SDL_Texture* target_texture, SDL_Rect* dst_rect)
{
  SDL_SetRenderTarget(renderer, target_texture);
  SDL_RenderFillRect(renderer, dst_rect);
}