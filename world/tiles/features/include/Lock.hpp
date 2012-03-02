#pragma once
#include <boost/shared_ptr.hpp>

class Lock
{
};

typedef boost::shared_ptr<Lock> LockPtr;
