#pragma once
#include <fstream>
#include <iostream>
#include "Creature.hpp"
#include "ScoreFileEntry.hpp"

// RAII class representing the high score file.  When constructed, the
// score file will be read (or an exception will be thrown) into a
// data structure representing the file.  The write operation can be
// used to attempt to write a creature to the file - it will return
// true if it was successful, false otherwise.
class ScoreFile
{
  public:
    ScoreFile();
    virtual ~ScoreFile();

    bool write(CreaturePtr creature);

  protected:
    bool version_ok(std::istream& stream);
    bool read_file(std::istream& stream);

    std::multimap<ulonglong, ScoreFileEntry> entries;
};

