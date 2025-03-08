#include <sstream>
#include <vector>
#include <boost/algorithm/string/trim.hpp> 
#include <boost/filesystem.hpp>
#include "Conversion.hpp"
#include "Environment.hpp"
#include "FileWriter.hpp"
#include "Setting.hpp"

using namespace std;

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#ifndef __unix__  // Probably MacOS
#define __unix__          // This define is used later
#define LOGIN_NAME_MAX 30 // MacOS doesn't define this
#endif
#include <limits.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
#error Error: define user name code in Environment.cpp for this configuration.
#endif

using namespace std;

string Environment::get_log_directory(const Settings* settings)
{
  string log_directory;

  if (settings != nullptr)
  {
    log_directory = File::harmonize_dirname(settings->get_setting(Setting::LOG_DIR));
    boost::algorithm::trim(log_directory);
  }

  if (log_directory.empty())
  {
    log_directory = "logs";
    log_directory.append(1, FS_PATH_SEPARATOR);
  }

  return log_directory;
}

bool Environment::create_userdata_directory(const Settings* settings)
{
  bool created = false;

  string userdata_dir = get_userdata_directory(settings);
  string user_home_dir = get_user_home_directory();

  // Only try to create the directory if it's in the user's home dir.
  // Leave other directory creation to the sysadmins.
  if (userdata_dir.find(user_home_dir) != std::string::npos)
  {
    boost::filesystem::create_directory(userdata_dir);
  }

  return created;
}

bool Environment::create_empty_user_settings_if_necessary(const Settings* /*settings*/)
{
  bool created = false;

  string dir = Environment::get_userdata_directory(nullptr);
  string ini_file_loc = dir + Settings::SETTINGS_FILENAME;

  FileWriter fw(ini_file_loc);
  ostringstream ss;

  ss << "; This is your personal copy of swyrm.ini.\n";
  ss << "; \n";
  ss << "; You can use this file to override settings from the game's swyrm.ini that\n";
  ss << "; don't start with '_'.  To find the game's copy of swyrm.ini and to see what\n";
  ss << "; you might want to override, look in the main game directory.\n";
  ss << "; \n";

  created = fw.write(ss.str());
  return created;
}

string Environment::get_userdata_directory(const Settings* settings)
{
  string userdata_directory = get_user_home_directory().append(1, FS_PATH_SEPARATOR).append(".sotw").append(1, FS_PATH_SEPARATOR);

  if (settings != nullptr)
  {
    string settings_userdata_dir = settings->get_setting(Setting::USERDATA_DIR);
    boost::algorithm::trim(settings_userdata_dir);

    if (!settings_userdata_dir.empty())
    {
      userdata_directory = settings_userdata_dir;
    }
  }

  userdata_directory = File::harmonize_dirname(userdata_directory);
  return userdata_directory;
}

string Environment::get_syschardump_directory(const Settings* settings)
{
  string syschardump_directory = ".";

  if (settings != nullptr)
  {
    string settings_syschardump_dir = settings->get_setting(Setting::SYSCHARDUMP_DIR);
    boost::algorithm::trim(settings_syschardump_dir);

    if (!settings_syschardump_dir.empty())
    {
      syschardump_directory = settings_syschardump_dir;
    }
  }

  syschardump_directory = File::harmonize_dirname(syschardump_directory);
  return syschardump_directory;
}

string Environment::get_scorefile_directory(const Settings* settings)
{
  string scorefile_directory = ".";

  if (settings != nullptr)
  {
    string settings_scorefile_dir = settings->get_setting(Setting::SCOREFILE_DIR);
    boost::algorithm::trim(settings_scorefile_dir);

    if (!settings_scorefile_dir.empty())
    {
      scorefile_directory = settings_scorefile_dir;
    }
  }

  scorefile_directory = File::harmonize_dirname(scorefile_directory);
  return scorefile_directory;
}

bool Environment::check_scorefile_write_permissions(const Settings* settings)
{
  bool can_write = true;

  string fname = get_scorefile_directory(settings) + "test";
  std::ofstream test_file;
  test_file.open(fname, ios::out | ios::binary);

  if (!test_file.good())
  {
    can_write = false;
  }
  else
  {
    test_file.close();
    std::remove(fname.c_str());
  }

  return can_write;
}

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

  if (rv != 0)
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
