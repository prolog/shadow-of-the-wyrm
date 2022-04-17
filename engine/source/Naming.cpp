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
  { CreatureSex::CREATURE_SEX_MALE,   { { 1, { {1, { "Aesche", "Arc", "Amn", "Arke", "Ashe", "Bal", "Bel", "Bane", "Bash", "Bek", "Birch", "Bonn", "Brae", "Cade", "Cael", "Cain", "Cal", "Caln", "Calt", "Carr", "Cas", "Cid", "Claye", "Clyne", "Creel", "Clyve", "Col", "Cole", "Colm", "Corr", "Crane", "Cram", "Crim", "Crom", "Crow", "Crowe", "Cyd", "Dane", "Dax", "Dun", "East", "Elm", "Eorl", "Erne", "Falk", "Fayne", "Finn", "Fil", "Flick", "Forde", "Froste", "Gael", "Gan", "Garr", "Girn", "Gep", "Guy", "Heath", "Helm", "Holte", "Howa", "Howe", "Hume", "Hur", "Hymm", "Jak", "Jek", "Jax", "Jot", "Kharne", "Karr", "Kay", "Kael", "Kel", "Kerr", "Knot", "Kronk", "Krul", "Kyp", "Layne", "Lev", "Llew", "Lux", "Mace", "Marr", "Mak", "Mead", "Mill", "Mik", "Miles", "Mirk", "Myrr", "Nashe", "Nil", "Nodd", "North", "Null", "Nye", "Oak", "Orbe", "Pan", "Pat", "Pax", "Pearne", "Peart", "Pin", "Pine", "Pogg", "Puck", "Quip", "Quinn", "Ran", "Rain", "Rex", "Rhode", "Rhun", "Rhon", "Rock", "Rogue", "Rom", "Rone", "Rushe", "Ryne", "Scrip", "Serg", "Shaw", "Shere", "Slade", "Slemp", "Sloan", "Stave", "Stone", "Stork", "Storm", "Tave", "Tel", "Tep", "Tik", "Tir", "Tok", "Tooke", "Trayne", "Tull", "Tyg", "Varne", "Vayne", "Vel", "Vim", "Wart", "Wel", "Wink", "Wulf", "Wyl", "Wyld", "Wyn", "Zane", "Zann", "Zog", "Zoq" } } } },
                                        { 2, { {1, { "A", "Ad", "Ae", "Ak", "Ar", "Ash", "Ax", "Az", "Ba", "Bad", "Bal", "Be", "Bel", "Ben", "Bi", "Bil", "Bo", "Bor", "Bra", "Bro", "Brae", "Bran", "Bren", "Bron", "Brun", "Bu", "Ca", "Cal", "Caed", "Cael", "Cap", "Cau", "Ce", "Ced", "Ci", "Cir", "Co", "Com", "Crae", "Cral", "Crel", "Da", "Dae", "De", "Dea", "Di", "Ea", "Ed", "Ek", "Do", "Fa", "Fau", "Fo", "Feu", "Fu", "Fue", "Ga", "Gad", "Gae", "Gea", "Gra", "Grae", "Gre", "Gu", "Gur", "Ha", "Hae", "Hak", "Haz", "He", "Hel", "I", "Ja", "Je", "Jel", "Jo", "Jul", "Ka", "Kal", "Kan", "Kap", "Kae", "Kau", "Ke", "Kea", "Ko", "Kord", "Kra", "La", "Lae", "Le", "Lla", "Lle", "Lli", "Llo", "Llu", "Lly", "Lo", "Li", "Ma", "Me", "Mu", "Myr", "Na", "Ne", "Nu", "O", "Oe", "Pa", "Pae", "Pal", "Pul", "Po", "Qui", "Ra", "Rae", "Re", "Ru", "Sa", "Se", "Sel", "Su", "Sul", "Ta", "Tau", "Tal", "Te", "Tel", "Teu", "Ti", "Tie", "Tik", "Til", "Tei", "Tu", "Tyg", "U", "Va", "Vi", "Wa", "Wau", "We", "Wi", "Xa", "Xe", "Xen", "Ya", "Ye", "Za", "Ze", "Zi", "Zo", "Zu" } },
                                               {2, { "ab", "ac", "ad", "ag", "an", "as", "ax", "az", "ban", "bak", "bar", "bax", "baz", "bel", "ben", "berm", "bern", "bert", "bik", "cal", "cale", "cel", "ch", "den", "el", "es", "ex", "fan", "fax", "fae", "foe", "gan", "gen", "gew", "gon", "gonne", "gor", "gu", "gul", "iac", "ian", "ic", "im", "ix", "jax", "kal", "kam", "kan", "kel", "kh", "kin", "ko", "kul", "lac", "lal", "lan", "land", "las", "lale", "lel", "ling", "lon", "lec", "lic", "lone", "lul", "mak", "man", "mar", "max", "men", "mer", "mex", "min", "mon", "mor", "mux", "nak", "nel", "nex", "nul", "nuz", "on", "pa", "pan", "pas", "pul", "pol", "pog", "put", "ran", "rax", "rex", "rix", "ro", "rul", "ryx", "san", "sak", "she", "sir", "sik", "sek", "some", "som", "son", "sz", "tag", "tar", "tal", "tel", "ten", "til", "tin", "ton", "tul", "uc", "uck", "us", "ux", "val", "van", "var", "vax", "ver", "vex", "wan", "wen", "win", "wo", "wu", "xar", "yak", "yen", "z", "zak", "zar", "zax", "zel", "zek", "zen", "zo", "zu", "zzo"
                                               } } } } } },
  { CreatureSex::CREATURE_SEX_FEMALE, { { 1, { {1, { "Aenn", "Ash", "Brig", "Bae", "Bea", "Belle", "Blue", "Bron", "Brie", "Bree", "Brea", "Cass", "Cat", "Catte", "Crea", "Cresse", "Cwen", "Dove", "Elf", "Fae", "Fay", "Fey", "Ferne", "Gaile", "Grace", "Gwen", "Hail", "Hil", "Hild", "Hilde", "Hope", "Ia", "Jade", "Jass", "Jil", "Joyce", "Joye", "Kat", "Joye", "Kai", "Kess", "Kell", "Kim", "Kish", "Lark", "Leah", "Lil", "Lish", "Liss", "Liv", "Lyn", "Mab", "Maeve", "Mer", "Mere", "Nan", "Nea", "Ness", "Page", "Pea", "Rae", "Rax", "Ros", "Rhenne", "Rue", "Sage", "Saye", "Scout", "Sea", "Shal", "Shae", "Shale", "Shan", "Shay", "Shaye", "Shel", "Shelle", "Shrike", "Skye", "South", "Starre", "Swan", "Swaye", "Syd", "Syl", "Taff", "Tal", "Tashe", "Teek", "Teel", "Tass", "Tesse", "Tish", "Vi", "West", "Winn", "Wysp", "Wenne", "Wrenne", "Wy", "Wynne", "Zaye"} } } },
                                        { 2, { {1, { "A", "Ae", "Ael", "Ai", "Al", "Am", "An", "Ash", "Ba", "Be", "Bi", "Ca", "Cae", "Ce", "Cen", "Cal", "Cha", "Chal", "Che", "Chel", "Cre", "Da", "Dal", "De", "Del", "E", "Ei", "El", "Fa", "Fal", "Fay", "Fae", "Fe", "Fea", "Fen", "Fey", "Fi", "Ga", "Gae", "Ge", "Gi", "Gie", "I", "Ie", "Je", "Ji", "Ka", "Kal", "Ke", "Kel", "Kem", "Ki", "Kie", "Key", "La", "Li", "Lu", "Ly", "Ma", "Mah", "Mar", "Mae", "Me", "Mea", "Mi", "Mie", "Mier", "Mir", "Na", "Ne", "O", "Pa", "Pae", "Pe", "Pi", "Ni", "Sa", "Se", "Sea", "Sha", "Shae", "Shan", "She", "Shee", "Sza", "Szi", "Ta", "Tah", "Tal", "Te", "Tea", "Tel", "Tem", "Tey", "Tha", "The", "Thi", "Thu", "Ti", "Tie", "Til", "Tra", "Tre", "Tri", "Tu", "U", "Vi", "Ve", "Wen", "Xi", "Ya", "Yu"} },
                                               {2, { "a", "ba", "baea", "bea", "ca", "caea", "cea", "cey", "ci", "cie", "cy", "da", "daea", "dea", "di", "dia", "die", "dy", "ea", "fa", "ka", "ki", "kie", "key", "kha", "kka", "la", "laa", "lan", "las", "lea", "lenne", "ley", "lha", "li", "lia", "lie", "linne", "lis", "lise", "lisse", "lsa", "lse", "lsie", "lsey", "ly", "lya", "lyse", "lysse", "ma", "me", "mea", "mey", "mi", "mie", "my", "na", "nae", "nea", "ni", "nia", "nie", "ney", "ny", "phne", "ra", "rae", "rai", "re", "rea", "ri", "ria", "rie", "ry", "ryn", "sa", "sha", "she", "shi", "shie", "shy", "se", "sey", "si", "sie", "ssa", "ta", "tie", "ty", "va", "vie", "vy", "ya", "xa", "xe", "xi", "xie", "za", "zie", "zza"
                                               } } } } } }
};

