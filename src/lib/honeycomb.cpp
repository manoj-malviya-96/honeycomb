//
// Created by Manoj Malviya on 8/23/25.
//

#include "honeycomb.h"

#include <iostream>

namespace HoneyComb::Frame {

namespace {

constexpr std::size_t HEX_EDGE_COUNT = 6;

/**
 *  these are offsets from center to each corner of hexagon. We can simply multiply these with edge length to get actual
 * corner positions. So basically math goes like this - angle = π/6 + k * π/3 for k in [0, 5] (6 corners) offset is
 * (x_offset = cos(angle), y_offset = sin(angle)) now corner_x can be calculated as -> center_x + edge_length * x_offset
 *  NOTE:  Precomputed for performance reasons.
 */
const auto HEX_OFFSETS = [] {
    std::array<std::pair<double, double>, HEX_EDGE_COUNT> offsets{};
    constexpr double step_angle = M_PI / 3.0; // 60 degrees.
    for (int k = 0; k < HEX_EDGE_COUNT; ++k) {
        const double angle = static_cast<double>(k) * step_angle;
        offsets[k] = {std::cos(angle), std::sin(angle)};
    }
    return offsets;
}();

constexpr std::array<std::pair<std::size_t, std::size_t>, HEX_EDGE_COUNT> HEX_EDGE_INDEX_PAIR = {
    {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 0}}
};


} // namespace


double calculateApothem(const double edgeLength) { return (std::sqrt(3) / 2.0) * edgeLength; }

std::array<Vertex, HEX_EDGE_COUNT> computeHexagonCorners(const Vertex& center, const double edgeLength) {
    std::array<Vertex, HEX_EDGE_COUNT> corners{};
    for (int k = 0; k < HEX_EDGE_COUNT; ++k) {
        corners[k] = {center.x + edgeLength * HEX_OFFSETS[k].first, center.y + edgeLength * HEX_OFFSETS[k].second};
    }
    return corners;
}

void addHexagonToSkeleton(Skeleton2D& skeleton, const Vertex& center, double edgeLength) {
    const auto corners = computeHexagonCorners(center, edgeLength);
    std::array<VertexIndex, HEX_EDGE_COUNT> indexArrays{};
    std::transform(corners.begin(), corners.end(), indexArrays.begin(), [&skeleton](const Frame::Vertex& v) {
        return skeleton.addVertex(v);
    });
    for (const auto [a, b] : HEX_EDGE_INDEX_PAIR) {
        skeleton.addEdge({indexArrays[a], indexArrays[b]});
    }
}

std::vector<Vertex> computeHexagonCentersInGrid(const std::size_t rows, const std::size_t cols, const double edgeLength) {
    std::vector<Vertex> centers;
    centers.reserve(rows * cols);

    const double apothem = calculateApothem(edgeLength);
    const double x_offset = std::sqrt(std::pow(edgeLength, 2) - std::pow(apothem, 2));
    const double x_step = 2 * edgeLength - x_offset;

    for (auto col = 0; col < cols; ++col) {
        for (auto row = 0; row < rows; ++row) {
            if (rows != 1 && row == rows - 1 && col % 2 != 0) {
                // Skip last row for odd columns to maintain grid shape
                continue;
            }
            const double x = col * x_step;
            const double y = (static_cast<int>(col) % 2 == 0) ? (row * 2 * apothem) : ((row * 2 + 1) * apothem);
            centers.push_back({x, y});
        }
    }
    return centers;
}

Skeleton2D generateHoneyCombSkeleton(const HoneyCombFrameParams& params) {
    Skeleton2D result;
    const auto centers = computeHexagonCentersInGrid(params.cols, params.rows, params.edgeLength);
    for (const auto& center : centers) {
        addHexagonToSkeleton(result, center, params.edgeLength);
    }
    return result;
}


} // namespace HoneyComb::Frame