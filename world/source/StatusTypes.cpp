#include "StatusTypes.hpp"

using namespace std;

StatusIdentifiers::StatusIdentifiers()
{
}

StatusIdentifiers::~StatusIdentifiers()
{
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
