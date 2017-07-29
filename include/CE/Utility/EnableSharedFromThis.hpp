#ifndef CE_ENABLESHAREDFROMTHIS_HPP
#define CE_ENABLESHAREDFROMTHIS_HPP

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
    return std::dynamic_pointer_cast<T>(shared_from_this());
}

template <typename T>
template <typename U>
std::shared_ptr<U> EnableSharedFromThis<T>::castSharedFromThis()
{
    return std::dynamic_pointer_cast<U>(shared_from_this());
}

}

#endif
