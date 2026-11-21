#pragma once

#include <vector>
#include <functional>
#include <cstddef>
#include <concepts>

namespace algocore::ds {

/**
 * @brief High-performance generic Segment Tree supporting point updates and range queries.
 * @tparam T Value type stored in the tree nodes.
 * @tparam Op Associative binary operation: (T, T) -> T
 */
template <typename T, typename Op = std::plus<T>>
class SegmentTree {
public:
    SegmentTree(std::size_t n, T identity_val = T{}, Op op = Op{})
        : n_(n), identity_(identity_val), op_(op), tree_(4 * n, identity_val) {}

    explicit SegmentTree(const std::vector<T>& data, T identity_val = T{}, Op op = Op{})
        : n_(data.size()), identity_(identity_val), op_(op), tree_(4 * data.size(), identity_val) {
        if (n_ > 0) {
            build(data, 1, 0, n_ - 1);
        }
    }

    /**
     * @brief Updates the element at index idx with new_val.
     */
    void update(std::size_t idx, const T& new_val) {
        update(1, 0, n_ - 1, idx, new_val);
    }

    /**
     * @brief Queries the associative operation over range [ql, qr] inclusive.
     */
    [[nodiscard]] T query(std::size_t ql, std::size_t qr) const {
        if (ql > qr || qr >= n_) return identity_;
        return query(1, 0, n_ - 1, ql, qr);
    }

    [[nodiscard]] std::size_t size() const noexcept { return n_; }

private:
    std::size_t n_;
    T identity_;
    Op op_;
    std::vector<T> tree_;

    void build(const std::vector<T>& data, std::size_t node, std::size_t l, std::size_t r) {
        if (l == r) {
            tree_[node] = data[l];
            return;
        }
        std::size_t mid = l + (r - l) / 2;
        build(data, 2 * node, l, mid);
        build(data, 2 * node + 1, mid + 1, r);
        tree_[node] = op_(tree_[2 * node], tree_[2 * node + 1]);
    }

    void update(std::size_t node, std::size_t l, std::size_t r, std::size_t idx, const T& val) {
        if (l == r) {
            tree_[node] = val;
            return;
        }
        std::size_t mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, r, idx, val);
        }
        tree_[node] = op_(tree_[2 * node], tree_[2 * node + 1]);
    }

    [[nodiscard]] T query(std::size_t node, std::size_t l, std::size_t r, std::size_t ql, std::size_t qr) const {
        if (ql <= l && r <= qr) {
            return tree_[node];
        }
        std::size_t mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(2 * node, l, mid, ql, qr);
        }
        if (ql > mid) {
            return query(2 * node + 1, mid + 1, r, ql, qr);
        }
        return op_(query(2 * node, l, mid, ql, qr),
                   query(2 * node + 1, mid + 1, r, ql, qr));
    }
};

} // namespace algocore::ds
