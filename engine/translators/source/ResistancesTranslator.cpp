#include <iomanip>
#include <sstream>
#include "global_prototypes.hpp"
#include "ResistancesTranslator.hpp"
#include "ResistanceTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ResistancesDisplayOptions::ResistancesDisplayOptions(const bool new_use_braces, const bool new_use_abbreviations)
: use_braces(new_use_braces), use_abbreviations(new_use_abbreviations)
{
}

bool ResistancesDisplayOptions::get_use_braces() const
{
  return use_braces;
}

bool ResistancesDisplayOptions::get_use_abbreviations() const
{
  return use_abbreviations;
}

string ResistancesTranslator::create_description(const Resistances& res, const ResistancesDisplayOptions& rdo)
{
  ostringstream ss;

  if (res.has_resistances_or_vulnerabilities())
  {
    bool use_braces = rdo.get_use_braces();
    bool use_abrv = rdo.get_use_abbreviations();

    ss << std::fixed << std::setprecision(2);
    
    if (use_braces)
    {
      ss << "{";
    }

    bool first = true;

    for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
    {
      DamageType dt = static_cast<DamageType>(d);
      ResistancePtr cur_res = res.get_resistance(dt);

      if (cur_res != nullptr)
      {
        double val = cur_res->get_value();

        if (!dequal(val, 0.00))
        {
          if (!first)
          {
            ss << " ";
          }

          ss << val;

          if (use_abrv)
          {
            ss << StringTable::get(cur_res->get_abrv_sid());
          }
          else
          {
            ss << " " << StringTable::get(cur_res->get_name_sid());
          }

          first = false;
        }
      }
    }

    if (use_braces)
    {
      ss << "}";
    }
  }

  return ss.str();
}
