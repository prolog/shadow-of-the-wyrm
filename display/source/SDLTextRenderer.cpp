#include "SDLTextRenderer.hpp"

using namespace std;

SDLTextRenderer::SDLTextRenderer()
{
}

SDLTextRenderer::SDLTextRenderer(const SDLDisplayParameters& new_display_params)
: display_params(new_display_params)
{
}

void SDLTextRenderer::set_display_parameters(const SDLDisplayParameters& new_params)
{
  display_params = new_params;
}

SDLDisplayParameters SDLTextRenderer::get_display_parameters() const
{
  return display_params;
}

pair<int, int> SDLTextRenderer::get_glyph_location_from_spritesheet(char x)
{
  int glyphs_per_line = display_params.get_glyphs_per_line();
  return { x / glyphs_per_line, x % glyphs_per_line };
}

void SDLTextRenderer::render_text(SDL_Renderer* renderer, SDLTexture& text_spritesheet, SDL_Texture* texture, const int row, const int col, const string& text)
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

void SDLTextRenderer::render_text(SDL_Renderer* renderer, SDLTexture& text_spritesheet, SDL_Texture* texture, const int row, const int col, const char c)
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

  text_spritesheet.render(render_y, render_x, renderer, texture, &font_clip);
}
