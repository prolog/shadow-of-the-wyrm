#include "CoordUtils.hpp"
#include "MapUtils.hpp"

using namespace std;

CoordUtils::CoordUtils()
{
}

CoordUtils::~CoordUtils()
{
}

Coordinate CoordUtils::incr(const Coordinate& c, const Dimensions& d)
{
  Coordinate result = c;

  int rows = d.get_y();
  int cols = d.get_x();

  // First, increment the column.  If it's greater than the max cols,
  // increment the rows.
  if (++result.second >= cols)
  {
    result.second = 0;
    result.first++;
  }

  if (result.first >= rows)
  {
    // If we've gone off the end, set it to the end coordinate.
    return end();
  }

  // It's a valid coordinate, given the current dimensions - return it.
  return result;
}

// Generate the "end" coordinate.
Coordinate CoordUtils::end()
{
  Coordinate end_coord(-1, -1);
  return end_coord;
}

// Check to see if a coordinate is an "end" coordinate.  Similar to the
// idea from STL containers, and "end" coordinate indicates we've gone
// beyond the incrementable range.
bool CoordUtils::is_end(const Coordinate& c)
{
  return (c.first == -1 && c.second == -1);
}

// Check for adjacency - distance must be 1 using the Chessboard distance (Chebyshev).
bool CoordUtils::are_coordinates_adjacent(const Coordinate& c1, const Coordinate& c2)
{
  return (CoordUtils::chebyshev_distance(c1, c2) == 1);
}

// Get the distance between two coordinates using Chebyshev distance
int CoordUtils::chebyshev_distance(Coordinate c1, Coordinate c2)
{
  return std::max(abs(c1.second - c2.second), abs(c1.first - c2.first));
}

// Check to see if movement in a given direction is valid.
bool CoordUtils::is_valid_move(const Dimensions& dim, const Coordinate& c, const Direction d)
{
  bool valid_move = true;

  int max_row = dim.get_y();
  int max_col = dim.get_x();

  Coordinate new_coord = get_new_coordinate(c, d);
  int new_row = new_coord.first;
  int new_col = new_coord.second;

  if (new_row < 0 || new_row >= max_row || new_col < 0 || new_col >= max_col)
  {
    valid_move = false;
  }

  return valid_move;
}

// Generate the next coordinate in a given direction.  Does not do correctness checking!
Coordinate CoordUtils::get_new_coordinate(const Coordinate& c, const Direction d, const int offset)
{
  Coordinate new_coord = c;

  switch(d)
  {
    case Direction::DIRECTION_NULL:
      new_coord = c;
      break;
    case Direction::DIRECTION_SOUTH_WEST:
      new_coord.first += offset;
      new_coord.second -= offset;
      break;
    case Direction::DIRECTION_SOUTH:
      new_coord.first += offset;
      break;
    case Direction::DIRECTION_SOUTH_EAST:
      new_coord.first += offset;
      new_coord.second += offset;
      break;
    case Direction::DIRECTION_WEST:
      new_coord.second -= offset;
      break;
    case Direction::DIRECTION_EAST:
      new_coord.second += offset;
      break;
    case Direction::DIRECTION_NORTH_WEST:
      new_coord.first -= offset;
      new_coord.second -= offset;
      break;
    case Direction::DIRECTION_NORTH:
      new_coord.first -= offset;
      break;
    case Direction::DIRECTION_NORTH_EAST:
      new_coord.first -= offset;
      new_coord.second += offset;
      break;
    case Direction::DIRECTION_UP:
    case Direction::DIRECTION_DOWN:
    default:
      break;
  }

  return new_coord;
}

// Get the direction given start/end coordinates.
Direction CoordUtils::get_direction(const Coordinate& start, const Coordinate& end)
{
  if ((start == end) ||
      ((end.first == -1) && (end.second == -1)))
  {
    return Direction::DIRECTION_NULL;
  }
  
  Direction d;
  
  int y1 = start.first;
  int x1 = start.second;
  
  int y2 = end.first;
  int x2 = end.second;
  
  // Start greater than end - heading north
  if (y1 > y2)
  {
    if (x1 < x2)
    {
      d = Direction::DIRECTION_NORTH_EAST;
    }
    else if (x1 == x2)
    {
      d = Direction::DIRECTION_NORTH;
    }
    else
    {
      d = Direction::DIRECTION_NORTH_WEST;
    }
  }
  // Start row = end row - heading east or west
  else if (y1 == y2)
  {
    if (x1 < x2)
    {
      d = Direction::DIRECTION_EAST;
    }
    else
    {
      d = Direction::DIRECTION_WEST;
    }
  }
  // Start row > end row - heading north
  else
  {
    if (x1 < x2)
    {
      d = Direction::DIRECTION_SOUTH_EAST;
    }
    else if (x1 == x2)
    {
      d = Direction::DIRECTION_SOUTH;
    }
    else
    {
      d = Direction::DIRECTION_SOUTH_WEST;
    }
  }
  
  return d;
}

