#include <catch2/catch.hpp>
#include "PluginManager.h"

TEST_CASE("PluginManager fails on invalid path", "[plugin]") {
    PluginManager mgr;
    REQUIRE_FALSE(mgr.loadPlugin("/nonexistent/plugin.so"));
}
