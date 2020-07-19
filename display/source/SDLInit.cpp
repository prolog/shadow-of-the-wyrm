#ifdef ENABLE_SDL
#include <sstream>
#include "Log.hpp"
#include "SDLInit.hpp"

using namespace std;

void SDLInit::set_up()
{
  // Temporary code, will be moved elsewhere once the display is working.
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    ostringstream ss;
    ss << "Unable to initialize SDL: " << SDL_GetError();
    Log::instance().error(ss.str());
  }
  else
  {
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "0");
  }
}

void SDLInit::tear_down()
{
  SDL_Quit();
}
#endif