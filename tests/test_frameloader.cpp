#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "FrameLoader.h"

TEST_CASE("FrameLoader handles invalid file", "[frameloader]") {
    FrameLoader loader;
    REQUIRE_FALSE(loader.loadVideo("nonexistent.mp4"));
}
