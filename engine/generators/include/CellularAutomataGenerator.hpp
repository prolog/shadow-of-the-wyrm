#pragma once
#include <vector>
#include <map>
#include "Dimensions.hpp"

class Dimensions;

enum CellValue
{
  CELL_OFF = 0
, CELL_ON  = 1
};

typedef std::vector<std::vector<CellValue> > CellMap; 
//typedef std::map<std::pair<int, int>, CellValue> CellMap;

class CellularAutomataSettings
{
  public:
    CellularAutomataSettings();
    CellularAutomataSettings(const int close_cell, const int iterations, const int neighbour_threshold, const int offset, const CellValue flip_value);

    void set_p_close_cell(const int close_cell);
    int  get_p_close_cell() const;

    void set_iterations(const int iter);
    int  get_iterations() const;

    void set_neighbour_threshold(const int threshold);
    int  get_neighbour_threshold() const;

    void set_seed_p_close_cell(const int threshold);
    int  get_seed_p_close_cell() const;

    void set_flip_value(const CellValue flip_val);
    CellValue get_flip_value() const;

  protected:
    int p_close_cell;
    int iterations;
    int neighbour_threshold;
    int seed_p_close_cell;
    CellValue flip_value;
};

class CellularAutomataGenerator
{
  public:
    CellularAutomataGenerator();
    CellularAutomataGenerator(const CellularAutomataSettings& cas, const Dimensions& dim);

    CellMap generate();

    void set_settings(const CellularAutomataSettings& cas);
    CellularAutomataSettings get_settings() const;

    void set_dimensions(const Dimensions& dim);
    Dimensions get_dimensions() const;

  protected:
    virtual CellMap get_initialized_cells(const int y, const int x);
    virtual int get_number_closed_neighbours(const CellMap& cell_map, const Dimensions& dimensions, const int current_row, const int current_col);

    CellularAutomataSettings cas;
    Dimensions dimensions;

    const int P_CLOSE_CELL;
    const int ITERATIONS;
    const int NEIGHBOUR_THRESHOLD;
    const int SEED_P_CLOSE_CELL;

    const CellValue flip_value;
    CellValue inverse_flip_value;

};
