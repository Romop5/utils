#ifndef UTILS_LOOKUPTABLE_HPP
#define UTILS_LOOKUPTABLE_HPP
#include <functional>
#include <vector>

namespace utilslib{
/**
 * @brief Compile-time LUT builder
 * 
 * The class is used to build a look-up table (LUT) in compile time.
 * See lookuptable.cpp in unittests for usage.
 * 
 * As for my knowledge, this class should require C++14 as FOR cycle is used.
 * 
 * @tparam RESULT_TYPE 
 * @tparam START 
 * @tparam END 
 */
template <typename RESULT_TYPE, unsigned START, unsigned END>
class Lookuptable 
{
    using compute_function_t = std::function<RESULT_TYPE(size_t)>;
    public:
    static constexpr auto computeIt(compute_function_t func) 
    {
        std::array<RESULT_TYPE, END-START> result;
        for(size_t i = START; i < END; i++)
        {
            result[i] = func(i);
        }
        return result;
    }
};
} // utilslib namespace
#endif
