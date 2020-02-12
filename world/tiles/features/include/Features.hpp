#pragma once
#include "AlignmentEnums.hpp"
#include "EntranceState.hpp"
#include "EntranceTypes.hpp"
#include "Feature.hpp"
#include "Symbol.hpp"

class Altar : public Feature
{
  public:
    Altar(const std::string& new_desc_sid, const Symbol& new_symbol, const std::string& new_deity_id, const MaterialType new_material, const AlignmentRange alignment_range);
    virtual ~Altar() {};
    virtual bool operator==(const Altar& altar) const;

    virtual bool can_offer() const override;

    virtual bool offer() override;

    virtual std::string get_deity_id() const;
    
    virtual float get_piety_loss_multiplier() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

    virtual AlignmentRange get_alignment_range() const override;
        
  protected:
    std::string deity_id;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using AltarPtr = std::shared_ptr<Altar>;

// A convenience class that sets up an evil altar appropriately.
class EvilAltar : public Altar
{
  public:
    EvilAltar(const Symbol& new_symbol);
    EvilAltar(const Symbol& new_symbol, const std::string& new_deity_id);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// GoodAltar is a convenience class that sets up an altar for a 
// particular good-aligned deity.
class GoodAltar : public Altar
{
  public:
    GoodAltar(const Symbol& new_symbol);
    GoodAltar(const Symbol& new_symbol, const std::string& new_deity_id);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// NeutralAltar is a convenience class that sets up an altar
// appropriately for a neutral deity.
class NeutralAltar : public Altar
{
  public:
    NeutralAltar(const Symbol& new_symbol);
    NeutralAltar(const Symbol& new_symbol, const std::string& new_deity_id);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Barrel : public Feature
{
  public:
    Barrel(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Barrel& b) const;

    virtual void set_drinks(const int new_drinks);
    int get_drinks() const;

    virtual bool can_pour() const;
    virtual bool pour();

    virtual void set_tap(const bool new_tap);
    virtual bool get_tap() const;

    virtual void set_pour_item_id(const std::string& new_pour_item_id);
    virtual std::string get_pour_item_id() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual void initialize_drinks();

    int drinks;
    bool tap;
    std::string pour_item_id;

    static const int MIN_DRINKS;
    static const int MAX_DRINKS;
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Bed : public Feature
{
  public:
    Bed(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Bed& t) const;

    virtual float get_hp_regeneration_multiplier() const override;
    virtual float get_ap_regeneration_multiplier() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// Benches are made of iron, and increase healing rates while sitting by
// a little.
class Bench : public Feature
{
  public:
    Bench(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

// A number of lightweight, decorative statues that can be generated
// by the FeatureGenerator.  These all inherit from the DecorativeStatue.
class DecorativeStatue : public Feature
{
  public:
    DecorativeStatue(const std::string& new_desc_sid, const Symbol& new_symbol);

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


// These classes provide an actual description
class KingDecorativeStatue : public DecorativeStatue
{
  public:
    KingDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class QueenDecorativeStatue : public DecorativeStatue
{
  public:
    QueenDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WarlordDecorativeStatue : public DecorativeStatue
{
  public:
    WarlordDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class KnightDecorativeStatue : public DecorativeStatue
{
  public:
    KnightDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HighPriestDecorativeStatue : public DecorativeStatue
{
  public:
    HighPriestDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SorcerorDecorativeStatue : public DecorativeStatue
{
  public:
    SorcerorDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Entrance : public Feature
{
  public:
    explicit Entrance(const std::string& new_desc_sid, const Symbol& new_symbol);
    explicit Entrance(const std::string& new_desc_sid, const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state);
    virtual ~Entrance() {};

    virtual bool operator==(const Entrance& door) const;

    virtual bool get_is_entrance() const override;

    virtual void set_state(const EntranceState& new_state);
    virtual EntranceState get_state() const;
    virtual EntranceState& get_state_ref();
    
    virtual Symbol get_symbol() const override;

    virtual void set_maximum_size(const CreatureSize new_maximum_size);
    virtual CreatureSize get_maximum_size() const;

    virtual bool can_handle(const bool feature_tile_occupied) const override;
    virtual bool can_open() const override;
    virtual bool can_lock() const override;
    virtual bool open();
    virtual bool close();
    
    // Returns a value based on the current state of the entrance -
    // if the entrance is open, a message about opening the door; if
    // the entrance is closed, a message about closing the door (etc).
    virtual std::string get_handle_message_sid() const override;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    EntranceState state;
    CreatureSize maximum_size; // The maximum creature size for the entrance.  Dragons can't go in Hobbit holes.

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Entrance
{
  public:
    explicit Door(const Symbol& new_symbol);
    explicit Door(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual ~Door() {};

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
 };

using DoorPtr = std::shared_ptr<Door>;

class Gate : public Entrance
{
  public:
    explicit Gate(const Symbol& new_symbol);
    explicit Gate(const Symbol& new_symbol, LockPtr new_lock, const EntranceState& new_state);
    virtual Feature* clone() override;

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// This is a "north-south" pew: the symbol is '-'.
// "east-west" pews are defined in EastWestPew.hpp.
class Pew : public Feature
{
  public:
    Pew(const Symbol& new_symbol);
    virtual Feature* clone() override;

    virtual float get_piety_loss_multiplier() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// This can be merged with Pew when done
class EastWestPew : public Pew
{
  public:
    EastWestPew(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class FirePillar : public Feature
{
  public:
    FirePillar(const Symbol& new_symbol);
    virtual Feature* clone() override;

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Forge : public Feature
{
  public:
    Forge(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Fountain : public Feature
{
  public:
    Fountain(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class JewelerWorkbench : public Feature
{
  public:
    JewelerWorkbench(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const JewelerWorkbench& j) const;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Pulper : public Feature
{
  public:
    Pulper(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Pulper& p) const;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

// A number of lightweight regular statues that can be generated
// by the FeatureGenerator.
class RegularStatue : public Feature
{
  public:
    RegularStatue(const Symbol& new_symbol);

    virtual bool get_is_blocking() const override;

    // get_description_sid() not implemented because this is an abstract
    // parent class.

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


class PetrifiedCorpseStatue : public RegularStatue
{
  public:
    PetrifiedCorpseStatue(const Symbol& new_symbol);
    PetrifiedCorpseStatue(const Symbol& new_symbol, const std::string& corpse_description_sid);
    bool operator==(const PetrifiedCorpseStatue& statue) const;

    void set_corpse_description_sid(const std::string& new_corpse_description_sid);
    std::string get_corpse_description_sid() const;

    virtual Feature* clone() override;
    
    std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string get_description_sid() const override;

    std::string corpse_description_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using PetrifiedCorpseStatuePtr = std::shared_ptr<PetrifiedCorpseStatue>;

class Sarcophagus : public Feature
{
  public:
    Sarcophagus(const Symbol& new_symbol);
    Sarcophagus(const Symbol& new_symbol, const MaterialType material);
    bool operator==(const Sarcophagus& sar) const;

    virtual Feature* clone() override;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

    virtual void set_inscription_sid(const std::string& new_inscription_sid);
    virtual std::string get_inscription_sid() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

    std::string inscription_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using SarcophagusPtr = std::shared_ptr<Sarcophagus>;

class Sign : public Feature
{
  public:
    Sign(const Symbol& new_symbol, const std::string& new_text_sid);

    virtual Feature* clone() override;
    virtual bool get_is_blocking() const;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SlotMachine : public Feature
{
  public:
    SlotMachine(const Symbol& new_symbol, const MaterialType material, const int cost, const int pct_chance_win, const float payout_multiplier);
    SlotMachine(const Symbol& new_symbol);
    SlotMachine(const Symbol& new_symbol, const MaterialType material);
    bool operator==(const SlotMachine& sm) const;

    virtual Feature* clone() override;

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
    int cost;
    int pct_chance_win;
    float payout_multiplier;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using SlotMachinePtr = std::shared_ptr<SlotMachine>;

class StoneMarker : public Feature
{
  public:
    StoneMarker(const Symbol& new_symbol);
    virtual Feature* clone() override;

    virtual float get_hp_regeneration_multiplier() const override;
    virtual float get_ap_regeneration_multiplier() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Table : public Feature
{
  public:
    Table(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Tannery : public Feature
{
  public:
    Tannery(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class Trap : public Feature
{
  public:
    Trap(const Symbol& new_symbol);
    virtual ~Trap() {};
    bool operator==(const Trap& trap) const;
    
    Trap* clone() override;
    Trap* clone_and_randomize_uses();

    virtual void set_is_hidden(const bool new_hidden) override;
    virtual bool get_is_hidden() const override;
    virtual bool get_is_dangerous() const override;

    virtual bool apply_on_movement(CreaturePtr creature) const override;

    void set_triggered(const bool new_triggered);
    bool get_triggered() const;

    void set_id(const std::string& new_id);
    std::string get_id() const;

    void set_description_sid(const std::string& new_description_sid);

    void set_trigger_message_sid(const std::string& new_trigger_message_sid);
    std::string get_trigger_message_sid() const;

    void set_trigger_symbol(const Symbol& new_trigger_symbol);
    Symbol get_trigger_symbol() const;

    void set_player_damage_message_sid(const std::string& new_player_damage_message_sid);
    std::string get_player_damage_message_sid() const;

    void set_colour(const Colour new_colour);
    virtual Colour get_colour() const override;

    void set_item_id(const std::string& new_item_id);
    std::string get_item_id() const;
    bool has_items() const;

    void set_damage(const Damage& new_damage);
    Damage get_damage() const;

    void set_effect(const EffectType new_effect);
    EffectType get_effect() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string get_description_sid() const;

    bool triggered;
    std::string id;
    std::string trigger_message_sid;
    Symbol trigger_symbol;
    std::string player_damage_message_sid;
    std::string item_id;
    Damage damage;
    EffectType effect;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using TrapPtr = std::shared_ptr<Trap>;

class WheelAndLoom : public Feature
{
  public:
    WheelAndLoom(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const WheelAndLoom& j) const;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

