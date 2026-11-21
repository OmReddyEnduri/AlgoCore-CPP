#pragma once

#include <vector>
#include <cstddef>
#include <concepts>

namespace algocore::ds {

/**
 * @brief Binary Indexed Tree (Fenwick Tree) supporting point additions and prefix sum queries.
 * 0-indexed interface with internal 1-indexed implementation.
 * @tparam T Arithmetic type supporting addition and subtraction.
 */
template <typename T>
class FenwickTree {
public:
    explicit FenwickTree(std::size_t n) : n_(n), tree_(n + 1, T{}) {}

    explicit FenwickTree(const std::vector<T>& data) : n_(data.size()), tree_(data.size() + 1, T{}) {
        for (std::size_t i = 0; i < n_; ++i) {
            add(i, data[i]);
        }
    }

    /**
     * @brief Adds delta to the element at 0-based index idx.
     */
    void add(std::size_t idx, const T& delta) {
        for (std::size_t i = idx + 1; i <= n_; i += i & -i) {
            tree_[i] += delta;
        }
    }

    /**
     * @brief Returns prefix sum in range [0, idx] inclusive.
     */
    [[nodiscard]] T prefix_sum(std::size_t idx) const {
        if (idx >= n_) idx = n_ - 1;
        T sum = T{};
        for (std::size_t i = idx + 1; i > 0; i -= i & -i) {
            sum += tree_[i];
        }
        return sum;
    }

    /**
     * @brief Returns range sum in range [l, r] inclusive.
     */
    [[nodiscard]] T range_sum(std::size_t l, std::size_t r) const {
        if (l > r || r >= n_) return T{};
        if (l == 0) return prefix_sum(r);
        return prefix_sum(r) - prefix_sum(l - 1);
    }

    [[nodiscard]] std::size_t size() const noexcept { return n_; }

private:
    std::size_t n_;
    std::vector<T> tree_;
};

} // namespace algocore::ds
