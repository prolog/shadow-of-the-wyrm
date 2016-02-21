#pragma once
#include <map>
#include <vector>
#include "common.hpp"
#include "Generator.hpp"
#include "TileGenerator.hpp"

class SewerGenerator : public SOTW::Generator
{
  public:
    SewerGenerator(const std::string& map_exit_id);
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual MapType get_map_type() const override;

    void generate_sewer_sections(MapPtr result_map, const int y_incr);
    void place_staircases(MapPtr result_map);

    void connect_sewer_sections(MapPtr result_map, const int y_incr);
    void connect_section(MapPtr result_map, const std::pair<bool, std::vector<Coordinate>>& overlap, const int first_row, const int y_incr);
    void increment_connections(std::map<std::pair<Coordinate, Coordinate>, int>& connections_map, const std::pair<Coordinate, Coordinate>& section);
    void create_vertical_connections(MapPtr result_map, std::map<std::pair<Coordinate, Coordinate>, int>& incoming_connections, const int y_incr);
    void connect_unconnected_sections(MapPtr result_map, const std::map<std::pair<Coordinate, Coordinate>, int>& incoming_connections);
    std::pair<Coordinate, Coordinate> retrieve_and_remove_random_section(std::map<int, std::vector<std::pair<Coordinate, Coordinate>>>& sections_copy);

    TileGenerator tg;
    std::map<int, std::vector<std::pair<Coordinate, Coordinate>>> sections;
    static const int MIN_WIDTH, MAX_WIDTH, MIN_HEIGHT, MAX_HEIGHT;
    static const int MIN_Y_INCR, MAX_Y_INCR;
    static const int X_INCR;
};
