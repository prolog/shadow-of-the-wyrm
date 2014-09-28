#include "Feature.hpp"

class Barrel : public Feature
{
  public:
    Barrel();
    virtual Feature* clone() override;

    bool operator==(const Barrel& b) const;

    virtual uchar get_symbol() const override;

    virtual void set_tap(const bool new_tap);
    virtual bool get_tap() const;

    virtual void set_pour_item_id(const std::string& new_pour_item_id);
    virtual std::string get_pour_item_id() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const override;

    bool tap;
    std::string pour_item_id;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
