#pragma once
#include "Depth.hpp"
#include "ISerializable.hpp"

#define DEFAULT_DIMENSIONS_Y 20;
#define DEFAULT_DIMENSIONS_X 80;

class Dimensions : public ISerializable
{
  public:
    Dimensions();
    Dimensions(const int new_x, const int new_y);
    bool operator==(const Dimensions& dim) const;

    void set_y(int new_y);
    int  get_y() const;

    void set_x(int new_x);
    int  get_x() const;

    void set_depth(const Depth& new_depth);
    Depth depth() const;
    Depth& depth_ref();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    int y;
    int x;
    Depth dim_depth;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

