#pragma once
#include <memory>
#include "common.hpp"

// A simple structure that makes dungeon and settlement generation easier.
struct Room
{
  Room();
  Room(int nid, int nx1, int nx2, int ny1, int ny2);
  bool operator==(const Room& that) const;

  std::shared_ptr<Room> centre_room;
  bool contains(Coordinate c) const;
  Coordinate get_centre() const;

  static bool compare_rooms(const Room& r1, const Room& r2);
  
  int id;
  int x1;
  int x2;
  int y1;
  int y2;
};

