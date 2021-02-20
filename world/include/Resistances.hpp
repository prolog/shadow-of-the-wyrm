#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include "DamageTypes.hpp"
#include "ISerializable.hpp"

constexpr auto DEFAULT_RESISTANCE_VALUE = 1.0;

class Resistance : public ISerializable
{
  public:
    Resistance();
    
    Resistance(const DamageType type, const std::string& name_sid, const std::string& abrv_sid, const std::string& gain_msg_sid, const std::string& lose_msg_sid, const double value);
    bool operator==(const Resistance& r) const;

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

    // Get a 2-precision, fixed value for the resistance.
    std::string get_value_str() const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    DamageType type;
    std::string name_sid;
    std::string abrv_sid;
    std::string gain_message_sid;
    std::string lose_message_sid;
    double value;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

using ResistancesMap = std::map<DamageType, Resistance>;

// Resistance container class
class Resistances : public ISerializable
{
  public:
    Resistances();
    Resistances(const Resistances& r);
    bool operator==(const Resistances& r) const;

    void clear();

    // Add the values from the given resistances to the current set of resistances.
    void add(const Resistances& res);

    bool has_resistances_or_vulnerabilities() const;
    double get_total() const;

    void set_resistance_value(const DamageType type, double value);
    void set_all_resistances_to(const double new_value);
    const Resistance& get_resistance_cref(const DamageType dt) const;
    Resistance& get_resistance_ref(const DamageType dt);
    double get_resistance_value(const DamageType type) const;
    ResistancesMap get_resistances_map() const;

    std::string str() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;
    
  protected:
    ResistancesMap resistances;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
