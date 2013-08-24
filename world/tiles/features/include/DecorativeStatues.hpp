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
    virtual bool get_is_blocking() const;

    virtual uchar get_symbol() const;

    // Purposefully does not implement get_description() - this allows
    // the class to be abstract, and ensures one of the concrete
    // descendents is used.

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};


// These classes provide an actual description
class KingDecorativeStatue : public DecorativeStatue
{
  public:
    KingDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class QueenDecorativeStatue : public DecorativeStatue
{
  public:
    QueenDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class WarlordDecorativeStatue : public DecorativeStatue
{
  public:
    WarlordDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class KnightDecorativeStatue : public DecorativeStatue
{
  public:
    KnightDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class HighPriestDecorativeStatue : public DecorativeStatue
{
  public:
    HighPriestDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

class SorcerorDecorativeStatue : public DecorativeStatue
{
  public:
    SorcerorDecorativeStatue();
    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

