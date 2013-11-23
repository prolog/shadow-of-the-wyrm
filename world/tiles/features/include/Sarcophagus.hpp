#include "Feature.hpp"

class Sarcophagus : public Feature
{
  public:
    Sarcophagus();
    Sarcophagus(const MaterialType material);
    bool operator==(const Sarcophagus& sar) const;

    virtual Feature* clone();

    virtual bool handle();
    virtual bool kick();

    virtual uchar get_symbol() const;

    virtual std::pair<std::string, std::vector<std::string>> get_description_and_replacement_sids() const;

    virtual void set_inscription_sid(const std::string& new_inscription_sid);
    virtual std::string get_inscription_sid() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    virtual std::string get_description_sid() const;

    std::string inscription_sid;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Sarcophagus> SarcophagusPtr;
