#pragma once
#include <string>
#include <utility>
#include <boost/shared_ptr.hpp>
#include "Colours.hpp"
#include "Creature.hpp"

class IStatusAilmentTranslator
{
  public:
    virtual bool has_ailment(const CreaturePtr& creature) const = 0;
    virtual std::pair<std::string, Colour> get_status_ailment(const CreaturePtr& creature) const;

  protected:
    virtual std::string get_status_ailment_text(const CreaturePtr& creature) const = 0;
    virtual Colour get_status_ailment_colour(const CreaturePtr& creature) const = 0;
};

typedef boost::shared_ptr<IStatusAilmentTranslator> IStatusAilmentTranslatorPtr;

