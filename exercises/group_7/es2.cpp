#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    constexpr auto node_count = 6;
    constexpr auto min_node = -1.f;
    constexpr auto max_node = 1.f;
    constexpr auto node_range = max_node - min_node;
    constexpr auto node_ep = node_range / node_count;

    auto node_vec = nc::make_column_vector<float>( // .
        min_node + (node_ep * 0),                  // .
        min_node + (node_ep * 1),                  // .
        min_node + (node_ep * 2),                  // .
        min_node + (node_ep * 3),                  // .
        min_node + (node_ep * 4),                  // .
        min_node + (node_ep * 5),                  // .
        min_node + (node_ep * 6)                   // .
        );

    for(float j = -1; j <= 1.1; j += 0.1)
    {
        std::cout << j << " ";

        for(int k = 0; k < node_count; ++k)
        {
            auto basis = nc::newton_basis(node_vec, k);
            auto val = basis(j);

            std::cout << val << " ";
        }

        std::cout << "\n";
    }
}
