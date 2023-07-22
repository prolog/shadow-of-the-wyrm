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
  { CreatureSex::CREATURE_SEX_MALE,   { { 1, { {1, { "Aesche", "Ahl", "Arc", "Amn", "Anm", "Arke", "Ashe", "Bal", "Bael", "Bane", "Barg", "Bash", "Bek", "Bel", "Bhel", "Birch", "Boh", "Bonn", "Brae", "Bragg", "Brack", "Cade", "Cael", "Cain", "Cal", "Caln", "Calt", "Carr", "Cas", "Cid", "Claye", "Clyne", "Creel", "Clyve", "Col", "Cole", "Colm", "Corr", "Crane", "Cram", "Crim", "Crom", "Cron", "Crow", "Crowe", "Cyd", "Dal", "Dalle", "Dane", "Dax", "Dun", "East", "Elm", "Eorl", "Erne", "Falk", "Fayne", "Finn", "Fil", "Flick", "Forde", "Froste", "Gael", "Gan", "Garr", "Ged", "Gend", "Gep", "Girn", "Guy", "Heath", "Helm", "Hep", "Holte", "Howa", "Howe", "Hume", "Hur", "Hylt", "Hymm", "Jak", "Jek", "Jax", "Jhair", "Jhain", "Jol", "Jot", "Kharne", "Karr", "Kay", "Kael", "Kel", "Kerr", "Knot", "Kronk", "Krul", "Kyp", "Layne", "Lev", "Llew", "Llyw", "Luh", "Lux", "Mace", "Marr", "Mak", "Mead", "Mill", "Mik", "Miles", "Mirk", "Myrr", "Nashe", "Nil", "Nodd", "North", "Null", "Nye", "Oak", "Orbe", "Pan", "Pat", "Pax", "Pearne", "Peart", "Pin", "Pine", "Pogg", "Puck", "Quip", "Quinn", "Ran", "Rain", "Rex", "Rhode", "Rhun", "Rhon", "Rock", "Rogue", "Rom", "Rone", "Rushe", "Ryne", "Scrip", "Serg", "Shaw", "Shere", "Slade", "Slemp", "Sloan", "Stave", "Stone", "Stork", "Storm", "Tad", "Tal", "Tave", "Tel", "Tep", "Tik", "Tir", "Tok", "Tooke", "Trayne", "Tull", "Tyg", "Varne", "Vayne", "Vel", "Vim", "Wart", "Wel", "Wink", "Wulf", "Wyl", "Wyld", "Wyn", "Zane", "Zann", "Zog", "Zoq" } } } },
                                        { 2, { {1, { "A", "Ad", "Ae", "Ak", "Ahl", "Am", "Amn", "An", "Ar", "Ash", "Ax", "Az", "Ba", "Bad", "Bal", "Bael", "Bar", "Barg", "Bark", "Be", "Bel", "Ben", "Bi", "Bil", "Bo", "Boh", "Bor", "Bra", "Bro", "Brae", "Brag", "Bram", "Bran", "Bren", "Bron", "Bru", "Brun", "Bu", "Bur", "Ca", "Cal", "Caed", "Cael", "Cap", "Cau", "Ce", "Ced", "Ci", "Cir", "Co", "Com", "Crae", "Cral", "Crel", "Da", "Dae", "Dal", "De", "Dea", "Di", "Do", "Dor", "Ea", "Eb", "Ec", "Ed", "Ek", "Em", "En", "Er", "Err", "Ey", "Ez", "Fa", "Fau", "Fei", "Feu", "Fi", "Fie", "Fo", "Fou", "Fu", "Fue", "Ga", "Gad", "Gae", "Gea", "Gra", "Grae", "Gre", "Gu", "Gur", "Ha", "Hae", "Hak", "Hal", "Han", "Haz", "He", "Hel", "Hem", "Hen", "Hep", "I", "Ix", "Ja", "Je", "Jel", "Jha", "Jhe", "Jhi", "Jhu", "Jo", "Ju", "Jul", "Ka", "Kal", "Kan", "Kap", "Kae", "Kau", "Ke", "Kea", "Ko", "Kord", "Kra", "La", "Lae", "Le", "Lla", "Lle", "Lli", "Llo", "Llu", "Lly", "Lo", "Li", "Lu", "Ma", "Me", "Mu", "My", "Myr", "Myz", "Na", "Ne", "Nu", "O", "Oe", "Pa", "Pae", "Pal", "Phe", "Po", "Pol", "Pohl", "Pul", "Qui", "Ra", "Rae", "Re", "Ru", "Sa", "Se", "Sel", "Su", "Sul", "Ta", "Tad", "Tal", "Tam", "Tan", "Tau", "Te", "Tel", "Teu", "Ti", "Tie", "Tik", "Til", "Tei", "Tu", "Tyg", "U", "Va", "Vi", "Wa", "Wau", "We", "Wi", "Xa", "Xe", "Xen", "Ya", "Ye", "Za", "Ze", "Zi", "Zo", "Zu" } },
                                               {2, { "ab", "ac", "ad", "ael", "ag", "am", "an", "as", "at", "ax", "az", "ban", "bak", "bar", "bax", "baz", "bec", "beck", "bek", "bel", "ben", "berm", "bern", "bert", "bik", "cal", "cale", "cel", "ch", "dan", "dar", "den", "el", "es", "ex", "fan", "fax", "fae", "foe", "gan", "gen", "gew", "gon", "gonne", "gor", "gu", "gul", "iac", "ian", "ic", "im", "ix", "jax", "kal", "kam", "kan", "kel", "ken", "kh", "kin", "ko", "kul", "lac", "lal", "lan", "land", "las", "lale", "lel", "ling", "lon", "lec", "lic", "lone", "lul", "mak", "man", "mar", "max", "men", "mer", "mex", "min", "mon", "mor", "mux", "nak", "nel", "nex", "nul", "nuz", "od", "og", "on", "ox", "pa", "pan", "pas", "pul", "pol", "pog", "put", "rad", "ram", "ran", "rax", "red", "rex", "rix", "ro", "ron", "rul", "ryx", "san", "sak", "she", "sir", "sik", "sek", "some", "som", "son", "sz", "tag", "tar", "tal", "tek", "tel", "ten", "til", "tin", "ton", "tyn", "tul", "uc", "uck", "us", "ux", "val", "van", "var", "vax", "ver", "vex", "wad", "wam", "wan", "wel", "wen", "win", "wo", "wu", "xad", "xar", "yak", "yen", "z", "zak", "zar", "zax", "zel", "zek", "zen", "zo", "zu", "zzo"
                                               } } } } } },
  { CreatureSex::CREATURE_SEX_FEMALE, { { 1, { {1, { "Aenn", "Ash", "Brig", "Bae", "Bea", "Belle", "Bie", "Bix", "Blue", "Bron", "Brie", "Bree", "Brea", "Cass", "Cat", "Catte", "Cea", "Cey", "Crea", "Cresse", "Cwen", "Dove", "Elf", "Fae", "Fay", "Faye", "Fey", "Ferne", "Gaile", "Grace", "Gwen", "Hail", "Hil", "Hild", "Hilde", "Hope", "Hyld", "Ia", "Jade", "Jane", "Jass", "Jey", "Jil", "Joyce", "Joye", "Jy", "Kat", "Joye", "Kai", "Kess", "Kell", "Kim", "Kish", "Lark", "Leah", "Lesse", "Lil", "Lish", "Liss", "Liv", "Lune", "Ly", "Lyn", "Mab", "Maeve", "Mer", "Mere", "Nan", "Nea", "Ness", "Nin", "Page", "Pea", "Pesh", "Pish", "Rae", "Rax", "Ros", "Rhe", "Rhenne", "Rue", "Sage", "Saye", "Scout", "Sea", "Shal", "Shae", "Shale", "Shan", "Shay", "Shaye", "Shel", "Shelle", "Shrike", "Skye", "South", "Starre", "Swan", "Swaye", "Syd", "Syl", "Taff", "Tal", "Tash", "Tashe", "Teek", "Teel", "Tass", "Tesse", "Tish", "Vi", "West", "Winn", "Wysp", "Wenne", "Wrenne", "Wy", "Wynne", "Wyspe", "Zaye"} } } },
                                        { 2, { {1, { "A", "Ae", "Ael", "Ai", "Al", "Am", "An", "Ash", "Ba", "Be", "Bea", "Bi", "Ca", "Cae", "Ce", "Cea", "Cen", "Cal", "Cha", "Chal", "Che", "Chel", "Cre", "Da", "Dal", "De", "Dea", "Del", "E", "Ea", "Ei", "Eil", "El", "Fa", "Fal", "Fay", "Fae", "Fe", "Fea", "Fen", "Fey", "Fi", "Fiy", "Ga", "Gae", "Ge", "Gi", "Gie", "I", "Ie", "Is", "Iss", "Je", "Jeh", "Ji", "Ju", "Ka", "Kae", "Kal", "Ke", "Kel", "Kem", "Khu", "Ki", "Kie", "Key", "Ku", "La", "Li", "Lu", "Ly", "Ma", "Mah", "Mar", "Mae", "Me", "Mea", "Mi", "Mie", "Mier", "Mir", "Mu", "Na", "Ne", "Ni", "Ny", "O", "Pa", "Pae", "Pe", "Pea", "Pi", "Po", "Rhe", "Rhi", "Sa", "Se", "Sea", "Sha", "Shae", "Shan", "She", "Shee", "Shi", "Sza", "Szi", "Ta", "Tah", "Tal", "Te", "Tea", "Tel", "Tem", "Tey", "Tha", "The", "Thi", "Thu", "Ti", "Tie", "Til", "Tra", "Tre", "Tri", "Tu", "U", "Vi", "Ve", "We", "Wen", "Xi", "Y", "Ya", "Yu", "Za"}},
                                               {2, { "a", "ba", "bah", "baea", "bea", "beth", "bey", "ca", "caea", "cea", "cey", "ci", "cie", "cy", "da", "daea", "dea", "deth", "di", "dia", "die", "dy", "ea", "fa", "faea", "fea", "fey", "ga", "gaea", "gea", "gie", "gy", "hla", "hlea", "hli", "ja", "jie", "ka", "kaea", "kea", "ki", "kie", "key", "kha", "kka", "la", "laa", "lan", "las", "lea", "lee", "lenne", "ley", "lha", "li", "lii", "lia", "lie", "linne", "lis", "lise", "lisse", "lsa", "lse", "lsie", "lsey", "ly", "lya", "lye", "lyse", "lysse", "ma", "maea", "me", "mea", "mey", "mi", "mie", "my", "na", "naea", "nae", "nea", "ni", "nia", "nie", "ney", "ny", "phea", "phia", "phne", "phrea", "ra", "rae", "rai", "re", "rea", "ri", "ria", "rie", "rin", "ry", "ryn", "sa", "sha", "she", "shi", "shie", "shy", "se", "sey", "si", "sie", "ssa", "ta", "tie", "ty", "va", "vie", "vy", "ya", "xa", "xe", "xi", "xie", "za", "zea", "zie", "zza", "zy"
                                               } } } } } }
};

