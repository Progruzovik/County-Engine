#ifndef COUNTY_STDENABLESHAREDFROMTHISWRAPPER_HPP
#define COUNTY_STDENABLESHAREDFROMTHISWRAPPER_HPP

#include <memory>

namespace ce {

class StdEnableSharedFromThisWrapper : public std::enable_shared_from_this<StdEnableSharedFromThisWrapper>
{
public:
    virtual ~StdEnableSharedFromThisWrapper() {}

    virtual void onCreated() {}
};

template <typename T, typename... Args>
inline std::shared_ptr<T> createShared(Args &&... args)
{
    auto instance = std::make_shared<T>(std::forward<Args>(args)...);
    instance->onCreated();
    return instance;
}

}

#endif
