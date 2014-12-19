#pragma once
#include <memory>
#include "Feature.hpp"

class Trap : public Feature
{
  public:
    Trap();
    virtual ~Trap() {};
    bool operator==(const Trap& trap) const;
    
    Feature* clone() override;

    virtual uchar get_symbol() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Trap> TrapPtr;
