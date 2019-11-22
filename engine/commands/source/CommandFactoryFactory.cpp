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
  command_factory_map = CommandFactorySerializationMap{ {ClassIdentifier::CLASS_ID_COMMAND_FACTORY, std::make_unique<CommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_EQUIPMENT_COMMAND_FACTORY, std::make_unique<EquipmentCommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_INVENTORY_COMMAND_FACTORY, std::make_unique<InventoryCommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_TILE_SELECTION_COMMAND_FACTORY, std::make_unique<TileSelectionCommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_SCREEN_COMMAND_FACTORY, std::make_unique<ScreenCommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY, std::make_unique<HelpCommandFactory>()},
                                                        {ClassIdentifier::CLASS_ID_SKILLS_COMMAND_FACTORY, std::make_unique<SkillsCommandFactory>()} };
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
