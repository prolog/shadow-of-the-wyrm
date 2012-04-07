#pragma once
#include "Feature.hpp"

// A number of lightweight, decorative statues that can be generated
// by the StatueGenerator.  These all inherit from the DecorativeStatue.
class DecorativeStatue : public Feature
{
  public:
    DecorativeStatue();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_blocking() const;

    virtual uchar get_symbol() const;

    // Purposefully does not implement get_description() - this allows
    // the class to be abstract, and ensures one of the concrete
    // descendents is used.
};


// These classes provide an actual description
class KingDecorativeStatue : public DecorativeStatue
{
  public:
    KingDecorativeStatue();
    
    std::string get_description_sid() const;
};

class QueenDecorativeStatue : public DecorativeStatue
{
  public:
    QueenDecorativeStatue();
    
    std::string get_description_sid() const;
};

class WarlordDecorativeStatue : public DecorativeStatue
{
  public:
    WarlordDecorativeStatue();
    
    std::string get_description_sid() const;
};

class KnightDecorativeStatue : public DecorativeStatue
{
  public:
    KnightDecorativeStatue();
    
    std::string get_description_sid() const;
};

class HighPriestDecorativeStatue : public DecorativeStatue
{
  public:
    HighPriestDecorativeStatue();
    
    std::string get_description_sid() const;
};

class SorcerorDecorativeStatue : public DecorativeStatue
{
  public:
    SorcerorDecorativeStatue();
    
    std::string get_description_sid() const;
};

