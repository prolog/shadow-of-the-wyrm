#pragma once
#include <vector>
#include "AnimationInstruction.hpp"

// The Animation class contains a set of instructions (draw, pause, etc)
// that when taken as a whole create an animation on-screen.
class Animation
{
  public:
    void add_animation_instruction(AnimationInstructionPtr instr);
    void set_animation_instructions(const std::vector<AnimationInstructionPtr>& new_animation_instructions);
    void clear_animation_instructions();
    std::vector<AnimationInstructionPtr> get_animation_instructions() const;

  protected:
    std::vector<AnimationInstructionPtr> animation_instructions;
};

