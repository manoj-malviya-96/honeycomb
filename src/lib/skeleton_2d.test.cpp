#include <catch2/catch_test_macros.hpp>
#include "skeleton_2d.h"

TEST_CASE("Check If vertexs added are unique") {
    HoneyComb::Frame::Skeleton2D test;
    test.addVertex({0, 0});
    CHECK(test.getVertices().size() == 1);

    test.addVertex({1, 1});
    CHECK(test.getVertices().size() == 2);

    test.addVertex({0 , 0});
    CHECK(test.getVertices().size() == 2); // Shouldnt increase count
}


TEST_CASE("Check if edges added are unique") {
    HoneyComb::Frame::Skeleton2D test;
    test.addEdge({0, 1});
    test.addEdge({0, 2});
    CHECK(test.getEdges().size() == 2);
    test.addEdge({1, 0});
    CHECK(test.getEdges().size() == 2); // Shouldnt increase count
    test.addEdge({2, 0});
    CHECK(test.getEdges().size() == 2); // Shouldnt increase count
    test.addEdge({1, 2});
    CHECK(test.getEdges().size() == 3);
}