// Get the coordinates adjacent to a given set within the current dimensions
vector<Coordinate> CoordUtils::get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col)
{
  vector<Coordinate> adjacent_coordinates;

  int max_rows = dim.get_y();
  int max_cols = dim.get_x();

  for (int cur_row = row - 1; cur_row <= row+1; cur_row++)
  {
    for (int cur_col = col - 1; cur_col <= col+1; cur_col++)
    {
      // Check bounds
      if (cur_row >= 0 && cur_row < max_rows && cur_col >= 0 && cur_col < max_cols)
      {
        // Neighbours can't include the current tile
        if (cur_row != row || cur_col != col)
        {
          adjacent_coordinates.push_back(make_pair(cur_row, cur_col));
        }
      }
    }
  }

  return adjacent_coordinates;
}

vector<Coordinate> CoordUtils::get_perimeter_coordinates(const Coordinate& top_left, const Coordinate& bottom_right)
{
  vector<Coordinate> perimeter_coordinates(get_perimeter_length(top_left, bottom_right));

  // Top
  for (int col = top_left.second; col <= bottom_right.second; col++)
  {
    perimeter_coordinates.push_back(make_pair(top_left.first, col));
  }

  // Right
  for (int row = top_left.first+1; row <= bottom_right.first; row++)
  {
    perimeter_coordinates.push_back(make_pair(row, bottom_right.second));
  }

  // Bottom
  for (int col = top_left.second; col <= bottom_right.second - 1; col++)
  {
    perimeter_coordinates.push_back(make_pair(bottom_right.first, col));
  }

  // Left
  for (int row = top_left.first + 1; row <= bottom_right.first - 1; row++)
  {
    perimeter_coordinates.push_back(make_pair(row, top_left.second));
  }

  return perimeter_coordinates;
}

map<CardinalDirection, Coordinate> CoordUtils::get_midway_coordinates(const Coordinate& top_left, const Coordinate& bottom_right)
{
  int height = bottom_right.first - top_left.first;
  int width = bottom_right.second - top_left.second;

  map<CardinalDirection, Coordinate> mid_coords = { { CardinalDirection::CARDINAL_DIRECTION_NORTH, { top_left.first, top_left.second + (width / 2) } },
                                                    { CardinalDirection::CARDINAL_DIRECTION_SOUTH, { top_left.first + height, top_left.second + (width / 2) } },
                                                    { CardinalDirection::CARDINAL_DIRECTION_WEST, { top_left.first + (height / 2), top_left.second + width} },
                                                    { CardinalDirection::CARDINAL_DIRECTION_EAST, { top_left.first + (height / 2), top_left.second } } };

  return mid_coords;
}

// Returns all coordinates from top left to bottom right, inclusive.
vector<Coordinate> CoordUtils::get_coordinates_in_range(const Coordinate& top_left, const Coordinate& bottom_right)
{
  int size = ((bottom_right.first - top_left.first) * (bottom_right.second - top_left.second));

  vector<Coordinate> coords;
  coords.reserve(size);

  for (int row = top_left.first; row <= bottom_right.first; row++)
  {
    for (int col = top_left.second; col <= bottom_right.second; col++)
    {
      coords.push_back(make_pair(row, col));
    }
  }

  return coords;
}

int CoordUtils::get_perimeter_length(const Coordinate& top_left, const Coordinate& bottom_right)
{
  int p = 0;

  if ((top_left.first < bottom_right.first) && (top_left.second < bottom_right.second))
  {
    // Since this is a rectangle, P = 2(W + L)
    int length = bottom_right.first - top_left.first;
    int width = bottom_right.second - top_left.second;
    p = 2 * (length + width);
  }

  return p;
}

