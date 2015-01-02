#pragma once
#include <map>
#include <string>
#include <memory>
#include "DamageTypes.hpp"
#include "ISerializable.hpp"

#define DEFAULT_RESISTANCE_VALUE 1.0;
class Resistance : public ISerializable
{
  public:
    Resistance();
    virtual ~Resistance() {};
    Resistance(const DamageType type, const std::string& name_sid, const std::string& abrv_sid, const std::string& gain_msg_sid, const std::string& lose_msg_sid, const double value);
    virtual bool operator==(const Resistance& res) const;

    void set_type(const DamageType new_type);
    DamageType get_type() const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;

    void set_abrv_sid(const std::string& new_abrv_sid);
    std::string get_abrv_sid() const;

    std::string get_gain_or_lose_message_sid(const bool gained_resistance) const;

    void set_gain_message_sid(const std::string& new_msg_sid);
    std::string get_gain_message_sid() const;

    void set_lose_message_sid(const std::string& new_msg_sid);
    std::string get_lose_message_sid() const;

    void set_value(const double new_value);
    double get_value() const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual Resistance* clone() = 0;

  protected:
    DamageType type;
    std::string name_sid;
    std::string abrv_sid;
    std::string gain_message_sid;
    std::string lose_message_sid;
    double value;

  private:
    virtual ClassIdentifier internal_class_identifier() const = 0;
};

typedef std::shared_ptr<Resistance> ResistancePtr;

// Individual resistance types
class SlashResistance : public Resistance
{
  public:
    SlashResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PierceResistance : public Resistance
{
  public:
    PierceResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PoundResistance : public Resistance
{
  public:
    PoundResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HeatResistance : public Resistance
{
  public:
    HeatResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ColdResistance : public Resistance
{
  public:
    ColdResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class AcidResistance : public Resistance
{
  public:
    AcidResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class PoisonResistance : public Resistance
{
  public:
    PoisonResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HolyResistance : public Resistance
{
  public:
    HolyResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ShadowResistance : public Resistance
{
  public:
    ShadowResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class ArcaneResistance : public Resistance
{
  public:
    ArcaneResistance();

    virtual Resistance* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class LightningResistance : public Resistance
{
  public:
    LightningResistance();

    virtual Resistance* clone() override;

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

    bool has_resistances_or_vulnerabilities() const;

    void set_resistance_value(const DamageType type, double value);
    void set_all_resistances_to(const double new_value);
    ResistancePtr get_resistance(const DamageType dt) const;
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
