#include <algorithm>
#include <sstream>
#include <boost/algorithm/string/replace.hpp>
#include "Conversion.hpp"
#include "Naming.hpp"
#include "RNG.hpp"
#include "SettlementTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

uint Naming::MAXIMUM_NAME_SIZE = 15;
const int Naming::MIN_NAME_SYL = 1;
const int Naming::MAX_NAME_SYL = 2;

const SyllableMap Naming::syllables = 
{
  { CreatureSex::CREATURE_SEX_MALE,   { { 1, { {1, { "Aesche", "Arc", "Arke", "Ashe", "Bel", "Bane", "Bash", "Bek", "Birch", "Bonn", "Brae", "Cade", "Cael", "Cain", "Cal", "Carr", "Cid", "Claye", "Clyne", "Creel", "Clyve", "Col", "Cole", "Corr", "Crane", "Crim", "Crow", "Crowe", "Cyd", "Dane", "Dax", "Dun", "East", "Elm", "Eorl", "Erne", "Falk", "Fayne", "Finn", "Fil", "Forde", "Froste", "Gael", "Gan", "Garr", "Girn", "Gep", "Heath", "Helm", "Holte", "Howa", "Howe", "Hume", "Jak", "Jek", "Jax", "Jot", "Karr", "Kay", "Kel", "Kerr", "Knot", "Kyp", "Layne", "Lev", "Llew", "Lux", "Mace", "Marr", "Mak", "Mead", "Mill", "Mik", "Miles", "Mirk", "Myrr", "Nashe", "Nodd", "North", "Null", "Nye", "Oak", "Orbe", "Pan", "Pat", "Pax", "Pearne", "Peart", "Pin", "Pine", "Pogg", "Puck", "Quip", "Quinn", "Ran", "Rain", "Rex", "Rhode", "Rhun", "Rhon", "Rock", "Rogue", "Rom", "Rone", "Rushe", "Ryne", "Scrip", "Serg", "Shaw", "Shere", "Slade", "Sloan", "Stave", "Stone", "Stork", "Storm", "Tave", "Tel", "Tep", "Tik", "Tir", "Tull", "Varne", "Vayne", "Vel", "Vim", "Wart", "Wel", "Wink", "Wulf", "Wyld", "Zane", "Zann", "Zog", "Zoq" } } } },
                                        { 2, { {1, { "A", "Ae", "Ash", "Ax", "Az", "Ba", "Bal", "Be", "Bel", "Ben", "Bi", "Bil", "Bo", "Bor", "Bro", "Brae", "Bran", "Bren", "Bron", "Brun", "Bu", "Ca", "Cal", "Caed", "Cael", "Cap", "Cau", "Ce", "Ced", "Ci", "Co", "Com", "Crae", "Cral", "Crel", "Da", "Dae", "De", "Dea", "Di", "Ea", "Ek", "Do", "Fa", "Fo", "Fu", "Fue", "Gae", "Gea", "Gra", "Grae", "Gre", "Gu", "Gur", "Ha", "Hae", "Hak", "Haz", "He", "Hel", "I", "Ja", "Je", "Jel", "Jo", "Jul", "Ka", "Kae", "Kau", "Ke", "Kea", "Ko", "Kord", "Kra", "La", "Lae", "Le", "Lo", "Li", "Ma", "Me", "Mu", "Myr", "Na", "Ne", "Nu", "O", "Oe", "Pa", "Pae", "Pal", "Pul", "Po", "Qui", "Ra", "Rae", "Re", "Ru", "Sa", "Se", "Sel", "Su", "Sul", "Ta", "Tau", "Tal", "Te", "Tel", "Teu", "Ti", "Tie", "Tik", "Til", "Tei", "Tu", "U", "Va", "Vi", "Wa", "Wau", "We", "Wi", "Xa", "Xe", "Xen", "Ya", "Ye", "Za", "Ze", "Zi", "Zo", "Zu" } },
                                               {2, { "ac", "ag", "ax", "ban", "bak", "bax", "baz", "bel", "ben", "bern", "bert", "bik", "cal", "cale", "cel", "den", "ex", "fan", "fax", "fae", "foe", "gan", "gen", "gon", "gonne", "gor", "gul", "iac", "ian", "ic", "im", "ix", "jax", "kal", "kam", "kan", "kel", "kin", "kul", "lac", "lal", "lan", "land", "las", "lale", "lel", "lon", "lec", "lic", "lone", "lul", "mak", "man", "mar", "men", "mer", "mex", "min", "mon", "mor", "mux", "nak", "nel", "nex", "nul", "nuz", "pul", "pol", "pog", "put", "ran", "rax", "rex", "rix", "ro", "rul", "san", "sak", "sir", "sik", "sek", "some", "som", "son", "tag", "tar", "tal", "tel", "ten", "til", "tin", "ton", "tul", "uc", "uck", "ux", "val", "van", "var", "vax", "ver", "vex", "wan", "wen", "win", "wo", "wu", "xar", "yak", "yen", "zar", "zel", "zek"
                                               } } } } } },
  { CreatureSex::CREATURE_SEX_FEMALE, { { 1, { {1, { "Aenn", "Ash", "Brig", "Belle", "Bron", "Brie", "Bree", "Brea", "Cass", "Cat", "Crea", "Dove", "Fae", "Fay", "Fey", "Ferne", "Gaile", "Grace", "Hail", "Hil", "Hild", "Hilde", "Hope", "Ia", "Jass", "Jil", "Kat", "Joye", "Kai", "Kess", "Kell", "Kish", "Lark", "Leah", "Liss", "Liv", "Lyn", "Mab", "Maeve", "Mere", "Nan", "Nea", "Ness", "Page", "Pea", "Rae", "Rax", "Ros", "Rhenne", "Rue", "Sage", "Scout", "Shal", "Shae", "Shale", "Shan", "Shay", "Shaye", "Shel", "Shelle", "Shrike", "Skye", "South", "Swan", "Swaye", "Taff", "Tal", "Teek", "Teel", "Tass", "Tesse", "Tish", "Vi", "West", "Winn", "Wenne", "Wrenne", "Wy", "Zaye"} } } },
                                        { 2, { {1, { "A", "Ae", "Ai", "As", "Ash", "Ba", "Be", "Ca", "Cae", "Ce", "Cen", "Cal", "Cha", "Chal", "Che", "Da", "De", "Del", "E", "Ei", "El", "Fa", "Fay", "Fae", "Fe", "Fen", "Fey", "Fi", "Ga", "Gae", "Ge", "Gi", "Gie", "I", "Ie", "Je", "Ji", "Ka", "Ke", "Kel", "Ki", "Kie", "Key", "Ma", "Mah", "Mar", "Mae", "Me", "Mea", "Mi", "Mie", "Mir", "Na", "Ne", "O", "Pa", "Pae", "Pe", "Pi", "Ni", "Sha", "Shae", "Shan", "She", "Sza", "Szi", "Ta", "Tah", "Tal", "Te", "Tel", "Tem", "Tey", "Ti", "Tie", "Til", "Tu", "U", "Vi", "Ve", "Wen", "Xi", "Ya", "Yu"} },
                                               {2, { "a", "ba", "ca", "ci", "cie", "cy", "da", "di", "die", "dy", "ea", "fa", "ka", "kie", "key", "la", "laa", "lha", "ley", "li", "lie", "linne", "lis", "lise", "lisse", "lsa", "lse", "lsie", "lsey", "ly", "lyse", "lysse", "ma", "me", "mey", "mi", "mie", "my", "na", "nae", "ni", "nie", "ney", "ny", "phne", "ra", "rae", "re", "ri", "ria", "rie", "rra", "ry", "ryn", "sa", "sha", "she", "shi", "shie", "shy", "se", "sey", "si", "sie", "ta", "tie", "ty", "va", "vie", "vy", "ya", "xa", "xe", "xi", "xie",
                                               } } } } } }
};

