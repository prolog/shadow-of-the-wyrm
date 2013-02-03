#include "DeathEventFunctions.hpp"
#include "Game.hpp"

using namespace std;

// The event function identifiers
DeathEventFunctionNames::DeathEventFunctionNames()
{
}

DeathEventFunctionNames::~DeathEventFunctionNames()
{
}

const string DeathEventFunctionNames::DEATH_EVENT_WIN = "win";

// Individual death event functions
DeathEventFunctions::DeathEventFunctions()
{
}

DeathEventFunctions::~DeathEventFunctions()
{
}

// Win the game!  Great riches and hot elf babes/Legolas-lookalike strippers await!
void DeathEventFunctions::win(CreaturePtr attacking, CreaturePtr dead, MapPtr map)
{
  Game& game = Game::instance();
  game.stop_playing();
}

// This function should stay empty!  This is the default function that's called after each creature death.
// If the creature doesn't have a death event (and most won't), we want nothing to happen.
void DeathEventFunctions::null(CreaturePtr attacking, CreaturePtr dead, MapPtr map)
{
}
