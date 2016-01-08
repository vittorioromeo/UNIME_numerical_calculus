#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    nc::for_args(
        [](auto x)
        {
            using precision = float;

            constexpr auto component_count(decltype(x){});
            nc::column_vector<precision, component_count> v;

            constexpr precision interval_left(-1);
            constexpr precision interval_right(1);

            constexpr precision interval_range(
                -(interval_left - interval_right));

            constexpr auto max_step(interval_range / (component_count - 1));

            for(auto j(0); j < component_count; ++j)
            {
                nc::access_column_vector(v, j) = interval_left + max_step * j;
            }

            std::cout << component_count << " " << v.norm_1() << " "
                      << v.norm_2() << " " << v.norm_inf() << "\n";
        },
        int_v<2>{}, int_v<3>{}, int_v<4>{}, int_v<5>{}, int_v<6>{}, int_v<7>{},
        int_v<8>{}, int_v<9>{}, int_v<10>{}, int_v<11>{}, int_v<12>{},
        int_v<13>{}, int_v<14>{}, int_v<15>{});

    return 0;
}