const map<int, vector<string>> Naming::settlement_syllables =
{
  {
    { 1, { "Ach", "Ad", "Adh", "Adz", "Aed", "Ael", "Aer", "Air", "Al", "Ak", "Am", "Amm", "Amn", "An", "Anm", "Ann", "Ap", "Ar", "Arc", "Ard", "Asp", "Ast", "At", "Atn", "Au", "Ax", "Az", "Bac", "Bak", "Bal", "Bar", "Bek", "Bel", "Cad", "Ced", "Cam", "Cael", "Caer", "Dam", "Dan", "Dar", "Den", "Dip", "Eil", "El", "Em", "En", "Ex", "Ey", "Eye", "Eyx", "Fal", "Fan", "Far", "Gael", "Gan", "Gel", "Gil", "Gon", "Had", "Hal", "Han", "Har", "Hear", "Hu", "Hur", "Im", "In", "Ix", "Ip", "Kal", "Kam", "Kan", "Kat", "Ket", "Kit", "Ox", "Pad", "Pan", "Ran", "Tam", "Tan", "Tar", "Tet", "Sar", "Scar", "Sel", "Sen", "Skar", "Star", "Ux", "Van", "Var", "Ven", "Vid", "Vir", "Y", "Yad", "Yan", "Yar", "Yd", "Yl", "Ytt", "Yu", "Yukh", "Zeh", "Zo", "Zu", "Zy"}},
    { 2, { "a", "e", "i", "o", "u"}},
    { 3, { "bad", "bae", "bakh", "bal", "bag", "ban", "bar", "barr", "bat", "bax", "bec", "beck", "bek", "bel", "bey", "bil", "born", "cach", "cal", "can", "car", "crae", "crael", "crel", "dae", "dal", "dan", "den", "dex", "dil", "dim", "din", "dix", "dor", "el", "fal", "fel", "fil", "gal", "gan", "gap", "gel", "gen", "gil", "gon", "gorn", "ham", "han", "hel", "hem", "hen", "kam", "kan", "kar", "kha", "lan", "lin", "mar", "mi", "na", "nae", "nar", "ni", "ra", "ram", "ran", "ren", "rin", "tae", "tam", "tan", "tap", "tar", "tax", "tem", "wan", "well", "wen", "win", "ya", "yan", "yar", "ye", "yil", "za", "zar", "ze"}}
  }
};

