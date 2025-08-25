//
// Created by Manoj Malviya on 8/23/25.
//

#include <iostream>
#include "cxxopts.hpp"
#include "honeycomb.h"
#include "vtk_renderer.h"

int main(int argc, char* argv[]) {

    cxxopts::Options options(argv[0], "Honeycomb Frame Generator");
    options.add_options()
        ("r,numRows", "Number of rows in the grid", cxxopts::value<std::size_t>()->default_value("20"))
        ("c,numCols", "Number of columns in the grid", cxxopts::value<std::size_t>()->default_value("20"))
        ("s,edgeLength", "The edge length of a single hexagon", cxxopts::value<double>()->default_value("1.0"))
        ("h,help", "Print usage information");

    const auto result = options.parse(argc, argv);
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return EXIT_SUCCESS;
    }

    const auto numRows = result["numRows"].as<std::size_t>();
    const auto numCols = result["numCols"].as<std::size_t>();
    const auto edgeLength = result["edgeLength"].as<double>();
    const auto skeleton = HoneyComb::Frame::generateHoneyCombSkeleton({numRows, numCols, edgeLength});

    HoneyComb::Renderer::renderSkeleton(skeleton);

    return EXIT_SUCCESS;
}