#include <map>
#include "ArcanaTextKeys.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

ArcanaTextKeys::ArcanaTextKeys()
{
}

ArcanaTextKeys::~ArcanaTextKeys()
{
}

const string ArcanaTextKeys::TYPE = "TYPE"; 
const string ArcanaTextKeys::CLASSIFICATION = "CLASSIFICATION"; 
const string ArcanaTextKeys::AP_COST = "AP_COST";
const string ArcanaTextKeys::SHAPE = "SHAPE";
const string ArcanaTextKeys::RADIUS = "RADIUS";
const string ArcanaTextKeys::RANGE = "RANGE";

const string ArcanaTextKeys::ATTACK = "ATTACK";
const string ArcanaTextKeys::HEALING = "HEALING";
const string ArcanaTextKeys::BUFF = "BUFF";
const string ArcanaTextKeys::UTILITY = "UTILITY";
const string ArcanaTextKeys::TARGET_SELF = "TARGET_SELF";
const string ArcanaTextKeys::BEAM = "BEAM";
const string ArcanaTextKeys::REFLECTIVE_BEAM = "REFLECTIVE_BEAM";
const string ArcanaTextKeys::CONE = "CONE";
const string ArcanaTextKeys::BALL = "BALL";
const string ArcanaTextKeys::CROSS = "CROSS";
const string ArcanaTextKeys::STORM = "STORM";
const string ArcanaTextKeys::UNDEFINED = "UNDEFINED";

string ArcanaTextKeys::get_type_sid(const SkillType st)
{
  map<SkillType, string> types = { {SkillType::SKILL_MAGIC_CANTRIPS, SkillTextKeys::SKILL_GENERAL_CANTRIPS},
                                   {SkillType::SKILL_MAGIC_ARCANE, SkillTextKeys::SKILL_MAGIC_ARCANE},
                                   {SkillType::SKILL_MAGIC_DIVINE, SkillTextKeys::SKILL_MAGIC_DIVINE},
                                   {SkillType::SKILL_MAGIC_MYSTIC, SkillTextKeys::SKILL_MAGIC_MYSTIC},
                                   {SkillType::SKILL_MAGIC_PRIMORDIAL, SkillTextKeys::SKILL_MAGIC_PRIMORDIAL} };

  auto t_it = types.find(st);

  if (t_it != types.end())
  {
    return t_it->second;
  }

  return UNDEFINED;
}

string ArcanaTextKeys::get_classification_sid(const MagicClassification mc)
{
  map<MagicClassification, string> classes = { {MagicClassification::MAGIC_CLASSIFICATION_ATTACK, ATTACK},
                                               {MagicClassification::MAGIC_CLASSIFICATION_HEALING, HEALING},
                                               {MagicClassification::MAGIC_CLASSIFICATION_BUFF, BUFF},
                                               {MagicClassification::MAGIC_CLASSIFICATION_UTILITY, UTILITY},
                                               {MagicClassification::MAGIC_CLASSIFICATION_UNDEFINED, UNDEFINED} };

  auto c_it = classes.find(mc);

  if (c_it != classes.end())
  {
    return c_it->second;
  }

  return UNDEFINED;
}

string ArcanaTextKeys::get_shape_sid(const SpellShapeType sst)
{
  map<SpellShapeType, string> shapes = { {SpellShapeType::SPELL_SHAPE_TARGET_SELF, TARGET_SELF},
                                         {SpellShapeType::SPELL_SHAPE_BEAM, BEAM},
                                         {SpellShapeType::SPELL_SHAPE_REFLECTIVE_BEAM, REFLECTIVE_BEAM},
                                         {SpellShapeType::SPELL_SHAPE_CONE, CONE},
                                         {SpellShapeType::SPELL_SHAPE_BALL, BALL},
                                         {SpellShapeType::SPELL_SHAPE_CROSS, CROSS},
                                         {SpellShapeType::SPELL_SHAPE_STORM, STORM}
  };

  auto s_it = shapes.find(sst);

  if (s_it != shapes.end())
  {
    return s_it->second;
  }

  return UNDEFINED;
}
