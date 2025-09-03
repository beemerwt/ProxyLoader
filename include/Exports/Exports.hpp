#pragma once
#include <array>
#include <string_view>

#ifndef DECLARE_IMPL_NAME
#define DECLARE_IMPL_NAME(fn_name) \
    std::string_view(#fn_name),
#endif