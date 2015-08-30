#pragma once
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "Readable.hpp"

class ItemIdentifier;

// Implements common functionality required for reading a scroll, a
// spellbook, etc.  Used by the ReadAction class to perform the steps
// necessary.
class ReadStrategy : public IActionManager
{
  public:
    virtual ~ReadStrategy() {};

    // Attempt to read the scroll, spellbook, etc.
    virtual ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable) = 0;

    // Add a message indicating that reading the scroll, spellbook, etc.,
    // was successful.
    void add_successful_read_message(CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id);
    void add_read_message(const std::pair<std::string, std::string>& player_and_monster_message_sids, CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id);

  protected:
    virtual std::pair<std::string, std::string> get_player_and_monster_read_sids() const = 0;

    virtual ActionCostValue get_action_cost_value(CreaturePtr creature) const override = 0;
};

using ReadStrategyPtr = std::shared_ptr<ReadStrategy>;

