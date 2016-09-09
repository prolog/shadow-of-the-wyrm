#include <sstream>
#include <vector>
#include "Environment.hpp"

using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#elif defined(__unix__)
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#error Error: define user name code in Environment.cpp for this configuration.
#endif

using namespace std;

// Return the current player's username.
string Environment::get_user_name()
{
  string user_name;
  
  #ifdef _WIN32
  char username_c[UNLEN+1];
  DWORD dUsername = sizeof(username_c);
  
  GetUserName(username_c, &dUsername);
  user_name = username_c;
  #elif defined(__unix__)
  char username_c[LOGIN_NAME_MAX];
  int rv = getlogin_r(username_c, sizeof(username_c));

  if (rv == 0)
  {
    // Leave the username blank if no user exists.  Anyone can then
    // use the savefile.
  }
  else
  {
    user_name = username_c;
  }
  #else
  static_assert(false, "Unrecognized environment for Environment::get_user_name()");
  #endif
  
  return user_name;
}

// Return the current player's home directory.
string Environment::get_user_home_directory()
{
  ostringstream home_dir;

  #ifdef _WIN32
  // This code is so ugly it makes me die a little.
  //
  // People really did this in the 90s, huh?
  char* buf = 0;
  size_t sz = 0;
  vector<string> env_vars = { "HOMEDRIVE", "HOMEPATH" };

  for (const string& env_var : env_vars)
  {
    // Do you have any idea how much I loathe calling functions that allocate
    // memory and require you to deallocate manually?  Ugh.
    if (_dupenv_s(&buf, &sz, env_var.c_str()) == 0)
    {
      home_dir << buf;
      free(buf);
    }
  }
  #elif defined(__unix__)
  // Less ugly, but still C-ish, ugh.
  struct passwd* pw = getpwuid(getuid());
  home_dir << pw->pw_dir;
  #else
  static_assert(false, "Unrecognized environment for Environment::get_user_home_directory()");
  #endif
  return home_dir.str();
}
