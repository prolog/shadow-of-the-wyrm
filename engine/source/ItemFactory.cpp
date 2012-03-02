#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "ItemFactory.hpp"

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

ItemPtr ItemFactory::create(ItemPtr item_to_copy)
{
  ItemPtr new_item;
  
  if (item_to_copy)
  {
    new_item = ItemPtr(item_to_copy->deep_copy());
    
    // Create and set a new item ID.  Clone just makes a true copy.
    boost::uuids::uuid id = boost::uuids::random_generator()();
    std::string id_s = Uuid::to_string(id);
    new_item->set_id(id_s);
  }
  
  return new_item;
}
