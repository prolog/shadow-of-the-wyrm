#include "Feature.hpp"

class Fountain : public Feature
{
  public:
    Fountain();
    virtual Feature* clone();

    virtual bool handle();
    virtual bool kick();

    virtual uchar get_symbol() const;
    virtual std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};
