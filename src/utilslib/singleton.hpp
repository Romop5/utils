#ifndef UTILS_CALLBACKS_HPP
#define UTILS_CALLBACKS_HPP
#include <functional>
#include <vector>

namespace utilslib{
template <typename DECORATED_CLASS>
class Singleton: public DECORATED_CLASS
{
    private:
        Singleton() = default;
    public:
        static Singleton<DECORATED_CLASS>* getInstance()
        {
            static Singleton<DECORATED_CLASS>* ptr = nullptr;
            if(!ptr)
                ptr = new Singleton<DECORATED_CLASS>();
            return ptr;
        }
};
} // utilslib namespace
#endif
