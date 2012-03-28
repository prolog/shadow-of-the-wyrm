#include "Feature.hpp"

class Fountain : public Feature
{
  public:
    Fountain();

    virtual bool handle();
    virtual bool kick();

    virtual uchar get_symbol() const;
};
