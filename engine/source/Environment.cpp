#include "Environment.hpp"

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#else
#error Error: define user name code in Environment.cpp for this configuration.
#endif

using namespace std;

string Environment::get_user_name()
{
  string user_name;
  
  #ifdef _WIN32
  char username_c[UNLEN+1];
  DWORD dUsername = sizeof(username_c);
  
  GetUserName(username_c, &dUsername);
  user_name = username_c;
  #else
  #endif
  
  return user_name;
}
