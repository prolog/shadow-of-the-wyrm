#pragma once
#include <memory>
#include "Colours.hpp"
#include "IStatusEffectCalculator.hpp"

class Creature;

// StatusEffect is a base class for dealing with status changes to
// creatures.  It records the start time and duration of the status
// change, and methods to apply, finalize, and undo the change, as well
// as a method to do something every minute along the way, if required.
class StatusEffect
{
  public:
    StatusEffect();
    virtual ~StatusEffect();

    // Method to check whether the status should be applied.
    virtual bool should_apply_change(std::shared_ptr<Creature> creature) const;

    // Methods to handle creating, updating, removing, etc., the status change.
    // Each of these simply calls the before, do, and after methods - these three
    // are the ones that should be overridden by subclasses as necessary.
    virtual void apply_change(std::shared_ptr<Creature> creature) const;
    virtual void finalize_change(std::shared_ptr<Creature> creature) const;
    virtual void undo_change(std::shared_ptr<Creature> creature) const;

    // By default, nothing happens each tick.  Subclasses should override
    // this behaviour as necessary.
    virtual void tick(std::shared_ptr<Creature> creature) const;

    // Status Effects can change a character's to-hit, etc.  Exposing these
    // allows a variety of status effects to affect various calculations
    // without hard-coding the status effect lookups into the calculators.
    virtual int get_to_hit_bonus(std::shared_ptr<Creature> creature) const;
    virtual int get_evade_bonus(std::shared_ptr<Creature> creature) const;

  protected:
    // These functions are boolean to indicate whether or not the status was
    // actually applied.  The status will be applied in almost all cases, but
    // there are times when it may not be (e.g., trying to apply haste when
    // the creature is slowed cancels out the statuses).
    virtual bool before_apply(std::shared_ptr<Creature> creature) const;
    virtual bool apply(std::shared_ptr<Creature> creature) const;
    virtual bool after_apply(std::shared_ptr<Creature> creature) const;
    
    virtual std::string get_application_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_player_application_message() const;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const;

    virtual void before_finalize(std::shared_ptr<Creature> creature) const;
    virtual void finalize(std::shared_ptr<Creature> creature) const;
    virtual void after_finalize(std::shared_ptr<Creature> creature) const;

    virtual std::string get_finalize_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_player_finalize_message() const;
    virtual std::string get_npc_finalize_message(std::shared_ptr<Creature> creature) const;

    virtual void before_undo(std::shared_ptr<Creature> creature) const;
    virtual void undo(std::shared_ptr<Creature> creature) const;
    virtual void after_undo(std::shared_ptr<Creature> creature) const;

    virtual std::string get_undo_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_player_undo_message() const;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const;

    // The status identifier this class encompasses
    virtual std::string get_status_identifier() const;

    IStatusEffectCalculatorPtr status_calc;
};

typedef std::shared_ptr<StatusEffect> StatusEffectPtr;

