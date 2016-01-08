#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    nc::for_args(
        [](auto x)
        {
            constexpr auto order = decltype(x){};
            auto m = nc::make_hilbert_matrix<float, order>();

            print_norm_values(m);
        },
        int_v<1>{}, int_v<2>{}, int_v<3>{}, int_v<4>{}, int_v<5>{}, int_v<6>{},
        int_v<7>{}, int_v<8>{}, int_v<9>{}, int_v<10>{}, int_v<11>{});
}