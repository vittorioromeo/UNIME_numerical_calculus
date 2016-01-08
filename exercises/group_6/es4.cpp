#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    // Sistema fornito dal testo.
    auto m = nc::make_matrix<float, 2, 3>( // .
        0.96326, 0.81321, 0.88824,         // .
        0.81321, 0.68654, 0.74988          // .
        );

    // Vettore di soluzioni iniziale.
    auto our_phi = nc::make_column_vector<float>(0.33116, 0.7);

    auto res = m.solve_gauss_seidel(our_phi);
    std::cout << "Soluzioni:\n";
    print_matrix(res);
    std::cout << "\n\n";

    std::cout << "Indice di perturbazione:\n" << m.perturbation_index()
              << "\n\n";
}
