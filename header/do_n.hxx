#include <functional>
template <typename function, typename... Arg> struct object_call_n
{
    decltype(std::bind(function(), Arg()...)) f;
    size_t _n;
    object_call_n(function foo, size_t n, Arg... arg) : f(std::bind(foo, arg...)), _n(n)
    {
    }
    auto operator()() -> decltype(f())
    {
        if (_n)
        {
            --_n;
            return f();
        }
        return decltype(f())();
    }
};