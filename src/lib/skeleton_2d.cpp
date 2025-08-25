//
// Created by Manoj Malviya on 8/23/25.
//

#include "skeleton_2d.h"

namespace HoneyComb::Frame {

namespace {
//Todo can we use std::numeric_limits<double>::epsilon() here?
constexpr double eps = 1e-6;
}


VertexIndex Skeleton2D::addVertex(const Vertex& vertex) {
    // Check if vertex already exists, return its index if found
    if (const auto it = m_vertexIndexMap.find(vertex); it != m_vertexIndexMap.end()) {
        return it->second;
    }
    // Otherwise, add the vertex and return its new index
    const std::size_t index = m_vertices.size();
    m_vertices.push_back(vertex);
    m_vertexIndexMap[vertex] = index;
    return index;
}


void Skeleton2D::addEdge(const Edge& edge) { m_edges.insert(edge); }

const std::vector<Vertex>& Skeleton2D::getVertices() const { return m_vertices; }

std::unordered_set<Frame::Edge, Frame::EdgeHasher> Skeleton2D::getEdges() const { return m_edges; }


bool Vertex::operator==(const Vertex& other) const {
    return std::lround(x / eps) == std::lround(other.x / eps) && std::lround(y / eps) == std::lround(other.y / eps);
}

std::size_t VertexHasher::operator()(const Vertex& v) const noexcept {
    const auto rx = static_cast<int>(std::lround(v.x / eps));
    const auto ry = static_cast<int>(std::lround(v.y / eps));
    // Standard combination of hash values: See std;:hash documentation on cppreference.com
    return std::hash<int>{}(rx) ^ (std::hash<int>{}(ry) << 1);
}


Edge::Edge(const VertexIndex& u, const VertexIndex& v) : start(u), end(v) {
    if (start == end) {
        throw std::invalid_argument("Edge cannot connect a vertex to itself.");
    }

    if (start > end) {
        // This ensures that Edge(u, v) is the same as Edge(v, u)
        std::swap(start, end);
    }
}
std::size_t EdgeHasher::operator()(const Edge& e) const noexcept {
    // Standard combination of hash values: See std;:hash documentation on cppreference.com
    return std::hash<std::size_t>{}(e.start) ^ (std::hash<std::size_t>{}(e.end) << 1);
}


} // namespace HoneyComb::Frame