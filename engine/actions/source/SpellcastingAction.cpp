#include "ActionTextKeys.hpp"
#include "ArcanaTextKeys.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DirectionUtils.hpp"
#include "SpellcastingAction.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MagicalAbilityChecker.hpp"
#include "MagicalDamageCalculator.hpp"
#include "MagicCommandFactory.hpp"
#include "MagicCommandProcessor.hpp"
#include "MagicCommands.hpp"
#include "MagicKeyboardCommandMap.hpp"
#include "MagicCommandKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"
#include "RNG.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SkillManager.hpp"
#include "SoundEffectID.hpp"
#include "SpellBonusUpdater.hpp"
#include "SpellcastingTextKeys.hpp"
#include "SpellSelectionScreen.hpp"
#include "SpellcastingProcessor.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "StatisticsMarker.hpp"
#include "StringTable.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

const int SpellcastingAction::PCT_CHANCE_MARK_MAGIC = 50;
const int SpellcastingAction::PCT_CHANCE_MARK_CATEGORY = 80;

ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  CurrentCreatureAbilities cca;

  // used to determine whether a spell was selected in the spellcasting screen.
  // if so, the spell will be cast at the end of the process.
  string spell_id;

  if (cca.can_speak(creature, true) && cca.can_focus(creature, true))
  {
    MagicalAbilityChecker mac;

    if (mac.has_magical_knowledge(creature) == false)
    {
      if (creature->get_is_player())
      {
        add_no_magical_knowledge_message(creature);
      }
    }
    else
    {
      Game& game = Game::instance();
      MapPtr current_map = game.get_current_map();

      if (current_map && current_map->get_map_type() == MapType::MAP_TYPE_WORLD)
      {
        add_invalid_spellcasting_location_message(creature);
      }
      else
      {
        pair<string, ActionCostValue> spell_details = cast_spell_on_valid_map_type(creature);
        spell_id = spell_details.first;
        action_cost_value = spell_details.second;
      }
    }
  }

  if ((action_cost_value > 0) && !spell_id.empty())
  {
    // First, re-display the contents of the map screen, since we would
    // have selected from a screen (in a different window):
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
    game.get_display()->redraw();

    // Indicate that a full redraw is needed.
    game.get_loaded_map_details_ref().update_spell_cast(true);

    action_cost_value = cast_spell(creature, spell_id);
  }

  return action_cost_value;
}

pair<string, ActionCostValue> SpellcastingAction::cast_spell_on_valid_map_type(CreaturePtr creature) const
{
  pair<string, ActionCostValue> selection_details("", 0);
  bool cast_spells = true;

  if (creature->get_is_player())
  {
    while (cast_spells)
    {
      pair<bool, pair<string, ActionCostValue>> cur_selection_details = process_spellcasting_selection(creature);
      cast_spells = cur_selection_details.first;
      selection_details = cur_selection_details.second;
    }
  }
  else
  {
    // JCD FIXME - Change this once creatures with magic are added to AI
    // considerations...
  }

  return selection_details;
}

