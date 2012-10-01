#include <boost/serialization/export.hpp>
#include "CreatureTimeObserver.hpp"
#include "SeasonsTimeObserver.hpp"
#include "CreatureHPRegeneration.hpp"
#include "CreaturePietyRegeneration.hpp"
#include "CreatureSkillIncrementer.hpp"
#include "MovementAccumulationChecker.hpp"
#include "MovementAccumulator.hpp"
#include "Spring.hpp"
#include "Summer.hpp"
#include "Autumn.hpp"
#include "Winter.hpp"

// This file is used to declare class exports, needed to properly handle
// derived classes.  Base classes aren't declared!

// These are never actually tracked via a pointer, so suppress Boost's warning
// from my otherwise pristine build window.
BOOST_CLASS_TRACKING( ActionCoordinator, boost::serialization::track_never )
BOOST_CLASS_TRACKING( WorldTimeKeeper, boost::serialization::track_never )

// engine/time
BOOST_CLASS_EXPORT(CreatureTimeObserver)
BOOST_CLASS_EXPORT(SeasonsTimeObserver)
BOOST_CLASS_EXPORT(CreatureHPRegeneration)
BOOST_CLASS_EXPORT(CreaturePietyRegeneration)
BOOST_CLASS_EXPORT(CreatureSkillIncrementer)
BOOST_CLASS_EXPORT(MovementAccumulationChecker)
BOOST_CLASS_EXPORT(MovementAccumulator)

// world/seasons
BOOST_CLASS_EXPORT(Spring)
BOOST_CLASS_EXPORT(Summer)
BOOST_CLASS_EXPORT(Autumn)
BOOST_CLASS_EXPORT(Winter)

