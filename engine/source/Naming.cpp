#include <algorithm>
#include <sstream>
#include "Naming.hpp"
#include "RNG.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

uint Naming::MAXIMUM_NAME_SIZE = 15;
const int Naming::MIN_NAME_SYL = 1;
const int Naming::MAX_NAME_SYL = 2;

const SyllableMap Naming::syllables = 
{
  { CreatureSex::CREATURE_SEX_MALE,   { { 1, { {1, { "Arc", "Ashe", "Bel", "Bane", "Bash", "Bek", "Birch", "Bonn", "Cade", "Cael", "Cain", "Carr", "Cid", "Claye", "Clyve", "Col", "Cole", "Crane", "Crim", "Cyd", "Dane", "Dax", "Dun", "Eorl", "Erne", "Falk", "Fayne", "Finn", "Fil", "Forde", "Froste", "Gael", "Gan", "Garr", "Girn", "Gep", "Heath", "Holte", "Howe", "Hume", "Jak", "Jek", "Jax", "Jot", "Karr", "Kay", "Kerr", "Knot", "Kyp", "Layne", "Lev", "Llew", "Lux", "Mace", "Marr", "Mak", "Mead", "Mill", "Mik", "Miles", "Nashe", "North", "Null", "Nye", "Oak", "Orbe", "Pax", "Peart", "Pin", "Pine", "Puck", "Quip", "Quinn", "Rain", "Rex", "Rhode", "Rock", "Rogue", "Rushe", "Scrip", "Serg", "Shaw", "Slade", "Sloan", "Stone", "Storm", "Tave", "Tel", "Tep", "Tir", "Tull", "Varne", "Vayne", "Vel", "Vim", "Wart", "Wel", "Wulf" } } } },
                                        { 2, { {1, { "A", "Ba", "Be", "Ben", "Bi", "Bil", "Bo", "Ca", "Cal", "Ce", "Ci", "Co", "Com", "Da", "De", "Di", "Do", "Fa", "Fi", "Fo", "Fu", "Gae", "Gea", "Gu", "Gur", "Hae", "Ja", "Je", "Jo", "Ka", "Ke", "Ko", "La", "Le", "Lo", "Li", "Ma", "Me", "Mu", "Na", "Ne", "Nu", "Pa", "Po", "Qui", "Ra", "Re", "Ru", "Sa", "Se", "Sel", "Su", "Sul" "Ta", "Tau", "Tal", "Te", "Tel", "Teu", "Ti", "Tie", "Tei", "Tu", "U", "Va", "Vi", "Wa", "We", "Wi", "Za", "Ze" } },
                                               {2, { "bel", "ben", "bik", "cal", "cale", "cel", "den", "fan", "fax", "fae", "foe", "gon", "gonne", "gor", "gul", "jax", "kal", "kel", "kul", "lal", "lale", "lel", "lon", "lec", "lic", "lone", "lul", "mak", "mar", "mer", "mex", "mux", "nak", "nel", "nex", "nul", "nuz", "pul", "pol", "pog", "put", "rax", "rex", "rix", "rul", "san", "sak", "sir", "sik", "sek", "some", "som", "son", "tag", "tar", "tal", "tel", "ten", "til", "tin", "ton", "tul", "val", "van", "var", "vax", "ver", "vex", "wan", "wen", "win", "xar", "yak", "yen", "zar", "zel", "zek"
                                               } } } } } },
  { CreatureSex::CREATURE_SEX_FEMALE, { { 1, { {1, { "Aenn", "Brig", "Bron", "Brie", "Bree", "Brea", "Cat", "Fay", "Ferne", "Gaile", "Grace", "Hail", "Hil", "Hild", "Jass", "Jil", "Kat", "Kai", "Lark", "Liv", "Lyn", "Mab", "Mere", "Nan", "Page", "Ros", "Rue", "Sage", "Scout", "Shal", "Shae", "Shale", "Shaye", "Shel", "Shrike", "Skye", "Teeg", "Teel", "Tass", "Vi", "Winn", "Wrenne"} } } },
                                        { 2, { {1, { "A", "Cal", "Cha", "Chal", "Che", "E", "El", "I", "Ka", "Ke", "Ki", "Ma", "Me", "Mi", "Na", "Ne", "Ti", "Til", "Tel", "Vi", "Ve", "Wen", "Ya", "Yu"} },
                                               {2, { "ca", "cie", "cy", "da", "dy", "la", "laa", "lie", "lsa", "lse", "lsie", "lsey", "ly", "mey", "mie", "my", "na", "nie", "ney", "ny", "phne", "ra", "rae", "ri", "rie", "rra", "ry", "sa", "se", "sey", "sie", "ta", "tie", "ty", "va", "vie", "vy", "ya", "xie",
                                               } } } } } }
};

Naming::Naming()
{
}

string Naming::generate_name(const CreatureSex sex)
{
  string name = "Spud";

  auto s_it = syllables.find(sex);

  if (s_it != syllables.end())
  {
    auto syl_map = s_it->second;
    int num_syllables = RNG::range(MIN_NAME_SYL, MAX_NAME_SYL);

    auto syl_it = syl_map.find(num_syllables);

    if (syl_it != syl_map.end())
    {
      auto syl_entry = syl_it->second;
      string new_name = create_name(num_syllables, syl_map);

      if (!new_name.empty())
      {
        name = new_name;
      }
    }
  }

  return name;
}

string Naming::clean_name_or_use_default(const string& c_name, const CreatureSex sex)
{
  string name = c_name;
  boost::trim(name);

  name = Naming::clean_name(name);

  if (name.empty())
  {
    name = Naming::generate_name(sex);
  }

  return name;
}

string Naming::create_name(const int num_syllables, const map<int, map<int, vector<string>>>& syl_map_entry)
{
  vector<string> vname;
  auto s_it = syl_map_entry.find(num_syllables);

  if (s_it != syl_map_entry.end())
  {
    map<int, vector<string>> cur_syl = s_it->second;

    if (!cur_syl.empty())
    {
      for (int i = 1; i <= num_syllables; i++)
      {
        auto cs_it = cur_syl.find(i);

        if (cs_it != cur_syl.end())
        {
          vector<string> possible_syllables = cs_it->second;

          if (!possible_syllables.empty())
          {
            string syl = possible_syllables.at(RNG::range(0, possible_syllables.size() - 1));
            vname.push_back(syl);
          }
        }
      }
    }
  }

  ostringstream ss;

  for (const string& syl : vname)
  {
    ss << syl;
  }

  return ss.str();
}

string Naming::clean_name(const string& name)
{
  string new_name = name;

  if (new_name.size() > 0)
  {
    size_t new_name_length = min(new_name.size(), MAXIMUM_NAME_SIZE);
    new_name = new_name.substr(0, new_name_length);
  }

  return new_name;
}

uint Naming::get_max_name_size()
{
  return MAXIMUM_NAME_SIZE;
}
