//
// Created by Manoj Malviya on 8/23/25.
//

#include <iostream>
#include "honeycomb.h"
#include "vtk_renderer.h"


int main() {
    constexpr std::size_t numRows = 20;
    constexpr std::size_t numCols = 20;
    constexpr double cellSize = 1.0;

    const auto skeleton = HoneyComb::Frame::generateHoneyCombSkeleton({numRows, numCols, cellSize});
    HoneyComb::Renderer::renderSkeleton(skeleton);
    return EXIT_SUCCESS;
}