#include <boost/thread/thread.hpp>
#include "PauseAnimationInstruction.hpp"

// Pause for a default number of milliseconds, using the Boost threading
// library for reasonable portability.
void PauseAnimationInstruction::execute(Display* const)
{
  boost::this_thread::sleep(boost::posix_time::milliseconds(100));
}

Coordinate PauseAnimationInstruction::get_coords() const
{
  return std::make_pair(-1, -1);
}