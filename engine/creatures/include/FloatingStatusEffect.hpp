#pragma once
#include "StatusEffect.hpp"

// Not an actual in-game effect.  Flying and Incorporeal both inherit
// from this class, since they both involve hovering off the ground.
// This allows sharing some common code, in particular surrounding what
// happens when the status wears off.
class FloatingStatusEffect : public StatusEffect
{
  protected:
    virtual void after_undo(std::shared_ptr<Creature> creature) const override;
};

