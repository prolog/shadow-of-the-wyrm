#pragma once
#include "Feature.hpp"
#include "Symbol.hpp"

class Table : public Feature
{
  public:
    Table(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Table& t) const;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

