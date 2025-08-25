//
// Created by Manoj Malviya on 8/23/25.
//
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace HoneyComb::Frame {


struct Vertex {
    double x, y;
    bool operator==(const Vertex& other) const;
};
struct VertexHasher {
    std::size_t operator()(const Vertex& v) const noexcept;
};

using VertexIndex = std::size_t;
struct Edge {
    VertexIndex start, end;

    Edge(const VertexIndex& u, const VertexIndex& v);
    bool operator==(const Edge& other) const { return other.start == start && other.end == end; }
};
struct EdgeHasher {
    std::size_t operator()(const Edge& e) const noexcept;
};

/**
 *  2D Skeleton representation using vertices and edges.
 */
class Skeleton2D {
public:
    VertexIndex addVertex(const Vertex& vertex);
    void addEdge(const Edge& edge);

    [[nodiscard]] const std::vector<Vertex>& getVertices() const;
    [[nodiscard]] std::unordered_set<Frame::Edge, Frame::EdgeHasher> getEdges() const;

protected:
    // The order matters and therefore this is a vector
    // But to make sure vertices are unique, using unordered_map to make sure of that.
    // This approach results in optimal performance - aka O(1) for lookup and O(1) for access.
    std::vector<Vertex> m_vertices;
    std::unordered_map<Vertex, std::size_t, VertexHasher> m_vertexIndexMap;

    // Why this a set ? because here indexing doesn't matter, we just need to store unique edges.
    std::unordered_set<Edge, EdgeHasher> m_edges;
};


} // namespace HoneyComb::Frame