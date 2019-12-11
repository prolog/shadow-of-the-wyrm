#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

// JCD SYMBOL SPRITESHEET FIXME
//
// Once features all have their own per-instance symbol, remove most
// of these classes...

// A number of lightweight, decorative statues that can be generated
// by the FeatureGenerator.  These all inherit from the DecorativeStatue.
class DecorativeStatue : public Feature
{
  public:
    DecorativeStatue(const std::string& new_desc_sid, const Symbol& new_symbol);

    virtual bool get_is_blocking() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};


// These classes provide an actual description
class KingDecorativeStatue : public DecorativeStatue
{
  public:
    KingDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class QueenDecorativeStatue : public DecorativeStatue
{
  public:
    QueenDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class WarlordDecorativeStatue : public DecorativeStatue
{
  public:
    WarlordDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class KnightDecorativeStatue : public DecorativeStatue
{
  public:
    KnightDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class HighPriestDecorativeStatue : public DecorativeStatue
{
  public:
    HighPriestDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

class SorcerorDecorativeStatue : public DecorativeStatue
{
  public:
    SorcerorDecorativeStatue(const Symbol& new_symbol);
    virtual Feature* clone() override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
