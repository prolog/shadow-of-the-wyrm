#pragma once
#include <map>
#include <string>
#include <memory>
#include "DamageTypes.hpp"
#include "ISerializable.hpp"

inline DamageType operator--(DamageType &dt, int)
{
  return dt = DamageType(dt-1);
}

inline DamageType operator++(DamageType &dt, int)
{
  return dt = DamageType(dt+1);
}

#define DEFAULT_RESISTANCE_VALUE 1.0;
class Resistance : public ISerializable
{
  public:
    Resistance();
    virtual ~Resistance() {};
    Resistance(const DamageType type, const std::string& name_sid, const double value);
    virtual bool operator==(const Resistance& res) const;

    void set_type(const DamageType new_type);
    DamageType get_type() const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;

    void set_value(const double new_value);
    double get_value() const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Resistance* clone() = 0;

  protected:
    DamageType type;
    std::string name_sid;
    double value;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

// Individual resistance types
class SlashResistance : public Resistance
{
  public:
    SlashResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PierceResistance : public Resistance
{
  public:
    PierceResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PoundResistance : public Resistance
{
  public:
    PoundResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HeatResistance : public Resistance
{
  public:
    HeatResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ColdResistance : public Resistance
{
  public:
    ColdResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class AcidResistance : public Resistance
{
  public:
    AcidResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PoisonResistance : public Resistance
{
  public:
    PoisonResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HolyResistance : public Resistance
{
  public:
    HolyResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ShadowResistance : public Resistance
{
  public:
    ShadowResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ArcaneResistance : public Resistance
{
  public:
    ArcaneResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LightningResistance : public Resistance
{
  public:
    LightningResistance();

    virtual Resistance* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::map<DamageType, std::shared_ptr<Resistance>> ResistancesMap;

// Resistance container class
class Resistances : public ISerializable
{
  public:
    Resistances();
    virtual bool operator==(const Resistances& resistances) const;

    void set_resistance_value(const DamageType type, double value);
    double get_resistance_value(const DamageType type) const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
    
  protected:
    void default_resistances();

    ResistancesMap resistances;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
