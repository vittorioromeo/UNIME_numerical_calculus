#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

constexpr auto poly(float x) noexcept
{
    return -3 * std::pow(5, x) + 4 * std::pow(4, x) + -2 * std::pow(3, x) +
           5 * std::pow(2, x) + -2.5 * std::pow(1, x);
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
        -5,                                     // .
        -4,                                     // .
        -3,                                     // .
        -2,                                     // .
        -1,                                     // .
        0,                                      // .
        1,                                      // .
        2,                                      // .
        3,                                      // .
        4,                                      // .
        5                                       // .
        );


    auto fx_vec = nc::make_column_vector<float>( // .
        poly(-5),                                // .
        poly(-4),                                // .
        poly(-3),                                // .
        poly(-2),                                // .
        poly(-1),                                // .
        poly(0),                                 // .
        poly(1),                                 // .
        poly(2),                                 // .
        poly(3),                                 // .
        poly(4),                                 // .
        poly(5)                                  // .
        );

    print_matrix(x_vec);
    print_matrix(fx_vec);

    auto executor = exec(x_vec, fx_vec);

    for(float j = -10; j < 10; j += 0.25)
    {
        executor(j);
    }
}