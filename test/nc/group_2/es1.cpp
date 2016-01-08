#include "../../utils/nc_test_utils.hpp"

int main()
{
    constexpr auto order = 8;
    
    auto verify_relationship_0 = [](const auto& m)
    {
        double coeff0(1.0 / std::sqrt((double)order));
        double x0(coeff0 * m.norm_inf());

        double x1(m.norm_2());

        double coeff2(std::sqrt((double)order));
        double x2(coeff2 * m.norm_inf());

        TEST_ASSERT_OP(x0, <=, x1);
        TEST_ASSERT_OP(x1, <=, x2);
    };

    auto verify_relationship_1 = [](const auto& m)
    {
        double coeff0(1.0 / std::sqrt((double)order));
        double x0(coeff0 * m.norm_1());

        double x1(m.norm_2());

        double coeff2(std::sqrt((double)order));
        double x2(coeff2 * m.norm_1());

        TEST_ASSERT_OP(x0, <=, x1);
        TEST_ASSERT_OP(x1, <=, x2);
    };

    auto verify_relationship_2 = [](const auto& m)
    {
        auto curr_max = m(0, 0);
        m.for_idxs([&curr_max, &m](auto xi, auto xj)
            {
                curr_max = std::max(curr_max, m(xi, xj));
            });

        double x0(curr_max);

        double x1(m.norm_2());

        double coeff2((double)order);
        double x2(coeff2 * curr_max);

        TEST_ASSERT_OP(x0, <=, x1);
        TEST_ASSERT_OP(x1, <=, x2);
    };

    auto verify_relationship_3 = [](const auto& m)
    {
        double x0(m.norm_2());
        double x1(std::sqrt(m.norm_1() * m.norm_inf()));

        TEST_ASSERT_OP(x0, <=, x1);
    };

    for(auto i = 0; i < 10; ++i)
    {
        auto x = make_rnd_matrix_8();
        verify_relationship_0(x);
        verify_relationship_1(x);
        verify_relationship_2(x);
        verify_relationship_3(x);
    }
}