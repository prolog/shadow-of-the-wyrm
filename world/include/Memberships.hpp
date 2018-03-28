#pragma once
#include <map>
#include <set>
#include "ISerializable.hpp"

class Membership : public ISerializable
{
  public:
    Membership();
    Membership(const std::string& mem_id, const std::string& description_sid, const std::set<std::string>& excluded_memberships);
    bool operator==(const Membership& m) const;

    bool is_null() const;

    void set_membership_id(const std::string& new_membership_id);
    std::string get_membership_id() const;

    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;

    void add_excluded_membership(const std::string& membership_id);
    void remove_excluded_membership(const std::string& membership_id);
    void set_excluded_memberships(const std::set<std::string>& new_excluded_memberships);
    std::set<std::string> get_excluded_memberships() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    ClassIdentifier internal_class_identifier() const override;

    std::string membership_id;
    std::string description_sid;
    std::set<std::string> excluded_memberships;
};

class Memberships : public ISerializable
{
  public:
    bool operator==(const Memberships& mem) const;

    bool add_membership(const std::string& membership_id, const Membership& m);
    bool remove_membership(const std::string& membership_id);
    bool has_membership(const std::string& membership_id);
    std::map<std::string, Membership> get_memberships() const;
    std::set<std::string> get_excluded_memberships() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    ClassIdentifier internal_class_identifier() const override;

    std::map<std::string, Membership> memberships;
};