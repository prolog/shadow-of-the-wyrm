#pragma once

class DeityStatus
{
  public:
    DeityStatus();
    ~DeityStatus();
    
    void set_piety(const int new_piety);
    int get_piety() const;
    void increment_piety(const int inc_amount);
    void decrement_piety(const int dec_amount);

    void set_crowned(const bool new_crowned_status);
    bool get_crowned() const;
    
  protected:
    int piety;
    bool crowned;
};
