#pragma once

class AutomaticMovementFlags
{
  public:
    AutomaticMovementFlags(const bool ignore_item_checks, const bool ignore_tile_check, const bool ignore_prev_visited_checks, const bool ignore_feature_checks);

    bool get_ignore_items() const;
    bool get_ignore_tile() const;
    bool get_ignore_prev_visited() const;
    bool get_ignore_feature() const;

  protected:
    bool ignore_items;
    bool ignore_tile;
    bool ignore_prev_visited;
    bool ignore_feature;
};

