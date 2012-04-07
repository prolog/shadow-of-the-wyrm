#include "Feature.hpp"

class FirePillar : public Feature
{
  public:
    FirePillar();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_blocking() const;

    virtual uchar get_symbol() const;
    virtual std::string get_description_sid() const;
};
