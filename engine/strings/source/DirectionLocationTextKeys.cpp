#include "DirectionLocationTextKeys.hpp"
#include "Directions.hpp"

using namespace std;

DirectionLocationTextKeys::DirectionLocationTextKeys()
{
}

DirectionLocationTextKeys::~DirectionLocationTextKeys()
{
}

const string DirectionLocationTextKeys::get_direction_location_sid(const Direction d)
{
	string dir_sid = "";

	if (d == Direction::DIRECTION_NORTH_WEST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST;
	}
	else if (d == Direction::DIRECTION_NORTH)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH;
	}
	else if (d == Direction::DIRECTION_NORTH_EAST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST;
	}
	else if (d == Direction::DIRECTION_WEST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_WEST;
	}
	else if (d == Direction::DIRECTION_EAST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_EAST;
	}
	else if (d == Direction::DIRECTION_SOUTH_WEST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST;
	}
	else if (d == Direction::DIRECTION_SOUTH)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH;
	}
	else if (d == Direction::DIRECTION_SOUTH_EAST)
	{
		dir_sid = DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST;
	}

	return dir_sid;
}

const string DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_WEST = "DIRECTION_LOCATION_NORTH_WEST";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH = "DIRECTION_LOCATION_NORTH";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_NORTH_EAST = "DIRECTION_LOCATION_NORTH_EAST";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_WEST = "DIRECTION_LOCATION_WEST";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_MIDDLE = "DIRECTION_LOCATION_MIDDLE";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_EAST = "DIRECTION_LOCATION_EAST";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_WEST = "DIRECTION_LOCATION_SOUTH_WEST";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH = "DIRECTION_LOCATION_SOUTH";
const string DirectionLocationTextKeys::DIRECTION_LOCATION_SOUTH_EAST = "DIRECTION_LOCATION_SOUTH_EAST";