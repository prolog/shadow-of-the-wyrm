#pragma once
#include "ITimeObserver.hpp"
#include "Map.hpp"

class TileTransformObserver : public ITimeObserver
{
  public:
    void notify(const ulonglong minutes_elapsed) override;

    std::unique_ptr<ITimeObserver> clone() override;

  protected:
    void process_tile_transforms(MapPtr current_map, const double cur_seconds);

  private:
    ClassIdentifier internal_class_identifier() const override;
};