const map<int, vector<string>> Naming::settlement_syllables =
{
  {
    { 1, { "Ach", "Ad", "Adz", "Aed", "Aer", "Al", "Ak", "Alt", "Am", "Amn", "An", "Ap", "Ax", "Bac", "Bak", "Ban", "Bel", "Cad", "Cam", "Cael", "Caer", "Dam", "Dan", "Dar", "Den", "Dip", "El", "Ex", "Fan", "Far", "Gael", "Gan", "Gel", "Gil", "Gon", "Had", "Hal", "Han", "Har", "Hear", "Hur", "Ix", "Ip", "Kal", "Kan", "Kat", "Ket", "Kit", "Ox", "Pad", "Pan", "Ran", "Tam", "Tan", "Tar", "Tet", "Sar", "Scar", "Skar", "Star", "Ux", "Var", "Vid", "Vir", "Yad", "Yan", "Yar", "Zo", "Zu", "Zy"}},
    { 2, { "a", "al", "ae", "ar", "e", "el", "er", "i", "ii", "da", "dae", "de", "di", "do", "du", "ga", "gae", "ge", "gi", "gil", "go", "la", "lae", "le", "li", "lo", "o", "or", "ra", "rae", "re", "ri", "ro", "ru", "sa", "sae", "se", "si", "so", "su", "ta", "te", "to"} },
    { 3, { "bad", "bae", "bakh", "bal", "bag", "ban", "bar", "bat", "bek", "bax", "bex", "bil", "cach", "can", "car", "crae", "dae", "dan", "den", "dex", "dil", "dix", "dor", "el", "fil", "gal", "gan", "gap", "gel", "gen", "gil", "gon", "ham", "hem", "kha", "kam", "kan", "kar", "tae", "tam", "tan", "tap", "tax", "tem", "ya", "yar", "yil", "za", "ze"}}
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

  if (RNG::percent_chance(4))
  {
    settlement_name = generate_single_settlement_name();
  }
  else if (RNG::percent_chance(6))
  {
    settlement_name = generate_locative_settlement_name();
  }
  else if (RNG::percent_chance(13))
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

string Naming::generate_single_settlement_name()
{
  string name = StringTable::get(SettlementTextKeys::SINGLE_SETTLEMENT_FORMAT);
  vector<string> single_prefixes = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_SINGLE_PREFIX));
  vector<string> single_suffixes = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SETTLEMENT_NAME_SINGLE_SUFFIX));

  string prefix = single_prefixes.at(RNG::range(0, single_prefixes.size() - 1));
  string suffix = single_suffixes.at(RNG::range(0, single_suffixes.size() - 1));

  boost::replace_first(name, "%s1", prefix);
  boost::replace_first(name, "%s2", suffix);

  return name;
}

string Naming::generate_locative_settlement_name()
{
  vector<string> locative_formats = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::LOCATED_SETTLEMENT_FORMATS));
  string name = locative_formats.at(RNG::range(0, locative_formats.size() - 1));
  string rand1 = generate_base_random_settlement_name();
  string rand2 = generate_base_random_settlement_name();
  boost::replace_first(name, "%s1", rand1);
  boost::replace_first(name, "%s2", rand2);

  return name;
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

string Naming::generate_base_random_settlement_name()
{
  string rand_name;
  int num_syllables = RNG::range(1, 3);

  for (int i = 1; i <= num_syllables; i++)
  {
    if (i == 1 || RNG::percent_chance(70))
    {
      const vector<string>& syllables = settlement_syllables.at(i);
      string syl = syllables.at(RNG::range(0, syllables.size() - 1));

      if (i == 2 && num_syllables == 2 && RNG::percent_chance(5))
      {
        rand_name += "-";
      }

      // Sometimes skip the middle syllable.
      if (num_syllables == 3 && i == 2 && RNG::percent_chance(40))
      {
        continue;
      }

      rand_name += syl;
    }
  }

  return rand_name;
}

string Naming::generate_random_settlement_name()
{
  string rand_name = generate_base_random_settlement_name();

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
