#ifndef UTILS_CALLBACKS_HPP
#define UTILS_CALLBACKS_HPP
#include <functional>
#include <vector>

/// @brief Function-generic callback register mechanism
///
/// Following class enables to create a function-indepedent, yet type safe
/// callback register.
template <typename T>
class Callbacks
{
    public:
        using callbacksStorage_t = std::vector<T>;
        size_t index;
    private:
        callbacksStorage_t m_callbacks;
    public: 
        auto begin()
        {
            return m_callbacks.begin();
        }

        auto end()
        {
            return m_callbacks.end();
        }

        Callbacks() {}
        ///@brief append new callback and return handle. Skips if already appended.
        void add(T func)
        {
            m_callbacks.push_back(func);
        }

        void clear()
        {
            m_callbacks.clear();
        }
};
#endif
