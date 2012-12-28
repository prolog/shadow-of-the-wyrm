#include "CellularAutomataGenerator.hpp"
#include "CoordUtils.hpp"
#include "RNG.hpp"

using namespace std;

// CELLULAR AUTOMATA SETTINGS

CellularAutomataSettings::CellularAutomataSettings()
: p_close_cell(0)
, iterations(0)
, neighbour_threshold(0)
, seed_p_close_cell(0)
, flip_value(CELL_OFF)
{
}

CellularAutomataSettings::CellularAutomataSettings
(
  const int close_cell_probability
, const int number_of_iterations
, const int threshold
, const int seed_p
, const CellValue flip_val
)
: p_close_cell(close_cell_probability)
, iterations(number_of_iterations)
, neighbour_threshold(threshold)
, seed_p_close_cell(seed_p)
, flip_value(flip_val)
{
}

// This is expected as a percentage, not a normalized value, so 50% would be passed as 50.
void CellularAutomataSettings::set_p_close_cell(const int close_cell)
{
  p_close_cell = close_cell;
}

int CellularAutomataSettings::get_p_close_cell() const
{
  return p_close_cell;
}

void CellularAutomataSettings::set_iterations(const int iter)
{
  iterations = iter;
}

int CellularAutomataSettings::get_iterations() const
{
  return iterations;
}

void CellularAutomataSettings::set_neighbour_threshold(const int threshold)
{
  neighbour_threshold = threshold;
}

int CellularAutomataSettings::get_neighbour_threshold() const
{
  return neighbour_threshold;
}

void CellularAutomataSettings::set_seed_p_close_cell(const int seed_run_close_cell)
{
  seed_p_close_cell = seed_run_close_cell;
}

int CellularAutomataSettings::get_seed_p_close_cell() const
{
  return seed_p_close_cell;
}

void CellularAutomataSettings::set_flip_value(const CellValue flip_val)
{
  flip_value = flip_val;
}

CellValue CellularAutomataSettings::get_flip_value() const
{
  return flip_value;
}

// CELLULAR AUTOMATA GENERATOR

CellularAutomataGenerator::CellularAutomataGenerator()
: P_CLOSE_CELL(0)
, ITERATIONS(0)
, NEIGHBOUR_THRESHOLD(0)
, SEED_P_CLOSE_CELL(0)
, flip_value(CELL_OFF)
, inverse_flip_value(CELL_ON)
{
}

CellularAutomataGenerator::CellularAutomataGenerator(const CellularAutomataSettings& settings, const Dimensions& dim)
: cas(settings)
, dimensions(dim)
, P_CLOSE_CELL(cas.get_p_close_cell())
, ITERATIONS(cas.get_iterations())
, NEIGHBOUR_THRESHOLD(cas.get_neighbour_threshold())
, SEED_P_CLOSE_CELL(cas.get_seed_p_close_cell())
, flip_value(cas.get_flip_value())
{
  if (flip_value == CELL_ON)
  {
    inverse_flip_value = CELL_OFF;
  }
  else
  {
    inverse_flip_value = CELL_ON;
  }
}

// 1. Initialize the map
// For each iteration from 1 to ITERATIONS:
// 2. Randomly choose a square
// 3. Close that square if the random probability is less than P_CLOSE_CELL
// 4. If the cell is open, generate a random number.  If this is less than P_CLOSE_CELL, close the cell.
// 5. If the number of closed neighbours is greater than or equal to the number required to trigger, then open the cell, else close it.
CellMap CellularAutomataGenerator::generate()
{
  int y = dimensions.get_y();
  int x = dimensions.get_x();
  int rand_cell_y, rand_cell_x, num_closed_neighbours;
  int close_cell;

  CellMap cell_map = get_initialized_cells(y, x);
  
  for (int iteration = 0; iteration < ITERATIONS; iteration++)
  {
    // vectors start at 0, go to size-1.
    rand_cell_y = RNG::range(0, y-1);
    rand_cell_x = RNG::range(0, x-1);
    
    close_cell = RNG::range(0, 100);

    if (close_cell < P_CLOSE_CELL)
    {
      cell_map[rand_cell_y][rand_cell_x] = CELL_OFF;
    }

    num_closed_neighbours = get_number_closed_neighbours(cell_map, dimensions, rand_cell_y, rand_cell_x);
    if (num_closed_neighbours > NEIGHBOUR_THRESHOLD)
    {
      cell_map[rand_cell_y][rand_cell_x] = CELL_OFF;
    }
    else
    {
      cell_map[rand_cell_y][rand_cell_x] = CELL_ON;
    }
  }

  return cell_map;
}

CellMap CellularAutomataGenerator::get_initialized_cells(const int y, const int x)
{
  CellMap result_map;
  int rand_closed;

  for (int row = 0; row < y; row++)
  {
    vector<CellValue> cv;
    
    for (int col = 0; col < x; col++)
    {
      rand_closed = RNG::range(0, 100);

      if (rand_closed < SEED_P_CLOSE_CELL)
      {
        cv.push_back(flip_value);
      }
      else
      {
        cv.push_back(inverse_flip_value);
      }
    }
    
    result_map.push_back(cv);
  }
  
  return result_map;
}

int CellularAutomataGenerator::get_number_closed_neighbours(const CellMap& cell_map, const Dimensions& d, const int row, const int col)
{
  vector<pair<int, int> > neighbours = CoordUtils::get_adjacent_map_coordinates(d, row, col);
  int num_closed = 0;

  for (vector<pair<int, int> >::iterator n_it = neighbours.begin(); n_it != neighbours.end(); n_it++)
  {
    CellValue cell_val = cell_map[n_it->first][n_it->second];
    
    if (cell_val == CELL_OFF)
    {
      num_closed++;
    }
  }    

  return num_closed;
}


#ifdef UNIT_TESTS
#include "unit_tests/CellularAutomataGenerator_test.cpp"
#endif

