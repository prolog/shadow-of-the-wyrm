#pragma once
#include <memory>

class INPCEffectDecider
{
	public:
		virtual ~INPCEffectDecider() = default;
		virtual bool decide() const = 0;
};

using INPCEffectDeciderPtr = std::unique_ptr<INPCEffectDecider>;

