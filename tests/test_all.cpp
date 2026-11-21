#include <iostream>
#include <cassert>
#include <vector>
#include <string>

#include "algocore/data_structures/segment_tree.hpp"
#include "algocore/data_structures/fenwick_tree.hpp"
#include "algocore/data_structures/dsu.hpp"
#include "algocore/graphs/dijkstra.hpp"
#include "algocore/graphs/tarjan_scc.hpp"
#include "algocore/strings/kmp.hpp"
#include "algocore/strings/trie.hpp"
#include "algocore/math/modular.hpp"

void test_segment_tree() {
    std::cout << "[RUNNING] test_segment_tree...";
    std::vector<int> data = {1, 3, 5, 7, 9, 11};
    algocore::ds::SegmentTree<int> st(data, 0, std::plus<int>());

    assert(st.query(0, 2) == 9);   // 1 + 3 + 5 = 9
    assert(st.query(1, 4) == 24);  // 3 + 5 + 7 + 9 = 24
    assert(st.query(0, 5) == 36);  // total sum

    st.update(1, 10); // replace 3 with 10 -> {1, 10, 5, 7, 9, 11}
    assert(st.query(0, 2) == 16);  // 1 + 10 + 5 = 16
    assert(st.query(0, 5) == 43);

    // Range minimum test
    auto min_op = [](int a, int b) { return std::min(a, b); };
    algocore::ds::SegmentTree<int, decltype(min_op)> rmq(data, 1e9, min_op);
    assert(rmq.query(0, 5) == 1);
    assert(rmq.query(3, 5) == 7);
    std::cout << " PASSED" << std::endl;
}

void test_fenwick_tree() {
    std::cout << "[RUNNING] test_fenwick_tree...";
    std::vector<long long> arr = {2, 4, 6, 8, 10};
    algocore::ds::FenwickTree<long long> ft(arr);

    assert(ft.prefix_sum(2) == 12); // 2 + 4 + 6 = 12
    assert(ft.range_sum(1, 3) == 18); // 4 + 6 + 8 = 18
    assert(ft.range_sum(0, 4) == 30);

    ft.add(2, 5); // arr[2] becomes 11
    assert(ft.prefix_sum(2) == 17);
    assert(ft.range_sum(2, 2) == 11);
    std::cout << " PASSED" << std::endl;
}

void test_dsu() {
    std::cout << "[RUNNING] test_dsu...";
    algocore::ds::DisjointSetUnion dsu(6);
    assert(dsu.count_components() == 6);

    assert(dsu.unite(0, 1) == true);
    assert(dsu.unite(1, 2) == true);
    assert(dsu.connected(0, 2) == true);
    assert(dsu.connected(0, 3) == false);
    assert(dsu.component_size(0) == 3);
    assert(dsu.count_components() == 4);

    assert(dsu.unite(0, 2) == false); // already connected
    assert(dsu.count_components() == 4);
    std::cout << " PASSED" << std::endl;
}

void test_dijkstra() {
    std::cout << "[RUNNING] test_dijkstra...";
    std::size_t n = 5;
    std::vector<std::vector<algocore::graphs::Edge<long long>>> adj(n);

    // 0 -> 1 (w=4), 0 -> 2 (w=2)
    // 2 -> 1 (w=1), 1 -> 3 (w=5)
    // 2 -> 3 (w=8), 3 -> 4 (w=3)
    adj[0].push_back({1, 4});
    adj[0].push_back({2, 2});
    adj[2].push_back({1, 1});
    adj[1].push_back({3, 5});
    adj[2].push_back({3, 8});
    adj[3].push_back({4, 3});

    auto res = algocore::graphs::dijkstra(n, adj, 0);

    assert(res.dist[0] == 0);
    assert(res.dist[2] == 2);
    assert(res.dist[1] == 3); // 0 -> 2 -> 1 (cost 3)
    assert(res.dist[3] == 8); // 0 -> 2 -> 1 -> 3 (cost 8)
    assert(res.dist[4] == 11); // 0 -> 2 -> 1 -> 3 -> 4 (cost 11)

    auto path = res.reconstruct_path(4);
    std::vector<std::size_t> expected = {0, 2, 1, 3, 4};
    assert(path == expected);
    std::cout << " PASSED" << std::endl;
}

void test_tarjan_scc() {
    std::cout << "[RUNNING] test_tarjan_scc...";
    std::size_t n = 5;
    std::vector<std::vector<std::size_t>> adj(n);

    // SCC 1: 0 -> 1 -> 2 -> 0
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    // 1 -> 3 -> 4
    adj[1].push_back(3);
    adj[3].push_back(4);

    auto res = algocore::graphs::tarjan_scc(n, adj);
    assert(res.components.size() == 3); // {4}, {3}, {0, 1, 2}
    assert(res.component_id[0] == res.component_id[1]);
    assert(res.component_id[1] == res.component_id[2]);
    assert(res.component_id[3] != res.component_id[0]);
    assert(res.component_id[4] != res.component_id[3]);
    std::cout << " PASSED" << std::endl;
}

void test_kmp() {
    std::cout << "[RUNNING] test_kmp...";
    std::string text = "ababcabcabababd";
    std::string pat = "ababd";

    auto matches = algocore::strings::kmp_search(text, pat);
    assert(matches.size() == 1);
    assert(matches[0] == 10);

    std::string multi_text = "banana";
    auto a_matches = algocore::strings::kmp_search(multi_text, "an");
    assert(a_matches.size() == 2);
    assert(a_matches[0] == 1 && a_matches[1] == 3);
    std::cout << " PASSED" << std::endl;
}

void test_trie() {
    std::cout << "[RUNNING] test_trie...";
    algocore::strings::Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("banana");

    assert(trie.contains("app") == true);
    assert(trie.contains("apple") == true);
    assert(trie.contains("appl") == false);
    assert(trie.contains("orange") == false);

    assert(trie.count_with_prefix("app") == 3);
    assert(trie.count_with_prefix("ban") == 1);
    assert(trie.count_with_prefix("cat") == 0);
    std::cout << " PASSED" << std::endl;
}

void test_modular() {
    std::cout << "[RUNNING] test_modular...";
    using Mint = algocore::math::Mint1e9;

    Mint a = 1000000000;
    Mint b = 10;
    Mint c = a + b;
    assert(c.val() == 3); // (10^9 + 10) % (10^9 + 7) = 3

    Mint d = a * b; // modular multiplication
    assert(d.val() == (static_cast<__int128>(1000000000) * 10) % 1000000007);

    // Modular inverse: x * x^-1 = 1 (mod P)
    Mint x = 42;
    Mint x_inv = x.inv();
    assert((x * x_inv).val() == 1);

    // Division
    Mint p = 50, q = 5;
    assert((p / q).val() == 10);

    // Exponentiation: 2^10 = 1024
    Mint base = 2;
    assert(base.power(10).val() == 1024);
    std::cout << " PASSED" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     AlgoCore-CPP Test Suite Running    " << std::endl;
    std::cout << "========================================" << std::endl;

    test_segment_tree();
    test_fenwick_tree();
    test_dsu();
    test_dijkstra();
    test_tarjan_scc();
    test_kmp();
    test_trie();
    test_modular();

    std::cout << "========================================" << std::endl;
    std::cout << "  ALL 8 MODULE TESTS PASSED [100% OK]   " << std::endl;
    std::cout << "========================================" << std::endl;
    return 0;
}
