#pragma once
#include <boost/shared_ptr.hpp>
#include "ItemTypes.hpp"

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
    virtual bool effect(boost::shared_ptr<Creature> creature, const ItemStatus item_status) const;

    // Create an exact copy
    virtual Effect* clone() = 0;

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature) const = 0;
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature) const = 0;
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature) const = 0;
};

typedef boost::shared_ptr<Effect> EffectPtr;

