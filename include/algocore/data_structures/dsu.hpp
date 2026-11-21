#pragma once

#include <vector>
#include <numeric>
#include <cstddef>
#include <utility>

namespace algocore::ds {

/**
 * @brief Disjoint Set Union (Union-Find) with path compression and union by rank/size.
 * Includes component tracking and component size queries.
 */
class DisjointSetUnion {
public:
    explicit DisjointSetUnion(std::size_t n)
        : parent_(n), size_(n, 1), components_(n) {
        std::iota(parent_.begin(), parent_.end(), 0);
    }

    /**
     * @brief Finds the representative root of element u with path compression.
     */
    [[nodiscard]] std::size_t find(std::size_t u) {
        if (parent_[u] == u) return u;
        return parent_[u] = find(parent_[u]);
    }

    /**
     * @brief Merges sets containing u and v.
     * @return true if merged, false if already in the same set.
     */
    bool unite(std::size_t u, std::size_t v) {
        std::size_t root_u = find(u);
        std::size_t root_v = find(v);
        if (root_u == root_v) return false;

        if (size_[root_u] < size_[root_v]) {
            std::swap(root_u, root_v);
        }
        parent_[root_v] = root_u;
        size_[root_u] += size_[root_v];
        --components_;
        return true;
    }

    /**
     * @brief Checks if u and v belong to the same connected component.
     */
    [[nodiscard]] bool connected(std::size_t u, std::size_t v) {
        return find(u) == find(v);
    }

    /**
     * @brief Returns the size of the component containing u.
     */
    [[nodiscard]] std::size_t component_size(std::size_t u) {
        return size_[find(u)];
    }

    /**
     * @brief Returns total number of disjoint components.
     */
    [[nodiscard]] std::size_t count_components() const noexcept {
        return components_;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return parent_.size();
    }

private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> size_;
    std::size_t components_;
};

} // namespace algocore::ds
