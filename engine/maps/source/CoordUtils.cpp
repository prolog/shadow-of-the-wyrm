#include "CoordUtils.hpp"
#include "DirectionUtils.hpp"
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
int CoordUtils::chebyshev_distance(const Coordinate& c1, const Coordinate& c2)
{
  return std::max(abs(c1.second - c2.second), abs(c1.first - c2.first));
}

int CoordUtils::get_height(const Coordinate& c1, const Coordinate& c2)
{
  return std::abs(c2.first - c1.first);
}

int CoordUtils::get_width(const Coordinate& c1, const Coordinate& c2)
{
  return std::abs(c2.second - c1.second);
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

bool CoordUtils::is_in_range(const Dimensions& dim, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool valid_move = true;

  if (start_coord.first < 0 || end_coord.first >= dim.get_y() || start_coord.second < 0 || end_coord.second >= dim.get_x())
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

// Given a particular bounding box, return a new bounding box that represents
// shifting it in a particular direction.
BoundingBox CoordUtils::get_new_bounding_box(const BoundingBox& bb, const Direction d)
{
  BoundingBox shifted_bb(get_new_coordinate(bb.get_c1(), d), get_new_coordinate(bb.get_c2(), d));
  return shifted_bb;
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
vector<Coordinate> CoordUtils::get_adjacent_map_coordinates(const Dimensions& dim, const int row, const int col, const int step_size)
{
  vector<Coordinate> adjacent_coordinates;

  int max_rows = dim.get_y();
  int max_cols = dim.get_x();

  for (int cur_row = row - step_size; cur_row <= row + step_size; cur_row++)
  {
    for (int cur_col = col - step_size; cur_col <= col + step_size; cur_col++)
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

vector<Coordinate> CoordUtils::get_border_coordinates(const Coordinate& top_left, const Coordinate& bottom_right, const int length)
{
  Coordinate top_right = {top_left.first, bottom_right.second};
  Coordinate bottom_left = {bottom_right.first, top_left.second};

  vector<pair<Coordinate, vector<Direction>>> dirs = {{top_left, {Direction::DIRECTION_EAST, Direction::DIRECTION_SOUTH}}, 
                                                      {top_right, {Direction::DIRECTION_WEST, Direction::DIRECTION_SOUTH}},
                                                      {bottom_left, {Direction::DIRECTION_NORTH, Direction::DIRECTION_EAST}},
                                                      {bottom_right, {Direction::DIRECTION_NORTH, Direction::DIRECTION_WEST}}};

  vector<Coordinate> border_coords;

  for (auto d_pair : dirs)
  {
    border_coords.push_back(d_pair.first);

    for (auto d : d_pair.second)
    {
      for (int i = 0; i < length; i++)
      {
        Coordinate c = get_new_coordinate(d_pair.first, d, i+1);
        border_coords.push_back(c);
      }
    }
  }

  return border_coords;
}

vector<Coordinate> CoordUtils::get_corner_coordinates(const Coordinate& top_left, const Coordinate& bottom_right)
{
  Coordinate top_right = {top_left.first, bottom_right.second};
  Coordinate bottom_left = {bottom_right.first, top_left.second};
  vector<Coordinate> corners = {top_left, top_right, bottom_left, bottom_right};

  return corners;
}

vector<Coordinate> CoordUtils::get_perimeter_coordinates(const Coordinate& top_left, const Coordinate& bottom_right)
{
  vector<Coordinate> perimeter_coordinates;
  perimeter_coordinates.reserve(get_perimeter_length(top_left, bottom_right));

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

bool CoordUtils::is_in_perimeter(const Coordinate& cur_loc, const Coordinate& c1, const Coordinate& c2)
{
  bool in_perimeter = ((cur_loc.first == c1.first) || (cur_loc.first == c2.first) || (cur_loc.second == c1.second) || (cur_loc.second == c2.second));
  return in_perimeter;
}

vector<Coordinate> CoordUtils::get_beam_coordinates(const Coordinate& centre_coord, const Direction d, const uint radius)
{
  vector<Coordinate> beam;

  if (radius > 0)
  {
    beam.push_back(centre_coord);
  }

  Coordinate c1, c2;
  bool insert = false;

  for (uint i = 1; i < radius; i++)
  {
    switch (d)
    {
      // Valid beam directions:
      case Direction::DIRECTION_NORTH:
      case Direction::DIRECTION_SOUTH:
        c1 = make_pair(centre_coord.first, centre_coord.second - i);
        c2 = make_pair(centre_coord.first, centre_coord.second + i);

        insert = true;
        break;
      case Direction::DIRECTION_NORTH_WEST:
      case Direction::DIRECTION_SOUTH_EAST:
      case Direction::DIRECTION_NORTH_EAST:
      case Direction::DIRECTION_SOUTH_WEST:
      case Direction::DIRECTION_WEST:
      case Direction::DIRECTION_EAST:
        c1 = make_pair(centre_coord.first - i, centre_coord.second);
        c2 = make_pair(centre_coord.first + i, centre_coord.second);

        insert = true;
        break;

      // Not valid beam directions:
      case Direction::DIRECTION_UP:
      case Direction::DIRECTION_DOWN:
      case Direction::DIRECTION_NULL:
      default:
        insert = false;
        break;
    }

    if (insert)
    {
      beam.push_back(c1);
      beam.push_back(c2);
    }
  }

  return beam;
}

vector<Coordinate> CoordUtils::get_circle_coordinates(const int row_centre, const int col_centre, const int radius)
{
  vector<Coordinate> coords;

  // Midpoint circle algorithm.  Thank you, internets.
  // (Both of you - you're super.)
  //
  // Really, I wonder how I wrote code when I was a kid,
  // hacking C in djgpp, with no knowledge of data structures
  // and types outside of ints, chars, and arrays.

  // A midpoint circle
  // Math from basic principles:
  // Knowledge gone like ghosts.
  int y0 = row_centre;
  int x0 = col_centre;

  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  coords.push_back({y0 + radius, x0});
  coords.push_back({y0 - radius, x0});
  coords.push_back({y0, x0 + radius});
  coords.push_back({y0, x0 - radius});

  while (x < y)
  {
    // ddF_x = 2 * x + 1;
    // ddF_y = -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y+1;
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_x;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    coords.push_back({y0 + y, x0 + x});
    coords.push_back({y0 + y, x0 - x});
    coords.push_back({y0 - y, x0 + x});
    coords.push_back({y0 - y, x0 - x});
    coords.push_back({y0 + x, x0 + y});
    coords.push_back({y0 + x, x0 - y});
    coords.push_back({y0 - x, x0 + y});
    coords.push_back({y0 - x, x0 - y});
  }

  return coords;
}

vector<Coordinate> CoordUtils::get_square_coordinates(const int row_centre, const int col_centre, const int radius, const RotationDirection rd)
{
  vector<Coordinate> coords;
  int start_row = row_centre - radius;
  int start_col = col_centre - radius;
  int end_row = row_centre + radius;
  int end_col = col_centre + radius;
  bool iterate = true;
  int dy = 0;
  int dx = 0;
  int cur_col = start_col;
  int cur_row = start_row;
  Coordinate start_coord = {start_row, start_col};
  int num_coords = 1;

  // Iterate, turtle-like, around the coords.  Most algorithms don't care
  // about the coordinate order, and the turtle-like iteration will satisfy
  // those who need the coordinates "stepped".
  //
  // The iteration is clockwise.
  if (radius > 0)
  {
    while (iterate)
    {
      if (cur_col == start_col && cur_row == start_row)
      {
        dy = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 0 : 1;
        dx = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 1 : 0;
      }
      else if (cur_col == end_col && cur_row == start_row)
      {
        dy = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 1 : 0;
        dx = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 0 : -1;
      }
      else if (cur_col == end_col && cur_row == end_row)
      {
        dy = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 0 : -1;
        dx = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? -1 : 0;
      }
      else if (cur_col == start_col && cur_row == end_row)
      {
        dy = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? -1 : 0;
        dx = (rd == RotationDirection::ROTATION_DIRECTION_CLOCKWISE) ? 0 : 1;
      }

      Coordinate cur_coord = make_pair(cur_row, cur_col);

      // If we've completed the iteration, break.
      // Otherwise, add the current coordinates to our list of coordinates and
      // continue the iteration.
      if (num_coords > 1 && cur_coord == start_coord)
      {
        iterate = false;
      }
      else
      {
        coords.push_back(cur_coord);
      }

      cur_row += dy;
      cur_col += dx;
      num_coords++;
    }
  }

  return coords;
}

Coordinate CoordUtils::get_centre_coordinate(const Coordinate& top_left, const Coordinate& bottom_right)
{
  return {(top_left.first + bottom_right.first) / 2, (top_left.second + bottom_right.second) / 2};
}

vector<Coordinate> CoordUtils::get_t_coordinates(const Coordinate& sp, const CardinalDirection cd, const int segment_length)
{
  vector<Coordinate> coords;
  Coordinate next = sp;

  coords.push_back(next);

  // First segment
  for (int i = 0; i < segment_length; i++)
  {
    next = get_new_coordinate(next, DirectionUtils::to_direction(cd));

    coords.push_back(next);
  }

  // Second segment.  Form the "T" by going east/west if this is a N/S stem,
  // and vice versa.
  vector<Direction> t_dirs = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH};

  if (cd == CardinalDirection::CARDINAL_DIRECTION_NORTH || cd == CardinalDirection::CARDINAL_DIRECTION_SOUTH)
  {
    t_dirs = {Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};
  }

  for (int i = 1; i <= segment_length; i++)
  {
    coords.push_back(get_new_coordinate(next, t_dirs[0], i));
    coords.push_back(get_new_coordinate(next, t_dirs[1], i));
  }

  return coords;
}

// Gets coordinates in an equal, sequential stepping pattern from a given 
// starting point.
// 
// E.g.: North 2, East 2, North 2, West 2, North 2...
vector<Coordinate> CoordUtils::get_stepped_coordinates(const Coordinate& sp, const vector<CardinalDirection>& directions, const int step_length)
{
  vector<Coordinate> coords;

  Coordinate c = sp;
  coords.push_back(c);

  for (const CardinalDirection cd : directions)
  {
    Direction d = DirectionUtils::to_direction(cd);

    for (int i = 0; i < step_length; i++)
    {
      c = get_new_coordinate(c, d);
      coords.push_back(c);
    }
  }

  return coords;
}

// Creates a cross like:
//
//  *
// *** (size 1)
//  *
//
//    *
//    *
//  ***** (size 2)
//    *
//    *
//
// Centre point is always added.  Size is number of coordinates generated
// in each direction.
vector<Coordinate> CoordUtils::get_cross(const Coordinate& origin, const int size)
{
  vector<Coordinate> points;

  points.push_back(origin);
  vector<Direction> directions = {Direction::DIRECTION_NORTH, Direction::DIRECTION_SOUTH, Direction::DIRECTION_EAST, Direction::DIRECTION_WEST};

  for (int i = 0; i < size; i++)
  {
    for (const Direction d : directions)
    {
      points.push_back(get_new_coordinate(origin, d, i + 1));
    }
  }

  return points;
}

vector<Coordinate> CoordUtils::get_line_segment(const Coordinate& origin, const CardinalDirection cd, const int length)
{
  return get_line_segment(origin, DirectionUtils::to_direction(cd), length);
}

vector<Coordinate> CoordUtils::get_line_segment(const Coordinate& origin, const Direction d, const int length)
{
  vector<Coordinate> seg;

  if (length > 0)
  {
    seg.push_back(origin);

    for (int i = 1; i < length; i++)
    {
      seg.push_back(get_new_coordinate(origin, d, i));
    }
  }

  return seg;
}

// Return the top left/bottom right coordinate of the minimum bounding box
BoundingBox CoordUtils::get_minimum_bounding_box(const Dimensions& dim, const vector<Coordinate>& points, const int padding)
{
  pair<Coordinate, Coordinate> bounds = {{dim.get_y(), dim.get_x()},{-1,-1}};

  if (points.empty())
  {
    bounds = {{0,0},{dim.get_y()-1,dim.get_x()-1}};
  }
  else
  {
    for (const Coordinate& c : points)
    {
      if (c.first < bounds.first.first)
      {
        bounds.first.first = c.first;
      }

      if (c.second < bounds.first.second)
      {
        bounds.first.second = c.second;
      }

      if (c.first > bounds.second.first)
      {
        bounds.second.first = c.first;
      }

      if (c.second > bounds.second.second)
      {
        bounds.second.second = c.second;
      }
    }
  }

  bounds.first.first -= padding;
  bounds.first.second -= padding;

  bounds.second.first += padding;
  bounds.second.second += padding;

  bounds.first.first = std::max<int>(0, bounds.first.first);
  bounds.first.second = std::max<int>(0, bounds.first.second);

  bounds.second.first = std::min<int>(dim.get_y()-1, bounds.second.first);
  bounds.second.second = std::min<int>(dim.get_x()-1, bounds.second.second);

  BoundingBox bb(bounds.first, bounds.second);
  return bb;
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
vector<Coordinate> CoordUtils::get_coordinates_in_range(const Coordinate& top_left, const Coordinate& bottom_right, const bool start_row_inclusive, const bool start_col_inclusive, const bool end_row_inclusive, const bool end_col_inclusive)
{
  int size = ((bottom_right.first - top_left.first) * (bottom_right.second - top_left.second));

  vector<Coordinate> coords;
  coords.reserve(size);

  int start_row = top_left.first + 1;

  if (start_row_inclusive)
  {
    start_row--;
  }

  int start_col = top_left.second + 1;

  if (start_col_inclusive)
  {
    start_col--;
  }

  int end_row = bottom_right.first - 1;

  if (end_row_inclusive)
  {
    end_row++;
  }

  int end_col = bottom_right.second - 1;

  if (end_col_inclusive)
  {
    end_col++;
  }

  for (int row = start_row; row <= end_row; row++)
  {
    for (int col = start_col; col <= end_col; col++)
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

pair<bool, vector<Coordinate>> CoordUtils::are_segments_joinable(const pair<Coordinate, Coordinate>& s1, const pair<Coordinate, Coordinate>& s2, const int incr)
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
      auto c_join = are_coordinates_joinable(seg1_c, seg2_c, incr);

      // If the coordinates are joinable, add the intersecting coordinates to
      // the the return values.
      if (c_join.first)
      {
        if (!result.first)
        {
          result.first = true;
        }

        result.second.insert(result.second.end(), c_join.second.begin(), c_join.second.end());
      }

      // Iterate the appropriate iterator.  Always iterate at least one iterator!
      //
      // If the rows are 2 apart, iterate the iterator with the smallest
      // column.  
      if (CoordUtils::is_vertical(s1))
      {
        (seg1_c.first < seg2_c.first) ? s1_it++ : s2_it++;
      }
      // If the columns are 2 apart, iterate the iterator with the smallest
      // row.
      else if (CoordUtils::is_horizontal(s1))
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
pair<bool, vector<Coordinate>> CoordUtils::are_coordinates_joinable(const Coordinate& c1, const Coordinate& c2, const int incr)
{
  pair<bool, vector<Coordinate>> result(true, {make_pair(0,0)});

  int d_row = abs(c1.first - c2.first);
  int d_col = abs(c1.second - c2.second);

  // Vertical section, joinable horizontally
  if (d_row == 0 && d_col == incr)
  {
    Coordinate smaller, larger;
    if (c1.second <= c2.second)
    {
      smaller = c1;
      larger = c2;
    }
    else
    {
      smaller = c2;
      larger = c1;
    }
    result.second = get_coordinates_in_range(smaller, larger, true, false, true, false);
  }
  // Horizontal section, joinable vertically
  else if (d_col == 0 && d_row == incr)
  {
    Coordinate smaller, larger;
    if (c1.first <= c2.first)
    {
      smaller = c1;
      larger = c2;
    }
    else
    {
      smaller = c2;
      larger = c1;
    }
    result.second = get_coordinates_in_range(smaller, larger, false, true, false, true);
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

