#pragma once
#include "BeamShapeProcessor.hpp"

class ReflectiveBeamShapeProcessor : public BeamShapeProcessor
{
  protected:
    virtual bool should_beam_reflect() const;
};

