#pragma once

#include <vector>
#include <string_view>
#include <array>
#include <cstddef>

namespace algocore::strings {

/**
 * @brief High-efficiency array-backed Prefix Trie for lowercase English letters ('a'-'z').
 */
class Trie {
public:
    static constexpr std::size_t ALPHABET_SIZE = 26;

    Trie() {
        nodes_.emplace_back(); // Root node at index 0
    }

    /**
     * @brief Inserts a word into the trie.
     */
    void insert(std::string_view word) {
        std::size_t curr = 0;
        ++nodes_[curr].prefix_count;
        for (char c : word) {
            std::size_t idx = static_cast<std::size_t>(c - 'a');
            if (nodes_[curr].next[idx] == 0) {
                nodes_[curr].next[idx] = nodes_.size();
                nodes_.emplace_back();
            }
            curr = nodes_[curr].next[idx];
            ++nodes_[curr].prefix_count;
        }
        ++nodes_[curr].end_count;
    }

    /**
     * @brief Checks if a full word exists in the trie.
     */
    [[nodiscard]] bool contains(std::string_view word) const {
        std::size_t curr = 0;
        for (char c : word) {
            std::size_t idx = static_cast<std::size_t>(c - 'a');
            if (nodes_[curr].next[idx] == 0) return false;
            curr = nodes_[curr].next[idx];
        }
        return nodes_[curr].end_count > 0;
    }

    /**
     * @brief Returns the number of stored words that have the given prefix.
     */
    [[nodiscard]] std::size_t count_with_prefix(std::string_view prefix) const {
        std::size_t curr = 0;
        for (char c : prefix) {
            std::size_t idx = static_cast<std::size_t>(c - 'a');
            if (nodes_[curr].next[idx] == 0) return 0;
            curr = nodes_[curr].next[idx];
        }
        return nodes_[curr].prefix_count;
    }

    [[nodiscard]] std::size_t node_count() const noexcept {
        return nodes_.size();
    }

private:
    struct Node {
        std::array<std::size_t, ALPHABET_SIZE> next{};
        std::size_t end_count{0};
        std::size_t prefix_count{0};
    };

    std::vector<Node> nodes_;
};

} // namespace algocore::strings
