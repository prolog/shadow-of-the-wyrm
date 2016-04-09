#include "CommandFactoryFactory.hpp"
#include "EquipmentCommandFactory.hpp"
#include "HelpCommandFactory.hpp"
#include "InventoryCommandFactory.hpp"
#include "ScreenCommandFactory.hpp"
#include "SkillsCommandFactory.hpp"
#include "TileSelectionCommandFactory.hpp"

using namespace std;

CommandFactorySerializationMap CommandFactoryFactory::command_factory_map;

CommandFactoryFactory::CommandFactoryFactory()
{
}

CommandFactoryFactory::~CommandFactoryFactory()
{
}

CommandFactoryPtr CommandFactoryFactory::create_command_factory(const ClassIdentifier ci)
{
  CommandFactoryPtr factory;

  if (command_factory_map.empty())
  {
    initialize_command_factory_map();
  }

  CommandFactorySerializationMap::iterator c_it = command_factory_map.find(ci);

  if (c_it != command_factory_map.end())
  {
    factory = std::shared_ptr<CommandFactory>(c_it->second->clone());
  }

  return factory;
}

void CommandFactoryFactory::initialize_command_factory_map()
{
  command_factory_map.clear();

  CommandFactoryPtr cf     = std::make_shared<CommandFactory>();
  CommandFactoryPtr eq_cf  = std::make_shared<EquipmentCommandFactory>();
  CommandFactoryPtr inv_cf = std::make_shared<InventoryCommandFactory>();
  CommandFactoryPtr ts_cf  = std::make_shared<TileSelectionCommandFactory>();
  CommandFactoryPtr sc_cf  = std::make_shared<ScreenCommandFactory>();
  CommandFactoryPtr hlp_cf = std::make_shared<HelpCommandFactory>();
  CommandFactoryPtr sk_cf  = std::make_shared<SkillsCommandFactory>();

  command_factory_map = CommandFactorySerializationMap{{ClassIdentifier::CLASS_ID_COMMAND_FACTORY, cf},
                                                       {ClassIdentifier::CLASS_ID_EQUIPMENT_COMMAND_FACTORY, eq_cf},
                                                       {ClassIdentifier::CLASS_ID_INVENTORY_COMMAND_FACTORY, inv_cf},
                                                       {ClassIdentifier::CLASS_ID_TILE_SELECTION_COMMAND_FACTORY, ts_cf},
                                                       {ClassIdentifier::CLASS_ID_SCREEN_COMMAND_FACTORY, sc_cf},
                                                       {ClassIdentifier::CLASS_ID_HELP_COMMAND_FACTORY, hlp_cf},
                                                       {ClassIdentifier::CLASS_ID_SKILLS_COMMAND_FACTORY, sk_cf}};
}
