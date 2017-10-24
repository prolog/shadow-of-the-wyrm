#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "ClassIdentifiers.hpp"
#include "ScriptDetails.hpp"
#include "SerializationExceptions.hpp"

class Serialize
{
  public:
    static void write_class_id(std::ostream& stream, const ClassIdentifier val);
    static void read_class_id(std::istream& stream, ClassIdentifier& val);

    static void write_size_t(std::ostream& stream, const size_t size);
    static void read_size_t(std::istream& stream, size_t& size);

    static void write_bool(std::ostream& stream, const bool val);
    static void read_bool(std::istream& stream, bool& val);

    static void write_uchar(std::ostream& stream, const unsigned char val);
    static void read_uchar(std::istream& stream, unsigned char& val);

    static void write_uint(std::ostream& stream, const unsigned int val);
    static void read_uint(std::istream& stream, unsigned int& val);

    static void write_int(std::ostream& stream, const signed int val);
    static void read_int(std::istream& stream, signed int& val);

    static void write_ulong(std::ostream& stream, const unsigned long val);
    static void read_ulong(std::istream& stream, unsigned long& val);

    static void write_longlong(std::ostream& stream, const long long val);
    static void read_longlong(std::istream& stream, long long& val);

    static void write_ulonglong(std::ostream& stream, const unsigned long long val);
    static void read_ulonglong(std::istream& stream, unsigned long long& val);

    static void write_float(std::ostream& stream, const float val);
    static void read_float(std::istream& stream, float& val);

    static void write_double(std::ostream& stream, const double val);
    static void read_double(std::istream& stream, double& val);

    static void write_string(std::ostream& stream, const std::string& val);
    static void read_string(std::istream& stream, std::string& val);
    static void consume_string(std::istream& stream);

    static void write_string_vector(std::ostream& stream, const std::vector<std::string>& val);
    static void read_string_vector(std::istream& stream, std::vector<std::string>& val);

    static void write_string_map(std::ostream& stream, const std::map<std::string, std::string>& val);
    static void read_string_map(std::istream& stream, std::map<std::string, std::string>& val);

    static void write_string_set(std::ostream& stream, const std::set<std::string>& val);
    static void read_string_set(std::istream& stream, std::set<std::string>& val);

    static void write_event_scripts(std::ostream& stream, const EventScriptsMap& event_scripts);
    static void read_event_scripts(std::istream& stream, EventScriptsMap& event_scripts);

    template<class T>
    static void write_enum(std::ostream& stream, T& enum_type)
    {
      int underlying_int = static_cast<int>(enum_type);

      if (stream.good())
      {
        stream.write((char*)&underlying_int, sizeof(underlying_int));
      }
      else
      {
        SerializationException stream_error("Could not write enum");
        throw stream_error;
      }
    }

    template<class T>
    static void read_enum(std::istream& stream, T& enum_type)
    {
      if (stream.good())
      {
        stream.read((char*)&enum_type, sizeof(enum_type));
      }
      else
      {
        SerializationException stream_error("Could not read an enum");
        throw stream_error;
      }
    };
};

