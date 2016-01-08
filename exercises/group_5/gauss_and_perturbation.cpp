#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    auto ok(true);
    while(ok)
    {
        // Genera matrice 8x9 casuale.
        auto m = make_rnd_matrix_8x9();
        print_matrix(m);
        std::cout << "\n\n";

        // Calcoli pre-perturbazione.
        auto r_pre = m.solve_gauss();
        std::cout << "Soluzioni (pre-perturbazione):\n";
        print_matrix(r_pre);

        // Applico una perturbazione.
        m(7, 7) += 25;

        // Calcoli post-perturbazione.
        auto r_post = m.solve_gauss();
        std::cout << "Soluzioni (post-perturbazione):\n";
        print_matrix(r_post);

        // Calcolo errori.
        auto err_ass = (r_pre - r_post).norm_2();
        auto err_rel = err_ass / r_pre.norm_2();

        std::cout << "Errore assoluto: " << err_ass << "\n";
        std::cout << "Errore relativo: " << err_rel << "\n\n";

        std::cout << "Di nuovo?\n\n";
        std::cin >> ok;
    }
}