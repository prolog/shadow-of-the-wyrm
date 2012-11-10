#pragma once
#include "ISerializable.hpp"

// Contains information related to the user, version, compiler,
// architecture, and other details that are not actually game data,
// but which need to be checked and serialized.
class Metadata : public ISerializable
{
  public:
    std::string get_user_name() const;
    std::string get_version() const;
    std::string get_code_name() const;
    std::string get_game_version_synopsis() const;
    std::string get_compiler_details() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    ClassIdentifier internal_class_identifier() const;
};

