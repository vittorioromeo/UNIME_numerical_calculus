#pragma once

#include "./test_utils.hpp"
#include <nc_cpp.hpp>
#include <random>

template <int TV>
using int_v = std::integral_constant<int, TV>;

auto print_matrix = [](const auto& x)
{
    std::cout << "matrix(\n[\n";
    for(std::size_t i(0); i < x.row_count(); ++i)
    {
        std::cout << "[";

        for(std::size_t j(0); j < x.column_count(); ++j)
        {
            std::cout << x(i, j) << ", ";
        }

        std::cout << "],\n";
    }
    std::cout << "\n]\n)";
};

inline auto& gen()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    return gen;
}

auto rnd_float = [](auto min, auto max)
{
    return std::uniform_real_distribution<float>{min, max}(gen());
};

auto make_rnd_matrix_8x9 = []
{
    constexpr auto order(8);
    nc::matrix<float, order, order + 1> m;
    m.for_idxs([&](auto xi, auto xj)
        {
            m(xi, xj) = rnd_float(-100.f, 100.f);
        });

    return m;
};

auto make_rnd_matrix_8 = []
{
    constexpr auto order(8);
    nc::matrix<float, order, order> m;
    m.for_idxs([&](auto xi, auto xj)
        {
            m(xi, xj) = rnd_float(-100.f, 100.f);
        });

    return m;
};

auto make_rnd_matrix_3 = []
{
    constexpr auto order(3);
    nc::matrix<float, order, order> m;
    m.for_idxs([&](auto xi, auto xj)
        {
            m(xi, xj) = rnd_float(-100.f, 100.f);
        });

    return m;
};


auto confront_norms = [](const auto& title, const auto& m)
{
    std::cout << title << "\n";
    print_matrix(m);
    std::cout << "\n";
    std::cout.flush();

    auto norm1 = m.norm_1();
    auto norm2 = m.norm_2();
    auto norminf = m.norm_inf();
    auto normfrob = m.norm_frobenius();
    auto pindex = m.perturbation_index();

    std::cout << "Norm 1 of " << title << ": " << norm1 << "\n";
    std::cout << "Norm 2 of " << title << ": " << norm2 << "\n";
    std::cout << "Norm inf of " << title << ": " << norminf << "\n";
    std::cout << "Norm (Frobenius) of " << title << ": " << normfrob << "\n";
    std::cout << "Perturbation index of " << title << ": " << pindex
              << "\n\n\n";
};

auto print_norm_values = [](const auto& v)
{
    std::cout << v.order() << " " << v.norm_1() << " " << v.norm_2() << " "
              << v.norm_inf() << " " << v.norm_frobenius() << " " << v.perturbation_index() << "\n";
};