const map<int, vector<string>> Naming::settlement_syllables =
{
  {
    { 1, { "Ad", "Aed", "Aer", "Alt", "Ap", "Ax", "Bac", "Bak", "Ban", "Cad", "Cam", "Dam", "Dan", "Dar", "Den", "Dip", "El", "Ex", "Ix", "Ip", "Kal", "Kan", "Kat", "Ket", "Kit", "Ox", "Pad", "Pan", "Ran", "Tam", "Tar", "Tet", "Sar", "Scar", "Skar", "Star", "Ux", "Var", "Vid", "Vir", "Yad", "Yan", "Yar"} },
    { 2, { "a", "ae", "e", "i", "o", "da", "dae", "de", "di", "do", "du", "ga", "gae", "ge", "gi", "go", "la", "lae", "le", "li", "lo", "ra", "rae", "re", "ri", "ro", "ru", "sa", "sae", "se", "si", "so", "su"} },
    { 3, { "bal", "ban", "bex", "bil", "can", "car", "dan", "den", "dil", "dix", "el", "fil", "gan", "gap", "gel", "gen", "gil", "gon", "ham", "hem", "kam", "kan", "kar", "tam", "tan", "tap"}}
  }
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

string Naming::generate_settlement_name()
{
  string settlement_name;

  if (RNG::percent_chance(15))
  {
    settlement_name = generate_possessive_settlement_name();
  } 
  else if (RNG::percent_chance(20))
  {
    settlement_name = generate_descriptive_settlement_name();
  }
  else
  {
    settlement_name = generate_random_settlement_name();
  }

  return settlement_name;
}

string Naming::generate_possessive_settlement_name()
{
  string poss_name;

  string name = generate_name(CreatureSex::CREATURE_SEX_NOT_SPECIFIED);
  vector<string> descs = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_DESCRIPTIONS));
  int desc_idx = RNG::range(0, descs.size() - 1);
  string desc_part = descs[desc_idx];

  poss_name = StringTable::get(SettlementTextKeys::POSSESSIVE_SETTLEMENT_FORMAT);
  boost::replace_first(poss_name, "%s1", name);
  boost::replace_first(poss_name, "%s2", desc_part);

  return poss_name;
}

