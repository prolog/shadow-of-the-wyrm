#include "Animation.hpp"

using namespace std;

void Animation::add_animation_instruction(AnimationInstructionPtr instr)
{
  animation_instructions.push_back(instr);
}

void Animation::clear_animation_instructions()
{
  animation_instructions.clear();
}

void Animation::set_animation_instructions(const vector<AnimationInstructionPtr>& new_animation_instructions)
{
  animation_instructions = new_animation_instructions;
}

vector<AnimationInstructionPtr> Animation::get_animation_instructions() const
{
  return animation_instructions;
}

