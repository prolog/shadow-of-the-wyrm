#pragma once
#include "Skills.hpp"
#include "XMLDataStructures.hpp"

class XMLSkillsReader;

class XMLGeneralSkillsReader
{
  public:
    XMLGeneralSkillsReader();

    friend class XMLSkillsReader;

  protected:
    void parse_general_skills(Skills& skills, const XMLNode& general_skills_node);
};

class XMLWeaponSkillsReader
{
  public:
    XMLWeaponSkillsReader();

    friend class XMLSkillsReader;

  protected:
    void parse_weapon_skills(Skills& skills, const XMLNode& weapon_skills_node);
};

class XMLRangedWeaponSkillsReader
{
  public:
    XMLRangedWeaponSkillsReader();
  
    friend class XMLSkillsReader;

  protected:
    void parse_ranged_weapon_skills(Skills& skills, const XMLNode& ranged_weapon_skills_node);
};

class XMLMagicSkillsReader
{
  public:
    XMLMagicSkillsReader();
  
    friend class XMLSkillsReader;

  protected:
    void parse_magic_skills(Skills& skills, const XMLNode& magic_skills_node);
};

class XMLSkillsReader
{
  public:
    XMLSkillsReader();
    virtual ~XMLSkillsReader();

    Skills get_skills(const XMLNode& skills_node);

  protected:
    XMLGeneralSkillsReader general_skills_reader;
    XMLWeaponSkillsReader weapon_skills_reader;
    XMLRangedWeaponSkillsReader ranged_weapon_skills_reader;
    XMLMagicSkillsReader magic_skills_reader;
};
