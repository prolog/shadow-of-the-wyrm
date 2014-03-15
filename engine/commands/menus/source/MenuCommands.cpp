#include "MenuCommands.hpp"
#include "MenuCommandKeys.hpp"

using namespace std;

// Go to the next page
NextPageMenuCommand::NextPageMenuCommand(const int key)
: Command(MenuCommandKeys::NEXT_PAGE, key)
{
}

// Go to the previous page
PreviousPageMenuCommand::PreviousPageMenuCommand(const int key)
: Command(MenuCommandKeys::PREVIOUS_PAGE, key)
{
}

