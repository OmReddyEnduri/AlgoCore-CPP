#pragma once

#include <vector>
#include <stack>
#include <algorithm>
#include <cstddef>

namespace algocore::graphs {

struct TarjanResult {
    std::vector<std::vector<std::size_t>> components;
    std::vector<std::size_t> component_id;
};

/**
 * @brief Tarjan's algorithm for finding Strongly Connected Components in directed graphs.
 * Runs in O(V + E) time and O(V) space.
 * @param n Number of vertices.
 * @param adj Directed adjacency list.
 */
[[nodiscard]] inline TarjanResult tarjan_scc(
    std::size_t n,
    const std::vector<std::vector<std::size_t>>& adj
) {
    TarjanResult res;
    res.component_id.assign(n, std::numeric_limits<std::size_t>::max());

    std::vector<std::size_t> tin(n, 0);
    std::vector<std::size_t> low(n, 0);
    std::vector<bool> on_stack(n, false);
    std::stack<std::size_t> st;
    std::size_t timer = 0;

    auto dfs = [&](auto& self, std::size_t u) -> void {
        tin[u] = low[u] = ++timer;
        st.push(u);
        on_stack[u] = true;

        for (std::size_t v : adj[u]) {
            if (tin[v] == 0) {
                self(self, v);
                low[u] = std::min(low[u], low[v]);
            } else if (on_stack[v]) {
                low[u] = std::min(low[u], tin[v]);
            }
        }

        if (low[u] == tin[u]) {
            std::vector<std::size_t> scc;
            std::size_t current_scc_idx = res.components.size();
            while (true) {
                std::size_t v = st.top();
                st.pop();
                on_stack[v] = false;
                scc.push_back(v);
                res.component_id[v] = current_scc_idx;
                if (u == v) break;
            }
            res.components.push_back(std::move(scc));
        }
    };

    for (std::size_t i = 0; i < n; ++i) {
        if (tin[i] == 0) {
            dfs(dfs, i);
        }
    }

    return res;
}

} // namespace algocore::graphs
