#include "Room.hpp"

Room::Room(int nid, int nx1, int nx2, int ny1, int ny2)
: id(nid), x1(nx1), x2(nx2), y1(ny1), y2(ny2)
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
