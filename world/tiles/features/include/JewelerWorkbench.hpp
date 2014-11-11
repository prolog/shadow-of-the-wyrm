#include "Feature.hpp"

class JewelerWorkbench : public Feature
{
  public:
    JewelerWorkbench();
    virtual Feature* clone() override;

    bool operator==(const JewelerWorkbench& j) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