// Cast a particular spell by a particular creature.
ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature, const string& spell_id, const Direction preselected_direction) const
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  CurrentCreatureAbilities cca;

  if (creature && cca.can_speak(creature))
  {
    Game& game = Game::instance();
    const SpellMap& spells = game.get_spells_ref();
    auto s_it = spells.find(spell_id);
    Spell spell;

    if (s_it != spells.end())
    {
      spell = s_it->second;

      MagicalAbilityChecker mac;
      if (!GameUtils::is_magic_category_possible(spell.get_magic_category()))
      {
        add_no_deities_message(creature);
      }
      else
      {
        // Check to see if the creature has the AP for the spell.
        if (mac.has_sufficient_power(creature, spell))
        {
          action_cost_value = spell.get_speed();

          MapPtr current_map = game.get_current_map();
          Coordinate caster_coord = current_map->get_location(creature->get_id());

          // Reduce the creature's AP by the spell cost.
          reduce_caster_ap_by_spell_cost(creature, spell);

          // A check to see if spellcasting succeeded.  If the spell is directional
          // and a proper direction isn't selected, this will cause the magic 
          // to fail.
          bool spellcasting_succeeded = true;
          Direction spell_direction = Direction::DIRECTION_NORTH;

          // Is a direction needed?
          if (spell.get_shape().get_direction_category() != DirectionCategory::DIRECTION_CATEGORY_NONE)
          {
            if (preselected_direction != Direction::DIRECTION_NULL)
            {
              spell_direction = preselected_direction;
            }
            else
            {
              pair<bool, Direction> direction_pair = get_spell_direction_from_creature(creature, spell, spell_direction);
              spellcasting_succeeded = direction_pair.first; // Can the input be converted to a dir?
              spell_direction = direction_pair.second; // The actual direction, or the initial value if action conversion didn't work.

              if (!spellcasting_succeeded)
              {
                action_cost_value = ActionCostConstants::NO_ACTION;
              }
            }
          }

          if (spellcasting_succeeded == false)
          {
            IMessageManager& man = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
            man.add_new_message(ActionTextKeys::get_spellcasting_cancelled_message(creature->get_description_sid(), creature->get_is_player()));
          }
          else
          {
            // Casting a spell always involves a verbal component, which breaks the
            // Silent conduct.
            creature->get_conducts_ref().break_conduct(ConductType::CONDUCT_TYPE_SILENT);
            CreaturePtr player = Game::instance().get_current_player();

            Game::instance().get_sound()->play(SoundEffectID::SPELL);

            // Add an appropriate casting message.
            string cast_message = ActionTextKeys::get_spellcasting_message(spell, player, creature, creature->get_is_player());
            manager.add_new_message(cast_message);

            // Reduce castings by one, removing the spell if there are none left.
            reduce_castings_or_remove_spell(creature, spell);

            // Mark the spell as the most recently cast.
            SpellKnowledge& sk = creature->get_spell_knowledge_ref();
            sk.set_most_recently_cast_spell_id(spell_id);
            IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);

            // Process the spell shape.
            SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(spell.get_shape().get_spell_shape_type());

            if (spell_processor != nullptr)
            {
              SpellcastingProcessor sp;

              // Track the last cast spell in case it kills the target and
              // the target is the player and needs it for a character dump.
              creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_SPELL_IN_PROGRESS, spell_id);

              // Spells always use the "uncursed" effect status.
              sp.process(spell_processor.get(), creature, current_map, caster_coord, spell_direction, spell, isk.get_bonus().get_base(), ItemStatus::ITEM_STATUS_UNCURSED, AttackType::ATTACK_TYPE_MAGICAL);

              creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_SPELL_IN_PROGRESS);

              // Train the creature's magic skills
              train_skills(creature, spell);

              // Indicate that a full redraw is needed.
              game.get_loaded_map_details_ref().update_spell_cast(true);
            }

            // Now that the spell has been cast, update the spell bonus information
            update_spell_bonus(creature, spell);
          }

          // Send the cast message and any messages generating by hitting other
          // creatures, etc.
          manager.send();
        }
        else
        {
          add_insufficient_power_message(creature);
        }
      }
    }
  }

  return action_cost_value;
}

void SpellcastingAction::update_spell_bonus(CreaturePtr caster, const Spell& spell) const
{
  string spell_id = spell.get_spell_id();

  SpellKnowledge& sk = caster->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);

  SpellBonusUpdater sbu;
  bool bonus_updated = sbu.add_successful_casting(isk);
  sk.set_spell_knowledge(spell_id, isk);
  
  if (bonus_updated && caster->get_is_player())
  {
    add_spell_bonus_increased_message(caster);

    // When the spellcasting bonus is updated, the creature's willpower is
    // trained.
    StatisticsMarker sm;
    sm.mark_willpower(caster);
  }
}

void SpellcastingAction::train_skills(CreaturePtr creature, const Spell& spell) const
{
  if (creature != nullptr)
  {
    // Mark the applicable skills.
    vector<pair<SkillType, int>> marked_skills = {{SkillType::SKILL_GENERAL_MAGIC, PCT_CHANCE_MARK_MAGIC},
                                                  {spell.get_magic_category(), PCT_CHANCE_MARK_CATEGORY}};

    for (const auto& skill_pair : marked_skills)
    {
      SkillManager sm;

      if (RNG::percent_chance(skill_pair.second))
      {
        sm.mark_skill(creature, skill_pair.first, true);
      }
    }
  }
}

// Add a message about the spell bonus increasing.
void SpellcastingAction::add_spell_bonus_increased_message(CreaturePtr creature) const
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_BONUS_INCREASED));
  manager.send();
}

