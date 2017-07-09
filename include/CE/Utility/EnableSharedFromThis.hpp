#ifndef COUNTY_ENABLESHAREDFROMTHIS_HPP
#define COUNTY_ENABLESHAREDFROMTHIS_HPP

#include <CE/Utility/StdEnableSharedFromThisWrapper.hpp>

namespace ce {

template <typename T>
class EnableSharedFromThis : public virtual StdEnableSharedFromThisWrapper
{
public:
    std::shared_ptr<T> sharedFromThis();

    template <typename U>
    std::shared_ptr<U> castSharedFromThis();
};

template <typename T>
std::shared_ptr<T> EnableSharedFromThis<T>::sharedFromThis()
{
    return std::dynamic_pointer_cast<T>(StdEnableSharedFromThisWrapper::shared_from_this());
}

template <typename T>
template <typename U>
std::shared_ptr<U> EnableSharedFromThis<T>::castSharedFromThis()
{
    return std::dynamic_pointer_cast<U>(StdEnableSharedFromThisWrapper::shared_from_this());
}

}

#endif
