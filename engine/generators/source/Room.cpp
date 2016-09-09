#include <algorithm>
#include "CoordUtils.hpp"
#include "Room.hpp"

using namespace std;

Room::Room(const vector<string>& new_features, int nid, int nx1, int nx2, int ny1, int ny2)
: id(nid), x1(nx1), x2(nx2), y1(ny1), y2(ny2), features(new_features)
{
}

Room::Room()
: id(-1), x1(0), x2(0), y1(0), y2(0)
{
}

bool Room::operator==(const Room& that) const
{
  // Ignored shared ptr.
  return ((x1 == that.x1) && (x2 == that.x2) && (y1 == that.y1) && (y2 == that.y2));
}

bool Room::contains(Coordinate c) const
{
  int cy = c.first;
  int cx = c.second;

  return ((cy < y2) && (cy >= y1) && (cx < x2) && (cx >= x1));
}

Coordinate Room::get_centre() const
{
  Coordinate c;
  
  c.first  = (y1 + y2) / 2;
  c.second = (x1 + x2) / 2;
  
  return c;
}

bool Room::has_feature(const string& feature_name)
{
  return (find(features.begin(), features.end(), feature_name) != features.end());
}

bool Room::compare_rooms(const Room& r1, const Room& r2)
{
  Coordinate room1_c = r1.get_centre();
  Coordinate room1_centre_c = r1.centre_room->get_centre();

  Coordinate room2_c = r2.get_centre();
  Coordinate room2_centre_c = r2.centre_room->get_centre();
  
  int r1_td = CoordUtils::chebyshev_distance(room1_c, room1_centre_c);
  int r2_td = CoordUtils::chebyshev_distance(room2_c, room2_centre_c);
  
  return (r1_td < r2_td);
}
