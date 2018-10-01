#pragma once

#include <stdexcept>

namespace burda
{
namespace function_loader
{
namespace exceptions
{
struct library_load_failed : public std::runtime_error
{
    explicit library_load_failed(const std::string & path)
        : std::runtime_error{"Could not load library (or its dependencies) at path " + path }
    {
    }
};

struct function_does_not_exist : public std::logic_error
{
    explicit function_does_not_exist(const std::string & name)
        : std::logic_error{ "Could not load function " + name }
    {
    }
};
}
}
}
