#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

constexpr auto poly2(float x) noexcept
{
    return -3 * std::pow(x, 5) + 4 * std::pow(x, 4) + -2 * std::pow(x, 3) +
           5 * std::pow(x, 2) + -2.5 * x;
}

constexpr auto poly(float x) noexcept
{
    return 2 * std::pow(x, 5) + 4 * std::pow(x, 3) + 6 * x;
}

constexpr auto node_val(float n, float i)
{
    return (2.0 / n) * i;
}

int main()
{
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
            std::cout << k << " "       // .
                      << poly(k) << " " // .
                      << i_m1(k) << " " // .
                      << i_m2(k) << " " // .
                      << i_m3(k) << " " // .
                      << i_m4(k) << " " // .
                      << i_m5(k) << " " // .
                      << i_m6(k) << " " // .
                      << i_l(k) << " "  // .
                      << i_n(k) << " "  // .
                      << "\n";
        };
    };

    auto x_vec = nc::make_column_vector<float>( // .
        node_val(6, 0),                         // .
        node_val(6, 1),                         // .
        node_val(6, 2),                         // .
        node_val(6, 3),                         // .
        node_val(6, 4),                         // .
        node_val(6, 5)                          // .
        );


    auto fx_vec = nc::make_column_vector<float>( // .
        poly(node_val(6, 0)),                    // .
        poly(node_val(6, 1)),                    // .
        poly(node_val(6, 2)),                    // .
        poly(node_val(6, 3)),                    // .
        poly(node_val(6, 4)),                    // .
        poly(node_val(6, 5))                     // .
        );

    print_matrix(x_vec);
    print_matrix(fx_vec);

    auto executor = exec(x_vec, fx_vec);

    for(float j = -1; j < 1; j += 0.01)
    {
        executor(j);
    }
}