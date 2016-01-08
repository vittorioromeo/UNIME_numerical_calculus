#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    // Base:
    auto f_base = [](auto)
    {
        return 1.0;
    };

    // Polinomio di grado 5 da interpolare:
    auto f_poly = [](auto x)
    {
        return -3 * std::pow(5, x) + 4 * std::pow(4, x) + -2 * std::pow(3, x) +
               5 * std::pow(2, x) + -2.5 * std::pow(1, x);
    };


    auto exec = [](auto x, auto fx)
    {
        auto i_m1 = nc::monomial_interpolator<1>(x, fx);
        auto i_m2 = nc::monomial_interpolator<2>(x, fx);
        auto i_m3 = nc::monomial_interpolator<3>(x, fx);
        auto i_m4 = nc::monomial_interpolator<4>(x, fx);
        auto i_m5 = nc::monomial_interpolator<5>(x, fx);
        auto i_m6 = nc::monomial_interpolator<6>(x, fx);
        auto i_l = nc::lagrange_interpolator(x, fx);
        auto i_n = nc::newton_interpolator(x, fx);

        return [=](auto k)
        {
            std::cout << i_m1(k) << " " // .
                      << i_m2(k) << " " // .
                      << i_m3(k) << " " // .
                      << i_m4(k) << " " // .
                      << i_m5(k) << " " // .
                      << i_m6(k) << " " // .
                      << i_k(k) << " "  // .
                      << i_n(k) << " "  // .
                      << "\n";
        };
    };

    auto langrange_basis = [](auto x, auto i)
    {
        constexpr auto n = nc::vector_dimension(x);

        return [n, x, i](auto value)
        {
            double acc = 1;
            for(auto m(0); m < n; ++m)
            {
                if(m == i) continue;

                acc *= (value - nc::access_column_vector(x, m)) /
                       (nc::access_column_vector(x, i) -
                           nc::access_column_vector(x, m));
            }

            return acc;
        };
    };

    auto nodes = nc::make_column_vector<float>(
        -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1);

    // int k = 5;
    for(float i = 0; i < 1; i += (1.f / 9))
    {
        std::cout << i << " ";

        for(int k = 1; k < 7; ++k)
        {
            auto b0 = langrange_basis(nodes, k);
            std::cout << b0(i) << " ";
        }


        std::cout << "\n";
    }
    // auto i_l = nc::lagrange_interpolator(x, fx);
}
