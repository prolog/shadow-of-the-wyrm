#include "ScreenCommands.hpp"
#include "ScreenCommandKeys.hpp"

using namespace std;

// Go to the next page
NextPageScreenCommand::NextPageScreenCommand(const int key)
: Command(ScreenCommandKeys::NEXT_PAGE, key)
{
}

// Go to the previous page
PreviousPageScreenCommand::PreviousPageScreenCommand(const int key)
: Command(ScreenCommandKeys::PREVIOUS_PAGE, key)
{
}

