#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include "Metadata.hpp"
#include "Serialize.hpp"

using namespace std;

void convert_savefile(const string& savefile, const string& outfile);

void convert_savefile(const string& savefile, const string& outfile)
{
  Metadata md;
  int md_version = md.get_metadata_version();

  // Ensure the metadata version matches what SaveConverter expects
  if (md_version != 1)
  {
    ostringstream ss;
    ss << "Metadata version mismatch - expected 1, got " << md_version;

    throw ss.str();
  }

  ofstream ofile(outfile, ios::binary | ios::out);
  ifstream ifile(savefile, ios::binary | ios::in);

  cout << "Converting savefile..." << endl;

  string user_name, version, compilation_details, character_synopsis;
  
  ifile.seekg(0, ifile.end);
  streamoff length = ifile.tellg();
  ifile.seekg(0, ifile.beg);

  Serialize::read_string(ifile, user_name);
  Serialize::read_string(ifile, version);
  Serialize::read_string(ifile, compilation_details);
  Serialize::read_string(ifile, character_synopsis);

  // Clear the username so anyone can read the file.
  user_name.clear();

  // Write the metadata into the new file.
  Serialize::write_string(ofile, user_name);
  Serialize::write_string(ofile, version);
  Serialize::write_string(ofile, compilation_details);
  Serialize::write_string(ofile, character_synopsis);

  // Write the remainder of the input file into the new file.
  streamoff cur_pos = ifile.tellg();
  streamoff rem_size = length - cur_pos;

  char* rem_buffer = new char[static_cast<unsigned int>(rem_size)];
  ifile.read(rem_buffer, rem_size);
  ofile.write(rem_buffer, rem_size);

  cout << "Done!" << endl;
  delete[] rem_buffer;
}

int main(int argc, char** argv)
{
  int return_val = 0;

  try
  {
    Metadata md;
    cout << "Shadow of the Wyrm" << md.get_game_version_synopsis() << " savefile converter" << endl;

    string savefile, outfile;
    namespace po = boost::program_options;
    po::options_description odesc("Options");

    odesc.add_options()
      ("save", po::value<string>(), "Specify savefile")
      ("out", po::value<string>(), "Specify outfile");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, odesc), vm);
    po::notify(vm);

    if (vm.count("save"))
    {
      savefile = vm["save"].as<string>();
    }
    
    if (vm.count("out"))
    {
      outfile = vm["out"].as<string>();
    }

    if (savefile.empty() || outfile.empty())
    {
      cout << "Example usage: SaveConverter --save 214731592.sws --out 214731592.sws.out" << endl << endl;
      cout << "Available options:" << endl << endl;
      cout << " save\t\tSpecify the savefile to convert" << endl;
      cout << " out\t\tSpecify the name of the output file" << endl;
    }
    else
    {
      convert_savefile(savefile, outfile);
    }
  }
  catch (std::exception& e)
  {
    cerr << "Exception: " << e.what();
    return_val = 1;
  }

  return return_val;
}