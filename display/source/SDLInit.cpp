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

    ostringstream ss_audio;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
      ss_audio << "SDL_mixer init error: " << Mix_GetError();
      Log::instance().error(ss_audio.str());
    }
  }
  else
  {
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "0");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  }
}

void SDLInit::tear_down()
{
  Mix_Quit();
  SDL_Quit();
}
#endif