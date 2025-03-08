#pragma once
#include "BeamShapeProcessor.hpp"

class ReflectiveBeamShapeProcessor : public BeamShapeProcessor
{
  public:
    virtual ~ReflectiveBeamShapeProcessor() = default;

  protected:
    virtual bool should_beam_reflect() const override;
};

