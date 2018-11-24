#include "Feature.hpp"

class Table : public Feature
{
  public:
    Table();
    virtual Feature* clone() override;

    bool operator==(const Table& t) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

