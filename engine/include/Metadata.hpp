#pragma once
#include "ISerializable.hpp"
#include "Creature.hpp"

// Contains information related to the user, version, compiler,
// architecture, and other details that are not actually game data,
// but which need to be checked and serialized.
class Metadata : public ISerializable
{
  public:
    Metadata();
    Metadata(CreaturePtr player);
    bool operator==(const Metadata& meta) const;

    std::string get_user_name() const;
    std::string get_version() const;
    std::string get_code_name() const;
    std::string get_game_version_synopsis() const;
    std::string get_full_game_version_details() const; // includes compilation details

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    ClassIdentifier internal_class_identifier() const override;

    CreaturePtr player;
};

