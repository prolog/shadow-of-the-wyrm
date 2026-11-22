#include <chrono>
#include <thread>
#include "PauseAnimationInstruction.hpp"

using namespace std::chrono_literals;

// Pause for a default number of milliseconds.
void PauseAnimationInstruction::execute(Display* const)
{
  std::this_thread::sleep_for(100ms);
}

Coordinate PauseAnimationInstruction::get_coords() const
{
  return std::make_pair(-1, -1);
}