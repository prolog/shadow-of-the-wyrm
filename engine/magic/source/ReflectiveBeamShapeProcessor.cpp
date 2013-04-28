#include "ReflectiveBeamShapeProcessor.hpp"

// Reflective beams are, well, reflective.
bool ReflectiveBeamShapeProcessor::should_beam_reflect() const
{
  return true;
}