#include "ControllerFactory.hpp"
#include "DecisionStrategy.hpp"
#include "Serialize.hpp"

using namespace std;

DecisionStrategy::DecisionStrategy(ControllerPtr new_controller)
: controller(new_controller), autopickup(false)
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
  result = result && (autopickup == ds.autopickup);
  result = result && (autopickup_types == ds.autopickup_types);

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
  MapPtr fov = current_fov_map;

  // Generally shouldn't happen, but, you know...
  if (fov == nullptr)
  {
    Dimensions dim;
    fov = std::make_shared<Map>(dim);
  }

  return fov;
}

ControllerPtr DecisionStrategy::get_controller()
{
  return controller;
}

void DecisionStrategy::set_property(const string& prop, const string& value)
{
  properties[prop] = value;
}

bool DecisionStrategy::remove_property(const string& prop)
{
  bool removed = false;

  auto p_it = properties.find(prop);
  if (p_it != properties.end())
  {
    properties.erase(p_it);
    removed = true;
  }

  return removed;
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

void DecisionStrategy::set_autopickup(const bool new_autopickup)
{
  autopickup = new_autopickup;
}

bool DecisionStrategy::get_autopickup() const
{
  return autopickup;
}

void DecisionStrategy::set_autopickup_types(const set<ItemType>& new_autopickup_types)
{
  autopickup_types = new_autopickup_types;
}

set<ItemType> DecisionStrategy::get_autopickup_types() const
{
  return autopickup_types;
}

bool DecisionStrategy::can_move() const
{
  return true;
}

bool DecisionStrategy::serialize(ostream& stream) const
{
  threat_ratings.serialize(stream);
  Serialize::write_string_map(stream, properties);
  Serialize::write_bool(stream, autopickup);
  
  Serialize::write_size_t(stream, autopickup_types.size());
  for (const ItemType it : autopickup_types)
  {
    Serialize::write_enum(stream, it);
  }

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
  Serialize::read_bool(stream, autopickup);

  autopickup_types.clear();
  size_t aptypes_sz = 0;
  Serialize::read_size_t(stream, aptypes_sz);

  for (size_t i = 0; i < aptypes_sz; i++)
  {
    ItemType it = ItemType::ITEM_TYPE_NULL;
    Serialize::read_enum(stream, it);

    autopickup_types.insert(it);
  }

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