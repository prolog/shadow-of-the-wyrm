#include <boost/serialization/export.hpp>
#include "CreatureTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "CreatureHPRegeneration.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureSkillIncrementer.hpp"

// This file is used to declare class exports, needed to properly handle
// base/derived classes.
BOOST_CLASS_EXPORT(Display)
BOOST_CLASS_EXPORT(NCursesDisplay)

// engine/time
BOOST_CLASS_EXPORT(ICreatureRegeneration)
BOOST_CLASS_EXPORT(CreatureTimeObserver)
BOOST_CLASS_EXPORT(SeasonsTimeObserver)
BOOST_CLASS_EXPORT(CreatureHPRegeneration)
BOOST_CLASS_EXPORT(CreaturePietyRegeneration)
BOOST_CLASS_EXPORT(CreatureSkillIncrementer)