// Add a message that the player has no magical knowledge
void SpellcastingAction::add_no_magical_knowledge_message(CreaturePtr creature) const
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_NO_MAGICAL_KNOWLEDGE));
  manager.send();
}

// Add a message that spells can't be cast here (basically, world map)
void SpellcastingAction::add_invalid_spellcasting_location_message(CreaturePtr creature) const
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_UNAVAILABLE_ON_WORLD_MAP));
  manager.send();
}

// Add a message about not having enough AP.
void SpellcastingAction::add_insufficient_power_message(CreaturePtr creature) const
{
  IMessageManager& manager = MM::instance();

  if (creature && creature->get_is_player())
  {
    manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_INSUFFICIENT_POWER));
    manager.send();
  }
}

void SpellcastingAction::add_no_deities_message(CreaturePtr creature) const
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(SpellcastingTextKeys::SPELLCASTING_DIVINE_MAGIC_NO_DEITIES));
  manager.send();
}

ActionCostValue SpellcastingAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 1;
}

// Reduce the spellcaster's AP by the amount specified by the spell
void SpellcastingAction::reduce_caster_ap_by_spell_cost(CreaturePtr caster, const Spell& spell) const
{
  Statistic new_ap = caster->get_arcana_points();
  new_ap.set_current(new_ap.get_current() - spell.get_ap_cost());
  caster->set_arcana_points(new_ap);
}

// Reduce the number of castings by 1.  If there are 0 castings left, "remove" the
// spell by setting its castings to 0.  Keeping the spell around ensures that any
// bonuses, etc., remain after "re-learning" the spell.
void SpellcastingAction::reduce_castings_or_remove_spell(CreaturePtr caster, const Spell& spell) const
{
  string spell_id = spell.get_spell_id();

  SpellKnowledge& sk = caster->get_spell_knowledge_ref();
  IndividualSpellKnowledge isk = sk.get_spell_knowledge(spell_id);
  int new_castings = isk.get_castings() - 1;
  isk.set_castings(new_castings);
  sk.set_spell_knowledge(spell_id, isk);
}

// Get a direction for the spell from the creature.
// Also get whether the direction was "converted" properly from the base command
// (ie, was it a direction command?)
pair<bool, Direction> SpellcastingAction::get_spell_direction_from_creature(CreaturePtr creature, const Spell& spell, const Direction spell_direction) const
{
  bool direction_conversion_ok = true;
  Direction direction = spell_direction;

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  // Make the creature select a direction.
  CommandFactoryPtr command_factory = std::make_unique<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    string direction_prompt_sid = ActionTextKeys::ACTION_GET_DIRECTION;
    if (spell.get_shape().get_direction_category() == DirectionCategory::DIRECTION_CATEGORY_CARDINAL)
    {
      direction_prompt_sid = ActionTextKeys::ACTION_GET_CARDINAL_DIRECTION;
    }

    manager.add_new_message(StringTable::get(direction_prompt_sid));
    manager.send();
  }

  // Try to get a direction.  This might fail.
  Game& game = Game::instance();
  DisplayPtr display = game.get_display();

  if (display != nullptr)
  {
    display->refresh_current_window();
  }

  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), 0, false);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    DirectionalCommand* dcommand;
    dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

    if (dcommand)
    {
      // Clear the message manager.
      manager.clear_if_necessary();
      
      direction = dcommand->get_direction();
      DirectionCategory dc = spell.get_shape().get_direction_category();

      // Any directional spell must be at least cardinal.
      if (!DirectionUtils::is_cardinal(direction))
      {
        bool is_ordinal = DirectionUtils::is_ordinal(direction);

        // However, some spells (beams, etc) can also be
        // ordinal.
        if (dc == DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL && !is_ordinal)
        {
          direction_conversion_ok = false;
        }

        if (is_ordinal && dc != DirectionCategory::DIRECTION_CATEGORY_CARDINALORDINAL)
        {
          direction_conversion_ok = false;
        }
      }
    }
    else
    {
      direction_conversion_ok = false;
    }
  }
  else
  {
    direction_conversion_ok = false;
  }

  pair<bool, Direction> direction_status(direction_conversion_ok, direction);
  return direction_status;
}

