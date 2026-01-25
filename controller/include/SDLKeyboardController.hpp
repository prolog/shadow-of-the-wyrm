#pragma once
#ifdef ENABLE_SDL
#include <unordered_map>
#include "Controller.hpp"

class SDLKeyboardController : public Controller
{
  public:
    SDLKeyboardController();
    virtual ~SDLKeyboardController() = default;

    void poll_event() override;

    virtual Controller* clone() override;

  protected:
    void init_keymap();
    void init_shift_keymap();
    void init_ctrl_keymap();

    std::pair<int, std::set<KeyModifierType>> read_char_as_int() override;
    virtual std::pair<bool, int> read_char_as_int_nb() override;
    
    int translate_kb_input(const int input, const std::set<KeyModifierType>& key_modifiers) override;

    static bool SDL_initialized;
    static std::unordered_map<int, int> keymap;
    static std::unordered_map<int, int> shift_keymap;
    static std::unordered_map<int, int> ctrl_keymap;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

#endif
