#include <boost/thread/thread.hpp>
#include "PauseAnimationInstruction.hpp"

// Pause for a default number of milliseconds, using the Boost threading
// library for reasonable portability.
void PauseAnimationInstruction::execute(Display* const display)
{
  boost::this_thread::sleep(boost::posix_time::milliseconds(150));
}
