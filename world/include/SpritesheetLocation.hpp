#pragma once
#include <string>
#include "common.hpp"
#include "Colours.hpp"
#include "ISerializable.hpp"

class SpritesheetIndex
{
  public:
    static const std::string SPRITESHEET_INDEX_SYSTEM;
    static const std::string SPRITESHEET_INDEX_CREATURE;
    static const std::string SPRITESHEET_INDEX_TERRAIN;

  protected:
    SpritesheetIndex();
    ~SpritesheetIndex();
};

class SpritesheetReference
{
  public:
    static const std::string SPRITESHEET_REFERENCE_MAGIC_BLAST;
    static const std::string SPRITESHEET_REFERENCE_BEAM_NWSE;
    static const std::string SPRITESHEET_REFERENCE_BEAM_NESW;
    static const std::string SPRITESHEET_REFERENCE_BEAM_NS;
    static const std::string SPRITESHEET_REFERENCE_BEAM_EW;
    static const std::string SPRITESHEET_ENTRANCE_OPEN;
    static const std::string SPRITESHEET_ENTRANCE_CLOSED;
    static const std::string SPRITESHEET_ENTRANCE_DESTROYED;
    static const std::string SPRITESHEET_REFERENCE_TREASURE;
    static const std::string SPRITESHEET_REFERENCE_SHIPWRECK;
  
  protected:
    SpritesheetReference();
    ~SpritesheetReference();
};

class SpritesheetLocation : public ISerializable
{
  public:
    explicit SpritesheetLocation();
    explicit SpritesheetLocation(const std::string& new_index, const Coordinate& c);
    explicit SpritesheetLocation(const std::string& new_index, const std::string& new_ref_id);

    bool operator==(const SpritesheetLocation& sl) const;

    void set_index(const std::string& new_index);
    std::string get_index() const;

    void set_reference_id(const std::string& new_reference_id);
    std::string get_reference_id() const;
    bool uses_reference_id() const;

    void set_coordinate(const Coordinate& c);
    Coordinate get_coordinate() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string index;
    std::string reference_id;
    Coordinate coord;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
