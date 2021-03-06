/*
 * defer.hh by F1ssi0N
 *
 * source: https://github.com/josh33901/blue/blob/master/blue/defer.hh
 */

#pragma once

// helper class / macro for creating scope exit actions

template <class Lambda> class AtScopeExit
{
    Lambda &m_lambda;

public:
    AtScopeExit(Lambda &action) : m_lambda(action)
    {
    }
    ~AtScopeExit()
    {
        m_lambda();
    }
};

#define Defer_INTERNAL2(lname, aname, ...)                                     \
    auto lname = [&]() { __VA_ARGS__; };                                       \
    AtScopeExit<decltype(lname)> aname(lname);

#define Defer_TOKENPASTE(x, y) Defer_##x##y

#define Defer_INTERNAL1(ctr, ...)                                              \
    Defer_INTERNAL2(Defer_TOKENPASTE(func_, ctr),                              \
                    Defer_TOKENPASTE(instance_, ctr), __VA_ARGS__)

#define defer(...) Defer_INTERNAL1(__COUNTER__, __VA_ARGS__)
