#pragma once
#include <string>
#include "CalendarTypes.hpp"
#include "common.hpp"
#include "ISerializable.hpp"

class LoadedMapDetails : public ISerializable
{
  public:
    LoadedMapDetails();
    bool operator==(const LoadedMapDetails& lmd) const;

    void update_map_id(const std::string& new_map_id);
    
    void update_engine_coord(const Coordinate& new_engine_coord);
    
    void update_display_coord(const Coordinate& new_display_coord);
    
    void update_blind_status(const bool new_blind_status);

    void update_season(const Season& new_season);

    // Synchronize the previous and current values
    void synch();

    // Check to see whether a full map redraw is needed, based on the
    // differences between now and the last player turn.
    bool requires_full_map_redraw() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    friend class LoadedMapDetailsTester;

    std::string prev_map_id;
    std::string cur_map_id;

    Coordinate prev_engine_coord;
    Coordinate cur_engine_coord;

    Coordinate prev_display_coord;
    Coordinate cur_display_coord;

    bool prev_blind_status;
    bool cur_blind_status;

    Season prev_season;
    Season cur_season;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

