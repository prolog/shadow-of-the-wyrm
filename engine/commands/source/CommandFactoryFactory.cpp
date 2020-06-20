#include "CommandFactoryFactory.hpp"
#include "EquipmentCommandFactory.hpp"
#include "HelpCommandFactory.hpp"
#include "InventoryCommandFactory.hpp"
#include "ScreenCommandFactory.hpp"
#include "SkillsCommandFactory.hpp"
#include "TileSelectionCommandFactory.hpp"

using namespace std; 
CommandFactoryFactory::CommandFactoryFactory()
{
  CommandFactoryPtr command = std::make_unique<CommandFactory>();
  CommandFactoryPtr equipment = std::make_unique<EquipmentCommandFactory>();
  CommandFactoryPtr inventory = std::make_unique<InventoryCommandFactory>();
  CommandFactoryPtr tile_select = std::make_unique<TileSelectionCommandFactory>();
  CommandFactoryPtr screen = std::make_unique<ScreenCommandFactory>();
  CommandFactoryPtr help = std::make_unique<HelpCommandFactory>();
  CommandFactoryPtr skills = std::make_unique<SkillsCommandFactory>();

  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_COMMAND_FACTORY, std::move(command)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_EQUIPMENT_COMMAND_FACTORY, std::move(equipment)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_INVENTORY_COMMAND_FACTORY, std::move(inventory)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_TILE_SELECTION_COMMAND_FACTORY, std::move(tile_select)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_SCREEN_COMMAND_FACTORY, std::move(screen)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY, std::move(help)));
  command_factory_map.insert(make_pair(ClassIdentifier::CLASS_ID_SKILLS_COMMAND_FACTORY, std::move(skills)));
}

CommandFactoryFactory::~CommandFactoryFactory()
{
}

CommandFactoryPtr CommandFactoryFactory::create_command_factory(const ClassIdentifier ci)
{
  CommandFactoryPtr factory;
  CommandFactorySerializationMap::iterator c_it = command_factory_map.find(ci);

  if (c_it != command_factory_map.end())
  {
    factory = std::unique_ptr<CommandFactory>(c_it->second->clone());
  }

  return factory;
}
