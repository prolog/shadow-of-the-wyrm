#pragma once
#include <iostream>
#include "ClassIdentifiers.hpp"

class Serialize
{
  public:
    static void write_class_id(std::ostream& stream, const ClassIdentifier val);
    static void read_class_id(std::istream& stream, ClassIdentifier& val);

    static void write_size_t(std::ostream& stream, const size_t size);
    static void read_size_t(std::istream& stream, size_t& size);

    static void write_bool(std::ostream& stream, const bool val);
    static void read_bool(std::istream& stream, bool& val);

    static void write_uint(std::ostream& stream, const unsigned int val);
    static void read_uint(std::istream& stream, unsigned int& val);

    static void write_int(std::ostream& stream, const signed int val);
    static void read_int(std::istream& stream, signed int& val);

    static void write_ulonglong(std::ostream& stream, const unsigned long long val);
    static void read_ulonglong(std::istream& stream, unsigned long long& val);

    static void write_double(std::ostream& stream, const double val);
    static void read_double(std::istream& stream, double& val);

    static void write_string(std::ostream& stream, const std::string& val);
    static void read_string(std::istream& stream, std::string& val);
};