const vector<string> Naming::kell_prefixes = { "Alt", "Caer", "Yl", "Yg", "Yr"};

const map<int, vector<string>> Naming::artifact_syllables =
{
  {
    { 1, {"Ad", "Al", "Alt", "As", "Ast", "At", "Bad", "Bal", "Bael", "Balg", "Bel", "Cad", "Cal", "Cet", "Dab", "Dal", "Dam", "Dan", "Fab", "Fad", "Fag", "Fam", "Fan", "Fang", "Fas", "Gan", "Gol", "Gon", "Has", "I", "Il", "Jad", "Jan", "Kal", "Kam", "Kamn", "Kan", "Kat", "Lil", "Lis", "Mad", "Mag", "Mel", "Mol", "Mul", "Nad", "Nal", "Nag", "Nat", "Oth", "Pad", "Pag", "Pal", "Quid", "Quil", "Quin", "Rad", "Ral", "Ram", "Ran", "Ras", "Sad", "Sal", "Sag", "Samn", "Sed", "Sul", "Tag", "Tal", "Tam", "Ux", "Vad", "Vex", "Yg", "Yl" }},
    { 2, {"a", "e", "i", "o", "u"}},
    { 3, {"ab", "ad", "ag", "an", "ar", "at", "ax", "bad", "bal", "ban", "dal", "del", "din", "el", "en", "fal", "fen", "ful", "rad", "rag", "ramn", "ran", "rin", "rumn", "run", "sen", "sin", "tan", "tat", "ten", "tet", "van", "vin", "vix", "yan", "yar" }}
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
    settlement_name = generate_saint_settlement_name();
  }
  else if (RNG::percent_chance(4))
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

string Naming::generate_saint_settlement_name()
{
  string saint_name = generate_name(CreatureSex::CREATURE_SEX_NOT_SPECIFIED);
  string name = StringTable::get(SettlementTextKeys::SAINT_SETTLEMENT_FORMAT);

  if (RNG::percent_chance(20))
  {
    vector<string> saint_names = String::create_string_vector_from_csv_string(StringTable::get(SettlementTextKeys::SAINT_ADDITIONAL_SETTLEMENT_FORMAT));
    
    if (!saint_names.empty())
    {
      name = saint_names.at(RNG::range(0, saint_names.size() - 1));
    }
  }

  boost::replace_first(name, "%s", saint_name);


  return name;
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
  bool hyphen = false;

  for (int i = 1; i <= num_syllables; i++)
  {
    if (i == 1 || RNG::percent_chance(70))
    {
      vector<string> syllables = settlement_syllables.at(i);

      if (num_syllables == 1 && RNG::percent_chance(10))
      {
        rand_name += kell_prefixes.at(RNG::range(0, kell_prefixes.size() - 1)) + " ";
      }

      if (i == 2 && num_syllables == 2 && RNG::percent_chance(5))
      {
        rand_name += "-";
        hyphen = true;
      }

      // Some hypenated names
      if (num_syllables == 2 && hyphen && RNG::percent_chance(20))
      {
        syllables = settlement_syllables.at(1);
      }

      // Sometimes skip the middle syllable.
      if (num_syllables == 3 && i == 2 && RNG::percent_chance(40))
      {
        continue;
      }

      string syl = syllables.at(RNG::range(0, syllables.size() - 1));
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

string Naming::generate_artifact_name()
{
  string name;

  for (int i = 1; i <= 3; i++)
  {
    vector<string> syllables = artifact_syllables.at(i);

    if (i == 2 && RNG::percent_chance(20))
    {
      continue;
    }

    name = name + syllables.at(RNG::range(0, syllables.size() - 1));
  }

  return name;
}