pair<bool, vector<Coordinate>> CoordUtils::are_segments_joinable(const pair<Coordinate, Coordinate>& s1, const pair<Coordinate, Coordinate>& s2)
{
  pair<bool, vector<Coordinate>> result(false, {});

  vector<Coordinate> seg1 = get_coordinates_in_range(s1.first, s1.second);
  vector<Coordinate> seg2 = get_coordinates_in_range(s2.first, s2.second);

  if (!seg1.empty() && !seg2.empty())
  {
    auto s1_it = seg1.begin();
    auto s2_it = seg2.begin();

    while (!(s1_it == seg1.end() || s2_it == seg2.end()))
    {
      Coordinate seg1_c = *s1_it;
      Coordinate seg2_c = *s2_it;
      auto c_join = are_coordinates_joinable(seg1_c, seg2_c);

      // If the coordinates are joinable, add the intersecting coordinate to
      // the the return values.
      if (c_join.first)
      {
        if (!result.first)
        {
          result.first = true;
        }

        result.second.push_back(c_join.second);
      }

      // Iterate the appropriate iterator.  Always iterate at least one iterator!
      //
      // If the rows are 2 apart, iterate the iterator with the smallest
      // column.  
      if (abs(seg1_c.second - seg2_c.second) == 2)
      {
        (seg1_c.first < seg2_c.first) ? s1_it++ : s2_it++;
      }
      // If the columns are 2 apart, iterate the iterator with the smallest
      // row.
      else if (abs(seg1_c.first - seg2_c.first) == 2)
      {
        (seg1_c.second < seg2_c.second) ? s1_it++ : s2_it++;
      }
      // Otherwise, iterate the smallest coordinate.
      else
      {
        (seg1_c.first <= seg2_c.first && seg1_c.second <= seg2_c.second) ? s1_it++ : s2_it++;
      }
    }
  }

  return result;
}

// Is there a coordinate that can be placed between the two?
// Consider only horizontal and vertical (diagonal not currently supported).
pair<bool, Coordinate> CoordUtils::are_coordinates_joinable(const Coordinate& c1, const Coordinate& c2)
{
  pair<bool, Coordinate> result(true, make_pair(0,0));

  int d_row = abs(c1.first - c2.first);
  int d_col = abs(c1.second - c2.second);
  int middle_row = ((c1.first < c2.first) ? c1.first + 1 : c2.first + 1);
  int middle_col = ((c1.second < c2.second) ? c1.second + 1 : c2.second + 1);

  // Vertical section, joinable horizontally
  if (d_row == 0 && d_col == 2)
  {
    result.second = make_pair(c1.first, middle_col);
  }
  // Horizontal section, joinable vertically
  else if (d_col == 0 && d_row == 2)
  {
    result.second = make_pair(middle_row, c1.second);
  }
  else
  {
    result.first = false;
  }

  return result;
}

// Check to see if seg_1 ends before seg_2 starts
bool CoordUtils::ends_before(const pair<Coordinate, Coordinate>& seg_1, const pair<Coordinate, Coordinate>& seg_2)
{
  bool ends = false;

  if (is_horizontal(seg_1) && is_horizontal(seg_2))
  {
    ends = (seg_1.second.second < seg_2.first.second);
  }
  else if (is_vertical(seg_1) && is_vertical(seg_2))
  {
    ends = (seg_1.second.first < seg_2.first.first);
  }
  else
  {
    ends = (seg_1.second.first < seg_2.first.first && seg_1.second.second < seg_2.first.second);
  }

  return ends;
}

// Check to see if seg_1 starts after seg_2 ends
bool CoordUtils::starts_after(const pair<Coordinate, Coordinate>& seg_1, const pair<Coordinate, Coordinate>& seg_2)
{
  bool starts = false;

  if (is_horizontal(seg_1) && is_horizontal(seg_2))
  {
    starts = (seg_1.first.second > seg_2.second.second);
  }
  else if (is_vertical(seg_1) && is_vertical(seg_2))
  {
    starts = (seg_1.first.first > seg_2.second.first);
  }
  else
  {
    starts = (seg_1.first.first > seg_2.second.first && seg_1.first.second > seg_2.second.second);
  }

  return starts;
}

bool CoordUtils::is_horizontal(const pair<Coordinate, Coordinate>& segment)
{
  return (segment.first.first == segment.second.first);
}

bool CoordUtils::is_vertical(const pair<Coordinate, Coordinate>& segment)
{
  return (segment.first.second == segment.second.second);
}

string CoordUtils::to_string(const Coordinate& c)
{
  ostringstream ss;
  ss << "(" << c.first << "," << c.second << ")";

  return ss.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/CoordUtils_test.cpp"
#endif

