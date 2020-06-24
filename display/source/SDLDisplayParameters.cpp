#include "SDLDisplayParameters.hpp"
#include "SDLUtils.hpp"
#include "Serialize.hpp"

using namespace std;

SDLDisplayParameters::SDLDisplayParameters()
: screen_cols(0)
, screen_rows(0)
, screen_width(0)
, screen_height(0)
, glyph_width(0)
, glyph_height(0)
, glyphs_per_line(0)
, num_glyphs(0)
{
  fg_colour = { 255,255,255,255 }; // white
  bg_colour = { 0,0,0,255 }; // black
}

SDLDisplayParameters::SDLDisplayParameters(const int new_screen_cols, const int new_screen_rows, const int new_screen_width, const int new_screen_height, const int new_glyph_width, const int new_glyph_height, const int new_glyphs_per_line, const int new_num_glyphs)
: screen_cols(new_screen_cols)
, screen_rows(new_screen_rows)
, screen_width(new_screen_width)
, screen_height(new_screen_height)
, glyph_width(new_glyph_width)
, glyph_height(new_glyph_height)
, glyphs_per_line(new_glyphs_per_line)
, num_glyphs(new_num_glyphs)
{
  fg_colour = { 255,255,255,255 }; // white
  bg_colour = { 0,0,0,255 }; // black
}

bool SDLDisplayParameters::operator==(const SDLDisplayParameters& d)
{
  bool eq = true;

  SDLUtils sdl;

  eq = eq && (screen_cols == d.screen_cols);
  eq = eq && (screen_rows == d.screen_rows);
  eq = eq && (screen_width == d.screen_width);
  eq = eq && (screen_height == d.screen_height);
  eq = eq && (glyph_width == d.glyph_width);
  eq = eq && (glyph_height == d.glyph_height);
  eq = eq && (glyphs_per_line == d.glyphs_per_line);
  eq = eq && (num_glyphs == d.num_glyphs);
  eq = eq && (sdl.sdl_color_eq(fg_colour, d.fg_colour));
  eq = eq && (sdl.sdl_color_eq(bg_colour, d.bg_colour));

  return eq;
}

void SDLDisplayParameters::set_screen_cols(const int new_screen_cols)
{
  screen_cols = new_screen_cols;
}

int SDLDisplayParameters::get_screen_cols() const
{
  return screen_cols;
}

void SDLDisplayParameters::set_screen_rows(const int new_screen_rows)
{
  screen_rows = new_screen_rows;
}

int SDLDisplayParameters::get_screen_rows() const
{
  return screen_rows;
}

void SDLDisplayParameters::set_screen_width(const int new_screen_width)
{
  screen_width = new_screen_width;
}

int SDLDisplayParameters::get_screen_width() const
{
  return screen_width;
}

void SDLDisplayParameters::set_screen_height(const int new_screen_height)
{
  screen_height = new_screen_height;
}

int SDLDisplayParameters::get_screen_height() const
{
  return screen_height;
}

void SDLDisplayParameters::set_glyph_width(const int new_glyph_width)
{
  glyph_width = new_glyph_width;
}

int SDLDisplayParameters::get_glyph_width() const
{
  return glyph_width;
}

void SDLDisplayParameters::set_glyph_height(const int new_glyph_height)
{
  glyph_height = new_glyph_height;
}

int SDLDisplayParameters::get_glyph_height() const
{
  return glyph_height;
}

void SDLDisplayParameters::set_glyphs_per_line(const int new_glyphs_per_line)
{
  glyphs_per_line = new_glyphs_per_line;
}

int SDLDisplayParameters::get_glyphs_per_line() const
{
  return glyphs_per_line;
}

void SDLDisplayParameters::set_num_glyphs(const int new_num_glyphs)
{
  num_glyphs = new_num_glyphs;
}

int SDLDisplayParameters::get_num_glyphs() const
{
  return num_glyphs;
}

void SDLDisplayParameters::set_fg_colour(const SDL_Color& new_fg_colour)
{
  fg_colour = new_fg_colour;
}

SDL_Color SDLDisplayParameters::get_fg_colour() const
{
  return fg_colour;
}

void SDLDisplayParameters::set_bg_colour(const SDL_Color& new_bg_colour)
{
  bg_colour = new_bg_colour;
}

SDL_Color SDLDisplayParameters::get_bg_colour() const
{
  return bg_colour;
}

bool SDLDisplayParameters::serialize(std::ostream& stream) const
{
  Serialize::write_int(stream, screen_cols);
  Serialize::write_int(stream, screen_rows);
  Serialize::write_int(stream, screen_width);
  Serialize::write_int(stream, screen_height);
  Serialize::write_int(stream, glyph_width);
  Serialize::write_int(stream, glyph_height);
  Serialize::write_int(stream, glyphs_per_line);
  Serialize::write_int(stream, num_glyphs);

  // Write fg colour
  Serialize::write_sdl_colour(stream, fg_colour);

  // Write bg colour
  Serialize::write_sdl_colour(stream, bg_colour);

  return true;
}

bool SDLDisplayParameters::deserialize(std::istream& stream)
{
  Serialize::read_int(stream, screen_cols);
  Serialize::read_int(stream, screen_rows);
  Serialize::read_int(stream, screen_width);
  Serialize::read_int(stream, screen_height);
  Serialize::read_int(stream, glyph_width);
  Serialize::read_int(stream, glyph_height);
  Serialize::read_int(stream, glyphs_per_line);
  Serialize::read_int(stream, num_glyphs);

  // Read fg colour
  Serialize::read_sdl_colour(stream, fg_colour);

  // Read bg colour
  Serialize::read_sdl_colour(stream, bg_colour);

  return true;
}

ClassIdentifier SDLDisplayParameters::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_DISPLAY_PARAMETERS;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLDisplayParameters_test.cpp"
#endif
