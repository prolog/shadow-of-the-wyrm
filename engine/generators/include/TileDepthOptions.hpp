#pragma once
#include <vector>

class TileDepthOptions
{
  public:
    TileDepthOptions();
    TileDepthOptions(const int new_min_depth, const int new_max_depth, const std::vector<int>& new_remaining_depths);

    void set_min_depth(const int new_min_depth);
    int get_min_depth() const;

    void set_max_depth(const int new_max_depth);
    int get_max_depth() const;

    void set_remaining_depths(const std::vector<int>& new_remaining_depths);
    std::vector<int>& get_remaining_depths_ref();
    std::vector<int> get_remaining_depths() const;

  protected:
    // The min/max depths for this tile type.
    int min_depth;
    int max_depth;

    // Any set depths that should be used before randomly generating a depth
    // based on the min and max.
    std::vector<int> remaining_depths;
};
