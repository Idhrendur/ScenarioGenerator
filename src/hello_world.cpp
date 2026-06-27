#include "hello_world.hpp"

#pragma warning(push)
#pragma warning(disable : 4702)
#include <fmt/base.h>
#pragma warning(pop)



namespace scenario_generator
{

void HelloWorld()
{
   fmt::println("Hello world!");
}

}  // namespace scenario_generator