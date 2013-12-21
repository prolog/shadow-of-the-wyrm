#include "Feature.hpp"

class Fountain : public Feature
{
  public:
    Fountain();
    virtual Feature* clone() override;

    virtual bool handle(std::shared_ptr<Tile>, std::shared_ptr<Creature>) override;
    virtual bool kick() override;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
