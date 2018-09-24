#include <gtest/gtest.h>

#include <function_extractor/exceptions.hpp>
#include <test_utils/make_all_members_public.hpp>
#include <function_extractor/function_loader.hpp>
#include <test_utils/static_class_assertions.hpp>
#include <test_utils/test_utils.hpp>

#include "helpers.hpp"

namespace
{
namespace function_extractor = burda::function_extractor;
namespace test_utils = burda::test_utils;
namespace testing = function_extractor::testing;

using function_loader = function_extractor::function_loader;

TEST(function_loader, static_assertions)
{
    test_utils::assert_default_constructibility<function_loader, false>();
    test_utils::assert_copy_constructibility<function_loader, false>();
    test_utils::assert_move_constructibility<function_loader, false>();
}

TEST(library_loader, construction_destruction)
{
    test_utils::assert_construction_and_destruction<function_loader>(testing::get_demo_library_file_path());
    EXPECT_THROW(function_loader{ "foo" }, function_extractor::exceptions::library_load_failed);
    EXPECT_NO_THROW(function_loader{ "./subdirectory/another/demo-library.dll" });
}

TEST(library_loader, default_values)
{
    function_loader loader{ testing::get_demo_library_file_path() };
    EXPECT_NE(&loader.library, nullptr);
}

TEST(library_loader, get_procedure)
{
    function_loader loader{ testing::get_demo_library_file_path() };

    {
        const auto func_void_no_params = loader.get_procedure<void()>("function_with_no_params");

        EXPECT_NO_THROW(func_void_no_params());
    }

    {
        const auto func_with_return_value_and_params = loader.get_procedure<int(float, const char *)>("function_with_return_value_and_params");
        int returnedValue = 0;
        EXPECT_NO_THROW(returnedValue = func_with_return_value_and_params(2.3f, "foo-bar-baz"));
        EXPECT_EQ(returnedValue, 999);
    }

    {
        EXPECT_THROW(loader.get_procedure<int(float, const char *)>("function_that_does_not_exists"), function_extractor::exceptions::function_does_not_exist);
    }
}
}
