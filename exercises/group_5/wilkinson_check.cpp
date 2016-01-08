#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    for(int i = 0; i < 5; ++i)
    {
        // Genera matrice casuale di ordine 8.
        auto order = 8;
        auto m = make_rnd_matrix_8();

        // Scomponi in LU e prendi U.
        auto lu = nc::make_crout_decomposition(m);
        const auto& u(std::get<1>(lu));

        // Elemento u_nn.
        auto u_nn(std::abs(u(order - 1, order- 1)));

        // Maggiorazione data dal teorema di Wilkinson.
        float max_m = 0;
        m.for_idxs([&](auto xi, auto xj)
            {
                max_m = std::max(max_m, std::abs(m(xi, xj)));
            });


        // Verifica disuguaglianza.
        auto coeff = std::pow(2.f, order - 1);
        auto rhs = coeff * max_m;
        assert(u_nn <= rhs);
    }
}