// Process spellcasting selections on the Cast Spells screen. Return false
// if processing should repeat (that is, return false if a spell has been
// selected - return true if the input does not allow exiting the Cast
// Spell screen).
pair<bool, pair<string, ActionCostValue>> SpellcastingAction::process_spellcasting_selection(CreaturePtr creature) const
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  bool cast_spells = true;

  Game& game = Game::instance();
  SpellScreenDisplayStrategyPtr sds = std::make_unique<DefaultSpellScreenDisplayStrategy>();
  SpellSelectionScreen sss(game.get_display(), creature, sds.get());

  string display_s = sss.display();
  int input = display_s.at(0);
  char screen_selection = display_s.at(0);

  string spell_id = sss.get_selected_spell(screen_selection);

  DecisionStrategy* decision_strategy = creature->get_decision_strategy();
  CommandFactoryPtr command_factory    = std::make_unique<MagicCommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_unique<MagicKeyboardCommandMap>();

  if (decision_strategy)
  {
    // Get the actual command, signalling to the decision function that
    // input has been provided (don't try to get the input twice).
    CommandPtr magic_command = decision_strategy->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), &input, false);

    if (magic_command && magic_command->get_name() == MagicCommandKeys::ARCANA)
    {
      screen_selection = static_cast<char>(std::tolower(screen_selection));
      string arcana_id = sss.get_selected_spell(screen_selection);
      magic_command->set_custom_value(ArcanaCommand::ARCANA_ID, arcana_id);
    }

    action_cost_value = MagicCommandProcessor::process(creature, magic_command.get());

    if (action_cost_value > 0 && !spell_id.empty())
    {
      // A spell was selected, and the command processor will have
      // taken care of casting it.  Leave the screen and go back to
      // the map.
      cast_spells = false;
    }
  }

  if (!decision_strategy || action_cost_value == -1)
  {
    cast_spells = false;
  }

  pair<bool, pair<string, ActionCostValue>> selection_and_cost(cast_spells, make_pair(spell_id, action_cost_value));
  return selection_and_cost;
}

ActionCostValue SpellcastingAction::describe_spell(CreaturePtr creature, const string& spell_id)
{
  if (creature != nullptr && !spell_id.empty())
  {
    const SpellMap& spells = Game::instance().get_spells_ref();
    auto s_it = spells.find(spell_id);

    if (s_it != spells.end())
    {
      const Spell& spell = s_it->second;
      Game& game = Game::instance();
      vector<pair<Colour, string>> arcana_text;
      uint width = Game::instance().get_display()->get_width();
      string separator;

      string spell_name = String::centre(StringTable::get(spell.get_spell_name_sid()), width);
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, spell_name));
      arcana_text.push_back(make_pair(Colour::COLOUR_BLACK, separator));
      SpellShape ss = spell.get_shape();

      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::TYPE) + ": " + StringTable::get(ArcanaTextKeys::get_type_sid(spell.get_magic_category()))));
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::CLASSIFICATION) + ": " + StringTable::get(ArcanaTextKeys::get_classification_sid(spell.get_magic_classification()))));
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::SHAPE) + ": " + StringTable::get(ArcanaTextKeys::get_shape_sid(ss.get_spell_shape_type()))));
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::RANGE) + ": " + std::to_string(spell.get_range())));
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::RADIUS) + ": " + std::to_string(ss.get_radius())));
      arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::AP_COST) + ": " + std::to_string(spell.get_ap_cost())));

      bool has_damage = spell.get_has_damage();
      if (has_damage)
      {
        PhaseOfMoonCalculator pomc;
        PhaseOfMoonType phase = pomc.calculate_phase_of_moon(game.get_current_world()->get_calendar().get_seconds());
        MagicalDamageCalculator mdc(phase);
        mdc.set_spell_id(spell_id);
        Damage d = mdc.calculate_base_damage_with_bonuses_or_penalties(creature);
        arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ArcanaTextKeys::DAMAGE) + ": " + d.str()));
      }

      arcana_text.push_back(make_pair(Colour::COLOUR_BLACK, separator));

      TextDisplayFormatter tdf;
      string description = StringTable::get(spell.get_spell_description_sid());
      vector<string> artext = tdf.format_text(description);

      for (const string& line_of_text : artext)
      {
        arcana_text.push_back(make_pair(Colour::COLOUR_WHITE, line_of_text));
      }

      TextDisplayScreen tds(game.get_display(), ScreenTitleTextKeys::SCREEN_TITLE_SPELL_DETAILS, arcana_text, true, {});
      tds.display();
    }
  }

  return ActionCostConstants::NO_ACTION;
}