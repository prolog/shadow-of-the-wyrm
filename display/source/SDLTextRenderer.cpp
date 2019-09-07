#include "SDLTextRenderer.hpp"

using namespace std;

SDLTextRenderer::SDLTextRenderer()
: renderer(nullptr)
{
}

SDLTextRenderer::SDLTextRenderer(const SDLDisplayParameters& new_display_params, SDL_Renderer* new_renderer, const SDLTexture& new_text_spritesheet, SDL_Texture* new_texture)
: display_params(new_display_params), renderer(new_renderer), text_spritesheet(new_text_spritesheet), texture(new_texture)
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

void SDLTextRenderer::set_renderer(SDL_Renderer* new_renderer)
{
  renderer = new_renderer;
}

SDL_Renderer* SDLTextRenderer::get_renderer()
{
  return renderer;
}

void SDLTextRenderer::set_text_spritesheet(const SDLTexture& new_text_spritesheet)
{
  text_spritesheet = new_text_spritesheet;
}

SDLTexture SDLTextRenderer::get_text_spritesheet() const
{
  return text_spritesheet;
}

void SDLTextRenderer::set_texture(SDL_Texture* new_texture)
{
  texture = new_texture;
}

SDL_Texture* SDLTextRenderer::get_texture()
{
  return texture;
}

pair<int, int> SDLTextRenderer::get_glyph_location_from_spritesheet(char x)
{
  int glyphs_per_line = display_params.get_glyphs_per_line();
  return { x / glyphs_per_line, x % glyphs_per_line };
}

void SDLTextRenderer::render_text(const int row, const int col, const string& text)
{
  if (renderer != nullptr)
  {
    for (size_t i = 0; i < text.size(); i++)
    {
      render_text(row, col, text[i]);
    }
  }
}

void SDLTextRenderer::render_text(const int row, const int col, const char c)
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
