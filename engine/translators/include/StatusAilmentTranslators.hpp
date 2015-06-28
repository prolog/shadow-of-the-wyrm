#pragma once
#include <map>
#include "IStatusAilmentTranslator.hpp"

// The various status ailment translators, for things like hunger,
// poison, paralysis, and so on.  These translators check to see if the
// creature is afflicted by the appropriate ailment, and provide the
// display details (text, colour) for the UI.

// The hunger translator "has_ailment" if the hunger is anything other
// than normal: stuffed, hungry, etc.
class HungerStatusAilmentTranslator : public IStatusAilmentTranslator
{
  public:
    bool has_ailment(const CreaturePtr& creature) const override;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const override;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const override;

    static void initialize_text_sid_map();
    static void initialize_colour_map();

    static std::map<HungerLevel, std::string> text_sid_map;
    static std::map<HungerLevel, Colour> colour_map;
};

class WeightStatusAilmentTranslator : public IStatusAilmentTranslator
{
public:
  bool has_ailment(const CreaturePtr& creature) const override;

protected:
  std::string get_status_ailment_text(const CreaturePtr& creature) const override;
  Colour get_status_ailment_colour(const CreaturePtr& creature) const override;

  static void initialize_text_sid_map();
  static void initialize_colour_map();

  static std::map<BurdenLevel, std::string> text_sid_map;
  static std::map<BurdenLevel, Colour> colour_map;

};

class StatusAilmentTranslator : public IStatusAilmentTranslator
{
  public:
    StatusAilmentTranslator(const std::string& status_ailment_identifier, const std::string& status_ailment_text, const Colour status_ailment_colour);

    bool has_ailment(const CreaturePtr& creature) const override;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const override;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const override;

    std::string identifier;
    std::string text_sid;
    Colour colour;
};

