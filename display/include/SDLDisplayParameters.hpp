#pragma once
#include "ISerializable.hpp"

class SDLDisplayParameters : public ISerializable
{
  public:
    SDLDisplayParameters();
    SDLDisplayParameters(const int new_screen_cols, const int new_screen_rows, const int new_screen_width, const int new_screen_height, const int new_glyph_width, const int new_glyph_height, const int new_glyphs_per_line);
    bool operator==(const SDLDisplayParameters& d);

    void set_screen_cols(const int new_screen_cols);
    int get_screen_cols() const;

    void set_screen_rows(const int new_screen_rows);
    int get_screen_rows() const;

    void set_screen_width(const int new_screen_width);
    int get_screen_width() const;

    void set_screen_height(const int new_screen_height);
    int get_screen_height() const;

    void set_glyph_width(const int new_glyph_width);
    int get_glyph_width() const;

    void set_glyph_height(const int new_glyph_height);
    int get_glyph_height() const;

    void set_glyphs_per_line(const int new_glyphs_per_line);
    int get_glyphs_per_line() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

protected:
    int screen_cols; // text rows
    int screen_rows; 
    int screen_width; // pixels
    int screen_height;
    int glyph_width; // pixels again
    int glyph_height;
    int glyphs_per_line; // per line in the .png texture

  private:
    ClassIdentifier internal_class_identifier() const;
};