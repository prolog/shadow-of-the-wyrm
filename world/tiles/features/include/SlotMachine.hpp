#pragma once
#include "Feature.hpp"

class SlotMachine : public Feature
{
  public:
    SlotMachine(const MaterialType material, const int cost, const int pct_chance_win, const float payout_multiplier);
    SlotMachine();
    SlotMachine(const MaterialType material);
    bool operator==(const SlotMachine& sm) const;

    virtual Feature* clone() override;

    virtual uchar get_symbol() const override;
    virtual Colour get_colour() const override;

    virtual void set_cost(const int new_cost);
    virtual int get_cost() const;

    virtual void set_pct_chance_win(const int new_pct_chance_win);
    virtual int get_pct_chance_win() const;

    virtual void set_payout_multiplier(const float new_payout_multiplier);
    virtual float get_payout_multiplier() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

    int cost;
    int pct_chance_win;
    float payout_multiplier;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using SlotMachinePtr = std::shared_ptr<SlotMachine>;

