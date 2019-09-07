#include "SDLDisplayParameters.hpp"
#include "Serialize.hpp"

using namespace std;

SDLDisplayParameters::SDLDisplayParameters()
: screen_cols(0), screen_rows(0), screen_width(0), screen_height(0), glyph_width(0), glyph_height(0), glyphs_per_line(0)
{
}

SDLDisplayParameters::SDLDisplayParameters(const int new_screen_cols, const int new_screen_rows, const int new_screen_width, const int new_screen_height, const int new_glyph_width, const int new_glyph_height, const int new_glyphs_per_line)
: screen_cols(new_screen_cols), screen_rows(new_screen_rows), screen_width(new_screen_width), screen_height(new_screen_height), glyph_width(new_glyph_width), glyph_height(new_glyph_height), glyphs_per_line(new_glyphs_per_line)
{
}

bool SDLDisplayParameters::operator==(const SDLDisplayParameters& d)
{
  bool eq = true;

  eq = eq && (screen_cols == d.screen_cols);
  eq = eq && (screen_rows == d.screen_rows);
  eq = eq && (screen_width == d.screen_width);
  eq = eq && (screen_height == d.screen_height);
  eq = eq && (glyph_width == d.glyph_width);
  eq = eq && (glyph_height == d.glyph_height);
  eq = eq && (glyphs_per_line == d.glyphs_per_line);

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

bool SDLDisplayParameters::serialize(std::ostream& stream) const
{
  Serialize::write_int(stream, screen_cols);
  Serialize::write_int(stream, screen_rows);
  Serialize::write_int(stream, screen_width);
  Serialize::write_int(stream, screen_height);
  Serialize::write_int(stream, glyph_width);
  Serialize::write_int(stream, glyph_height);
  Serialize::write_int(stream, glyphs_per_line);

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

  return true;
}

ClassIdentifier SDLDisplayParameters::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SDL_DISPLAY_PARAMETERS;
}

#ifdef UNIT_TESTS
#include "unit_tests/SDLDisplayParameters_test.cpp"
#endif
