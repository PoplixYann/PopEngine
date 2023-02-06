#pragma once


#define BIT(x) (1 << x)

// This define is used to send this lambda function to an function ptr
// This lambda function take a variadic parameters that send to "fn" which is a function in "this"
// "this" is the object where we want to register the function to an event
// "fn" is call with the args put in the lambda function
//#define PE_BIND_EVENT_FN(fn) [this](auto&& ... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define PE_BIND_EVENT_FN(func) std::bind(&func, this, std::placeholders::_1)