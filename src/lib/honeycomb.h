#pragma once
#include <array>
#include "skeleton_2d.h"

namespace HoneyComb::Frame {

struct HoneyCombFrameParams {
    const std::size_t rows;
    const std::size_t cols;
    const double edgeLength;
};

// Pure function approach here as hexagon is a special type of mesh. No need to go class approach
Vertex computeHexagonCenterInGrid(double col, double row, double edgeLength);
std::array<Vertex, 6> computeHexagonCorners(const Vertex& center, double edgeLength);
std::vector<Vertex> computeHexagonCentersInGrid(std::size_t rows, std::size_t cols, double edgeLength);
void addHexagonToSkeleton(Skeleton2D& skeleton, const Vertex& center, double edgeLength);
Skeleton2D generateHoneyCombSkeleton(const HoneyCombFrameParams& params);

} // namespace HoneyComb::Frame
