#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <cstddef>

namespace algocore::strings {

/**
 * @brief Computes Knuth-Morris-Pratt (KMP) Prefix Function (pi array).
 * pi[i] is the length of the longest proper prefix of pattern[0..i] that is also a suffix of pattern[0..i].
 */
[[nodiscard]] inline std::vector<std::size_t> compute_prefix_function(std::string_view pattern) {
    std::size_t m = pattern.size();
    std::vector<std::size_t> pi(m, 0);
    for (std::size_t i = 1; i < m; ++i) {
        std::size_t j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

/**
 * @brief Finds all 0-based start occurrences of pattern in text using KMP.
 * Runs in O(|text| + |pattern|) time.
 */
[[nodiscard]] inline std::vector<std::size_t> kmp_search(std::string_view text, std::string_view pattern) {
    if (pattern.empty() || text.size() < pattern.size()) {
        return {};
    }

    auto pi = compute_prefix_function(pattern);
    std::vector<std::size_t> matches;

    std::size_t j = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == pattern.size()) {
            matches.push_back(i + 1 - pattern.size());
            j = pi[j - 1];
        }
    }

    return matches;
}

} // namespace algocore::strings
