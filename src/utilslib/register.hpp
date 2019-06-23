#ifndef UTILS_REGISTER_HPP
#define UTILS_REGISTER_HPP
#include <functional>
#include <vector>
#include <utilslib/singleton.hpp>

#define UTILSLIB_SINGLETON_CLASS(name)\
    struct singleton##name {};

namespace utilslib{
template <typename CLASS, typename HOOK_TYPE>
class RegisterImpl
{
    private:
        std::vector<HOOK_TYPE> m_register;
    public:
        void add(HOOK_TYPE& value)
        {
            m_register.push_back(value);
        }

        auto begin() const {return m_register.begin();}
        auto end() const {return m_register.end();}

        /// CLASS is used to differentiate between independent registers
        using type = CLASS;
};

template <typename CLASS, typename T>
using Register = Singleton<RegisterImpl<CLASS, T>>;

template <typename CLASS, typename T>
class RegisterIt
{
    public:
    using Register = Singleton<RegisterImpl<CLASS, T>>;
        RegisterIt(T value)
        {
            auto instance = Register::getInstance();
            instance->add(value);
        }
        Register* getInstance() const { return Register::getInstance();}
};
} // utilslib namespace
#endif
