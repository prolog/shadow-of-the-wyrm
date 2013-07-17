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
    bool has_ailment(const CreaturePtr& creature) const;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const;

    static void initialize_text_sid_map();
    static void initialize_colour_map();

    static std::map<HungerLevel, std::string> text_sid_map;
    static std::map<HungerLevel, Colour> colour_map;
};

class PoisonStatusAilmentTranslator : public IStatusAilmentTranslator
{
  public:
    bool has_ailment(const CreaturePtr& creature) const;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const;
};

class MutenessStatusAilmentTranslator : public IStatusAilmentTranslator
{
  public:
    bool has_ailment(const CreaturePtr& creature) const;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const;
};

class ParalysisStatusAilmentTranslator : public IStatusAilmentTranslator
{
  public:
    bool has_ailment(const CreaturePtr& creature) const;

  protected:
    std::string get_status_ailment_text(const CreaturePtr& creature) const;
    Colour get_status_ailment_colour(const CreaturePtr& creature) const;
};
