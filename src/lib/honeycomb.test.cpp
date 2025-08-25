#include "catch.hpp"
#include "honeycomb.h"


TEST_CASE("Check If centers are right") {
    constexpr std::size_t nRows = 1;
    constexpr std::size_t nCols = 2;
    const auto centers = HoneyComb::Frame::computeHexagonCentersInGrid(nRows, nCols, 1.0);
    REQUIRE(centers.size() == nRows * nCols);
    CHECK(centers.at(0) == HoneyComb::Frame::Vertex{0.0, 0.0});
    CHECK(centers.at(1) == HoneyComb::Frame::Vertex{1.5, std::sqrt(3) / 2});
}