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
  { CreatureSex::CREATURE_SEX_MALE,   { { 1, { {1, { "Aesche", "Arc", "Arke", "Ashe", "Bel", "Bane", "Bash", "Bek", "Birch", "Bonn", "Cade", "Cael", "Cain", "Carr", "Cid", "Claye", "Clyne", "Creel", "Clyve", "Col", "Cole", "Crane", "Crim", "Crow", "Crowe", "Cyd", "Dane", "Dax", "Dun", "East", "Elm", "Eorl", "Erne", "Falk", "Fayne", "Finn", "Fil", "Forde", "Froste", "Gael", "Gan", "Garr", "Girn", "Gep", "Heath", "Holte", "Howe", "Hume", "Jak", "Jek", "Jax", "Jot", "Karr", "Kay", "Kel", "Kerr", "Knot", "Kyp", "Layne", "Lev", "Llew", "Lux", "Mace", "Marr", "Mak", "Mead", "Mill", "Mik", "Miles", "Mirk", "Myrr", "Nashe", "North", "Null", "Nye", "Oak", "Orbe", "Pan", "Pax", "Pearne", "Peart", "Pin", "Pine", "Pogg", "Puck", "Quip", "Quinn", "Ran", "Rain", "Rex", "Rhode", "Rhun", "Rhon", "Rock", "Rogue", "Rone", "Rushe", "Ryne", "Scrip", "Serg", "Shaw", "Slade", "Sloan", "Stave", "Stone", "Stork", "Storm", "Tave", "Tel", "Tep", "Tir", "Tull", "Varne", "Vayne", "Vel", "Vim", "Wart", "Wel", "Wulf" } } } },
                                        { 2, { {1, { "A", "Ae", "Ash", "Ba", "Bal", "Be", "Bel", "Ben", "Bi", "Bil", "Bo", "Bor", "Bro", "Bran", "Bron", "Ca", "Cal", "Caed", "Cau", "Ce", "Ced", "Ci", "Co", "Com", "Da", "Dae", "De", "Di", "Do", "Fa", "Fo", "Fu", "Gae", "Gea", "Gu", "Gur", "Ha", "Hae", "He", "Hel", "Ja", "Je", "Jel", "Jo", "Jul", "Ka", "Kae", "Kau", "Ke", "Kea", "Ko", "Kord", "La", "Lae", "Le", "Lo", "Li", "Ma", "Me", "Mu", "Myr", "Na", "Ne", "Nu", "Oe", "Pa", "Pae", "Po", "Qui", "Ra", "Rae", "Re", "Ru", "Sa", "Se", "Sel", "Su", "Sul", "Ta", "Tau", "Tal", "Te", "Tel", "Teu", "Ti", "Tie", "Til", "Tei", "Tu", "U", "Va", "Vi", "Wa", "Wau", "We", "Wi", "Xa", "Xe", "Xen", "Ya", "Ye", "Za", "Ze" } },
                                               {2, { "ac", "ag", "ax", "bel", "ben", "bik", "cal", "cale", "cel", "den", "ex", "fan", "fax", "fae", "foe", "gan", "gen", "gon", "gonne", "gor", "gul", "iac", "ian", "ic", "ix", "jax", "kal", "kam", "kan", "kel", "kin", "kul", "lal", "lan", "land", "las", "lale", "lel", "lon", "lec", "lic", "lone", "lul", "mak", "man", "mar", "men", "mer", "mex", "mon", "mor", "mux", "nak", "nel", "nex", "nul", "nuz", "pul", "pol", "pog", "put", "ran", "rax", "rex", "rix", "rul", "san", "sak", "sir", "sik", "sek", "some", "som", "son", "tag", "tar", "tal", "tel", "ten", "til", "tin", "ton", "tul", "uc", "uck", "ux", "val", "van", "var", "vax", "ver", "vex", "wan", "wen", "win", "xar", "yak", "yen", "zar", "zel", "zek"
                                               } } } } } },
  { CreatureSex::CREATURE_SEX_FEMALE, { { 1, { {1, { "Aenn", "Ash", "Brig", "Belle", "Bron", "Brie", "Bree", "Brea", "Cass", "Cat", "Dove", "Fay", "Ferne", "Gaile", "Grace", "Hail", "Hil", "Hild", "Hilde", "Hope", "Jass", "Jil", "Kat", "Joye", "Kai", "Kess", "Kell", "Kish", "Lark", "Leah", "Liss", "Liv", "Lyn", "Mab", "Mere", "Nan", "Page", "Pea", "Rae", "Rax", "Ros", "Rhenne", "Rue", "Sage", "Scout", "Shal", "Shae", "Shale", "Shay", "Shaye", "Shel", "Shelle", "Shrike", "Skye", "South", "Swan", "Teek", "Teel", "Tass", "Tesse", "Vi", "West", "Winn", "Wenne", "Wrenne"} } } },
                                        { 2, { {1, { "A", "As", "Ba", "Be", "Ca", "Ce", "Cen", "Cal", "Cha", "Chal", "Che", "Da", "De", "Del", "E", "Ei", "El", "Fa", "Fae", "Fe", "Fen", "Fey", "Fi", "Ga", "Gae", "Ge", "Gi", "Gie", "I", "Ie", "Ka", "Ke", "Kel", "Ki", "Kie", "Key", "Ma", "Mae", "Me", "Mi", "Mie", "Mir", "Na", "Ne", "Pa", "Pe", "Pi", "Ni", "Sha", "She", "Ti", "Til", "Te", "Tel", "Vi", "Ve", "Wen", "Ya", "Yu"} },
                                               {2, { "a", "ba", "ca", "cie", "cy", "da", "die", "dy", "ka", "kie", "key", "la", "laa", "lha", "lie", "lis", "lise", "lsa", "lse", "lsie", "lsey", "ly", "ma", "mey", "mie", "my", "na", "nae", "nie", "ney", "ny", "phne", "ra", "rae", "ri", "rie", "rra", "ry", "ryn", "sa", "sha", "she", "shi", "shie", "shy", "se", "sey", "sie", "ta", "tie", "ty", "va", "vie", "vy", "ya", "xa", "xe", "xi", "xie",
                                               } } } } } }
};

Naming::Naming()
{
}

SyllableMap::const_iterator Naming::find_in_syllables(const CreatureSex cs)
{
  CreatureSex sex = cs;

  if (cs == CreatureSex::CREATURE_SEX_NOT_SPECIFIED)
  {
    if (RNG::percent_chance(50))
    {
      sex = CreatureSex::CREATURE_SEX_MALE;
    }
    else
    {
      sex = CreatureSex::CREATURE_SEX_FEMALE;
    }
  }

  return syllables.find(sex);
}

string Naming::generate_name(const CreatureSex sex)
{
  string name = "Spud";

  auto s_it = find_in_syllables(sex);

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
    size_t new_name_length = std::min<size_t>(new_name.size(), MAXIMUM_NAME_SIZE);
    new_name = new_name.substr(0, new_name_length);
  }

  return new_name;
}

uint Naming::get_max_name_size()
{
  return MAXIMUM_NAME_SIZE;
}
