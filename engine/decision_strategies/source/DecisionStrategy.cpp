#include "ControllerFactory.hpp"
#include "DecisionStrategy.hpp"
#include "Serialize.hpp"

using namespace std;

DecisionStrategy::DecisionStrategy(ControllerPtr new_controller)
: controller(new_controller)
{
}

bool DecisionStrategy::operator==(const DecisionStrategy& ds) const
{
  bool result = true;

  result = result && (internal_class_identifier() == ds.internal_class_identifier());

  result = result && ((current_fov_map && ds.current_fov_map) || (!current_fov_map && !ds.current_fov_map));
  
  if (result && current_fov_map)
  {
    result = result && (*current_fov_map == *ds.current_fov_map);
  }

  result = result && (threat_ratings == ds.threat_ratings);

  result = result && ((controller && ds.controller) || (!controller && !ds.controller));

  if (result && controller)
  {
    result = result && (*controller == *ds.controller);
  }

  result = result && (properties == ds.properties);

  return result;
}

// Get the threats - used to determine a course of action.
ThreatRatings& DecisionStrategy::get_threats_ref()
{
  return threat_ratings;
}

// Get a copy of the threats.
ThreatRatings DecisionStrategy::get_threats() const
{
  return threat_ratings;
}

// Set and get the current FOV map
void DecisionStrategy::set_fov_map(std::shared_ptr<Map> new_fov_map)
{
  current_fov_map = new_fov_map;
}

std::shared_ptr<Map> DecisionStrategy::get_fov_map()
{
  return current_fov_map;
}

ControllerPtr DecisionStrategy::get_controller()
{
  return controller;
}

void DecisionStrategy::set_property(const string& prop, const string& value)
{
  properties[prop] = value;
}

string DecisionStrategy::get_property(const string& prop) const
{
  string prop_val;
  auto p_it = properties.find(prop);

  if (p_it != properties.end())
  {
    prop_val = p_it->second;
  }

  return prop_val;
}

void DecisionStrategy::set_properties(const map<string, string>& new_properties)
{
  properties = new_properties;
}

map<string, string>& DecisionStrategy::get_properties_ref()
{
  return properties;
}

map<string, string> DecisionStrategy::get_properties() const
{
  return properties;
}

bool DecisionStrategy::can_move() const
{
  return true;
}

bool DecisionStrategy::serialize(ostream& stream) const
{
  threat_ratings.serialize(stream);
  Serialize::write_string_map(stream, properties);

  if (controller)
  {
    Serialize::write_class_id(stream, controller->get_class_identifier());
    controller->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  return true;
}

bool DecisionStrategy::deserialize(istream& stream)
{
  threat_ratings.deserialize(stream);
  Serialize::read_string_map(stream, properties);

  ClassIdentifier cl_id = ClassIdentifier::CLASS_ID_NULL;
  Serialize::read_class_id(stream, cl_id);

  if (cl_id != ClassIdentifier::CLASS_ID_NULL)
  {
    controller = ControllerFactory::create_controller(cl_id);
    if (!controller) return false;
    if (!controller->deserialize(stream)) return false;
  }

  return true;
}