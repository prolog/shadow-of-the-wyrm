#pragma once
#include "IMessageManager.hpp"
#include "StringConverter.hpp"

class MessageBufferDumper : public StringConverter
{
  public:
    MessageBufferDumper(const IMessageManager& new_mm, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_messages(const size_t num_messages) const;

    const IMessageManager& mm;
    const size_t num_msgs;
    uint num_cols;

    static const size_t DEFAULT_NUM_MSGS;
};

