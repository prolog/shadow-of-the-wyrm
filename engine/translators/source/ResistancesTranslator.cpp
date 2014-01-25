#include <iomanip>
#include <sstream>
#include "global_prototypes.hpp"
#include "ResistancesTranslator.hpp"
#include "ResistanceTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

string ResistancesTranslator::create_description(const Resistances& res)
{
  ostringstream ss;

  if (res.has_resistances_or_vulnerabilities())
  {
    ss << std::fixed << std::setprecision(2) << "{";
    bool first = true;

    for (DamageType dt = DAMAGE_TYPE_SLASH; dt < DAMAGE_TYPE_MAX; dt++)
    {
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

          ss << val << StringTable::get(cur_res->get_abrv_sid());

          first = false;
        }
      }
    }

    ss << "}";
  }

  return ss.str();
}
