#pragma once

#include <iostream>
#include <concepts>
#include <cstdint>

namespace algocore::math {

/**
 * @brief High-performance modular arithmetic wrapper supporting fast multiplication,
 * addition, subtraction, division, and modular inverse via extended Euclidean algorithm.
 * @tparam Mod Prime or coprime modulus.
 */
template <std::int64_t Mod>
class Modular {
    static_assert(Mod > 0, "Modulus must be strictly positive");

public:
    constexpr Modular() noexcept : val_(0) {}
    constexpr Modular(std::int64_t v) noexcept : val_(normalize(v)) {}

    [[nodiscard]] constexpr std::int64_t val() const noexcept { return val_; }
    static constexpr std::int64_t mod() noexcept { return Mod; }

    constexpr Modular& operator+=(const Modular& other) noexcept {
        val_ += other.val_;
        if (val_ >= Mod) val_ -= Mod;
        return *this;
    }

    constexpr Modular& operator-=(const Modular& other) noexcept {
        val_ -= other.val_;
        if (val_ < 0) val_ += Mod;
        return *this;
    }

    constexpr Modular& operator*=(const Modular& other) noexcept {
        val_ = static_cast<std::int64_t>((static_cast<__int128>(val_) * other.val_) % Mod);
        return *this;
    }

    [[nodiscard]] constexpr Modular power(std::int64_t exp) const noexcept {
        Modular base = *this;
        Modular res = 1;
        while (exp > 0) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }

    [[nodiscard]] constexpr Modular inv() const {
        std::int64_t a = val_, b = Mod;
        std::int64_t u = 1, v = 0;
        while (b) {
            std::int64_t t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        if (a != 1) {
            // No modular inverse if not coprime
            return Modular(0);
        }
        return Modular(u);
    }

    constexpr Modular& operator/=(const Modular& other) {
        return *this *= other.inv();
    }

    friend constexpr Modular operator+(Modular lhs, const Modular& rhs) noexcept { return lhs += rhs; }
    friend constexpr Modular operator-(Modular lhs, const Modular& rhs) noexcept { return lhs -= rhs; }
    friend constexpr Modular operator*(Modular lhs, const Modular& rhs) noexcept { return lhs *= rhs; }
    friend constexpr Modular operator/(Modular lhs, const Modular& rhs) { return lhs /= rhs; }

    friend constexpr bool operator==(const Modular& lhs, const Modular& rhs) noexcept { return lhs.val_ == rhs.val_; }
    friend constexpr bool operator!=(const Modular& lhs, const Modular& rhs) noexcept { return lhs.val_ != rhs.val_; }

    friend std::ostream& operator<<(std::ostream& os, const Modular& m) {
        return os << m.val_;
    }

private:
    std::int64_t val_;

    [[nodiscard]] static constexpr std::int64_t normalize(std::int64_t v) noexcept {
        v %= Mod;
        if (v < 0) v += Mod;
        return v;
    }
};

using Mint1e9 = Modular<1000000007>;
using Mint998 = Modular<998244353>;

} // namespace algocore::math
