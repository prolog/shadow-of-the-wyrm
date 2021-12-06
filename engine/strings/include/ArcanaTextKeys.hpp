#pragma once
#include <string>
#include "SkillTypes.hpp"
#include "SpellTypes.hpp"

class ArcanaTextKeys
{
  public:
    static const std::string TYPE;
    static const std::string CLASSIFICATION;
    static const std::string AP_COST;
    static const std::string SHAPE;
    static const std::string RADIUS;
    static const std::string RANGE;

    static std::string get_type_sid(const SkillType st);
    static std::string get_classification_sid(const MagicClassification mc);
    static std::string get_shape_sid(const SpellShapeType sst);

  protected:
    ArcanaTextKeys();
    ~ArcanaTextKeys();

    static const std::string ATTACK;
    static const std::string HEALING;
    static const std::string BUFF;
    static const std::string UTILITY;
    static const std::string TARGET_SELF;
    static const std::string BEAM;
    static const std::string REFLECTIVE_BEAM;
    static const std::string CONE;
    static const std::string BALL;
    static const std::string CROSS;
    static const std::string STORM;
    static const std::string UNDEFINED;
};