string Naming::generate_descriptive_settlement_name()
{
  string desc_name;

  vector<string> adjs = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_ADJECTIVES));
  vector<string> descs = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_DESCRIPTIONS));

  int dir_idx = RNG::range(0, adjs.size() - 1);
  int desc_idx = RNG::range(0, descs.size() - 1);

  string adj_part = adjs[dir_idx];
  string desc_part = descs[desc_idx];

  desc_name = StringTable::get(SettlementTextKeys::DESCRIPTIVE_SETTLEMENT_FORMAT);
  boost::replace_first(desc_name, "%s1", adj_part);
  boost::replace_first(desc_name, "%s2", desc_part);

  return desc_name;
}

string Naming::generate_random_settlement_name()
{
  string rand_name;
  int num_syllables = RNG::range(1, 3);

  for (int i = 1; i <= num_syllables; i++)
  {
    if (i == 1 || RNG::percent_chance(70))
    {
      const vector<string>& syllables = settlement_syllables.at(i);
      string syl = syllables.at(RNG::range(0, syllables.size() - 1));

      rand_name += syl;
    }
  }

  if (RNG::percent_chance(20))
  {
    vector<string> descs = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_DESCRIPTIONS));

    int desc_idx = RNG::range(0, descs.size() - 1);
    string desc_part = descs[desc_idx];

    string desc_name = StringTable::get(SettlementTextKeys::DESCRIPTIVE_SETTLEMENT_FORMAT);
    boost::replace_first(desc_name, "%s1", rand_name);
    boost::replace_first(desc_name, "%s2", desc_part);

    rand_name = desc_name;
  }

  return rand_name;
}
