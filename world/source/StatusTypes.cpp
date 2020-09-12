#include "StatusTypes.hpp"

using namespace std;

StatusIdentifiers::StatusIdentifiers()
{
}

StatusIdentifiers::~StatusIdentifiers()
{
}

bool StatusIdentifiers::is_status_identifier(const string& s)
{
  return ((s == STATUS_ID_POISON) ||
          (s == STATUS_ID_MUTE) ||
          (s == STATUS_ID_PARALYSIS) ||
          (s == STATUS_ID_SLOWNESS) ||
          (s == STATUS_ID_HASTE) ||
          (s == STATUS_ID_STONE) ||
          (s == STATUS_ID_BLOODIED) ||
          (s == STATUS_ID_STUNNED) ||
          (s == STATUS_ID_EXPOSED) ||
          (s == STATUS_ID_DISFIGURED) ||
          (s == STATUS_ID_SPELLBOUND) ||
          (s == STATUS_ID_BLINDED) ||
          (s == STATUS_ID_INCORPOREAL) ||
          (s == STATUS_ID_DRUNK) ||
          (s == STATUS_ID_FLYING) ||
          (s == STATUS_ID_TIMEWALK) ||
          (s == STATUS_ID_SATED) ||
          (s == STATUS_ID_WATER_BREATHING) ||
          (s == STATUS_ID_RAGE) ||
          (s == STATUS_ID_HIDE));
}

// The identifiers just need to be unique within those specified in
// StatusIdentifiers.
const string StatusIdentifiers::STATUS_ID_POISON = "_poison";
const string StatusIdentifiers::STATUS_ID_MUTE = "_mute";
const string StatusIdentifiers::STATUS_ID_PARALYSIS = "_para";
const string StatusIdentifiers::STATUS_ID_SLOWNESS = "_slow";
const string StatusIdentifiers::STATUS_ID_HASTE = "_haste";
const string StatusIdentifiers::STATUS_ID_STONE = "_stone";
const string StatusIdentifiers::STATUS_ID_BLOODIED = "_blood";
const string StatusIdentifiers::STATUS_ID_STUNNED = "_stun";
const string StatusIdentifiers::STATUS_ID_EXPOSED = "_expose";
const string StatusIdentifiers::STATUS_ID_DISFIGURED = "_disf";
const string StatusIdentifiers::STATUS_ID_SPELLBOUND = "_spellb";
const string StatusIdentifiers::STATUS_ID_BLINDED = "_blind";
const string StatusIdentifiers::STATUS_ID_INCORPOREAL = "_incorp";
const string StatusIdentifiers::STATUS_ID_DRUNK = "_drunk";
const string StatusIdentifiers::STATUS_ID_FLYING = "_flying";
const string StatusIdentifiers::STATUS_ID_TIMEWALK = "_timew";
const string StatusIdentifiers::STATUS_ID_SATED = "_sat";
const string StatusIdentifiers::STATUS_ID_WATER_BREATHING = "_wb";
const string StatusIdentifiers::STATUS_ID_RAGE = "_rage";
const string StatusIdentifiers::STATUS_ID_HIDE = "_hide";

#ifdef UNIT_TESTS
#include "unit_tests/StatusTypes_test.cpp"
#endif