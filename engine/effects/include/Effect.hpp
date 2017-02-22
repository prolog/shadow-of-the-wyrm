#pragma once
#include <vector>
#include <memory>
#include "AdditionalEffectMessage.hpp"
#include "ItemTypes.hpp"

class ActionManager;
class Creature;

// An interface describing some sort of (typically magical) effect.  The
// boolean return value is used to determine whether the creature should
// be aware of the result - i.e., if the result identifies the item.
//
// As an example, zapping a wand of light in a lit area should not identify
// the wand, but zapping it in a dark room should.
class Effect
{
  public:
    virtual ~Effect() {};

    void set_source_id(const std::string& new_source_id);
    std::string get_source_id() const;

    virtual bool effect(std::shared_ptr<Creature> creature, ActionManager * const am, const ItemStatus item_status, const bool show_message_on_unid = true);

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const = 0;

    // Is this a negative effect?  Would a create be upset if it were applied?
    virtual bool is_negative_effect() const;

    // Additional properties are read in from a map.  These can be used to set
    // values from spells, like healing amounts.
    virtual void read_properties(const std::map<std::string, std::string>& properties);

    // Create an exact copy
    virtual Effect* clone() = 0;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) = 0;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) = 0;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) = 0;
    
    // Effect identification functions
    virtual void identify_effect_as_necessary(std::shared_ptr<Creature> creature, const bool is_identified, const bool show_msg_on_unid) const;
    virtual void identify_effect_if_player(std::shared_ptr<Creature> creature) const;
    virtual void inform_unidentified_if_player(std::shared_ptr<Creature> creature) const;

    // Add all the additional effect messages, if the creature is the
    // player.
    virtual void add_additional_effect_messages(std::shared_ptr<Creature> creature) const;

    // Additional messages that are displayed regardless of identification
    // success or failure.
    std::vector<AdditionalEffectMessagePtr> additional_effect_messages;

    // Where did the effect originally come from?
    std::string source_id;
};

using EffectPtr = std::shared_ptr<Effect>;

