#pragma once
#include <memory>
#include "Damage.hpp"
#include "Feature.hpp"

class Trap : public Feature
{
  public:
    Trap();
    virtual ~Trap() {};
    bool operator==(const Trap& trap) const;
    
    Feature* clone() override;

    virtual uchar get_symbol() const override;

    void set_description_sid(const std::string& new_description_sid);

    void set_damage(const Damage& new_damage);
    Damage get_damage() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

    std::string description_sid;
    Damage damage;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Trap> TrapPtr;
