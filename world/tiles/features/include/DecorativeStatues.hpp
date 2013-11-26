#pragma once
#include "Feature.hpp"

// A number of lightweight, decorative statues that can be generated
// by the StatueGenerator.  These all inherit from the DecorativeStatue.
class DecorativeStatue : public Feature
{
  public:
    DecorativeStatue();

    virtual bool handle() override;
    virtual bool kick() override;
    virtual bool get_is_blocking() const override;

    virtual uchar get_symbol() const override;

    // Purposefully does not implement get_description() - this allows
    // the class to be abstract, and ensures one of the concrete
    // descendents is used.

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


// These classes provide an actual description
class KingDecorativeStatue : public DecorativeStatue
{
  public:
    KingDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class QueenDecorativeStatue : public DecorativeStatue
{
  public:
    QueenDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WarlordDecorativeStatue : public DecorativeStatue
{
  public:
    WarlordDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class KnightDecorativeStatue : public DecorativeStatue
{
  public:
    KnightDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HighPriestDecorativeStatue : public DecorativeStatue
{
  public:
    HighPriestDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SorcerorDecorativeStatue : public DecorativeStatue
{
  public:
    SorcerorDecorativeStatue();
    virtual Feature* clone() override;
    
  protected:
    std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

