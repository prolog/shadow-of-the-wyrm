#ifdef ENABLE_SDL
#include <sstream>
#include "Log.hpp"
#include "SDLInit.hpp"

using namespace std;

void SDLInit::set_up()
{
  // Temporary code, will be moved elsewhere once the display is working.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    ostringstream ss;
    ss << "Unable to initialize SDL: " << SDL_GetError();
    Log::instance().error(ss.str());
  }
  else
  {
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
  {
    ostringstream ss_audio;

    ss_audio << "SDL_mixer init error: " << Mix_GetError();
    Log::instance().error(ss_audio.str());
  }
}

void SDLInit::tear_down()
{
  Mix_Quit();
  SDL_Quit();
}
#endif