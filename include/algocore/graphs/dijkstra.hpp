#pragma once

#include <vector>
#include <queue>
#include <limits>
#include <cstddef>
#include <algorithm>

namespace algocore::graphs {

template <typename Weight = long long>
struct Edge {
    std::size_t to;
    Weight weight;
};

template <typename Weight = long long>
struct ShortestPathResult {
    std::vector<Weight> dist;
    std::vector<std::size_t> parent;
    static constexpr Weight INF = std::numeric_limits<Weight>::max();

    [[nodiscard]] bool reachable(std::size_t target) const {
        return dist[target] != INF;
    }

    [[nodiscard]] std::vector<std::size_t> reconstruct_path(std::size_t target) const {
        if (!reachable(target)) return {};
        std::vector<std::size_t> path;
        for (std::size_t curr = target; curr != std::numeric_limits<std::size_t>::max(); curr = parent[curr]) {
            path.push_back(curr);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
};

/**
 * @brief Dijkstra's Single Source Shortest Path with priority queue.
 * @tparam Weight Weight type, defaults to long long.
 * @param n Number of vertices.
 * @param adj Adjacency list representation: adj[u] = list of Edge{to, weight}.
 * @param source Starting vertex.
 */
template <typename Weight = long long>
[[nodiscard]] ShortestPathResult<Weight> dijkstra(
    std::size_t n,
    const std::vector<std::vector<Edge<Weight>>>& adj,
    std::size_t source
) {
    constexpr Weight INF = std::numeric_limits<Weight>::max();
    ShortestPathResult<Weight> res;
    res.dist.assign(n, INF);
    res.parent.assign(n, std::numeric_limits<std::size_t>::max());

    using Pair = std::pair<Weight, std::size_t>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;

    res.dist[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > res.dist[u]) continue;

        for (const auto& edge : adj[u]) {
            if (res.dist[u] + edge.weight < res.dist[edge.to]) {
                res.dist[edge.to] = res.dist[u] + edge.weight;
                res.parent[edge.to] = u;
                pq.emplace(res.dist[edge.to], edge.to);
            }
        }
    }

    return res;
}

} // namespace algocore::graphs
