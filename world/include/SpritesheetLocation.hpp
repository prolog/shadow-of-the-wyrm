#pragma once
#include <string>
#include "common.hpp"
#include "Colours.hpp"
#include "ISerializable.hpp"

class SpritesheetLocation : public ISerializable
{
  public:
    SpritesheetLocation();
    SpritesheetLocation(const std::string& new_index, const int new_rol, const int new_col);
    bool operator==(const SpritesheetLocation& sl) const;

    void set_index(const std::string& new_index);
    std::string get_index() const;

    void set_row(const int new_row);
    int get_row() const;

    void set_col(const int new_col);
    int get_col() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string index;
    int row;
    int col;

  private:
    ClassIdentifier internal_class_identifier() const override;
};