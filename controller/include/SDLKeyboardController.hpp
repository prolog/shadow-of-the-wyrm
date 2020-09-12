#pragma once
#ifdef ENABLE_SDL
#include <unordered_map>
#include "Controller.hpp"

class SDLKeyboardController : public Controller
{
  public:
    SDLKeyboardController();

    void poll_event() override;

    virtual Controller* clone() override;

  protected:
    void init_keymap();

    int read_char_as_int() override;
    virtual std::pair<bool, int> read_char_as_int_nb() override;
    
    int translate_kb_input(const int input) override;

    static bool SDL_initialized;
    static std::unordered_map<int, int> keymap;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

#endif
