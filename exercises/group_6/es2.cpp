#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main(int ac, char** av)
{
    // Sistemi forniti dal testo.
    auto a0 =
        nc::make_matrix<float, 3, 4>(3, 0, 4, 7, 7, 4, 2, 13, -1, -1, -2, -4);
    auto a1 =
        nc::make_matrix<float, 3, 4>(-3, 3, -6, -6, -4, 7, -8, -5, 5, 7, -9, 3);
    auto a2 =
        nc::make_matrix<float, 3, 4>(4, 1, 1, 6, 2, -9, 0, -7, 0, -8, -6, 14);
    auto a3 =
        nc::make_matrix<float, 3, 4>(7, 6, 9, 22, 4, 5, -4, 5, -7, -3, 8, -2);
    auto a4 = nc::make_matrix<float, 4, 5>(
        -4, -1, 1, 1, -3, 0, -4, -1, 1, -4, -1, -1, 4, 1, 3, 1, -1, 0, 4, 4);

    // Vettori iniziali per la risoluzione di Gauss-Seidel.
    auto our_phi_3 = nc::make_column_vector<float>(0, 0, 0);
    auto our_phi_4 = nc::make_column_vector<float>(0, 0, 0, 0);

    // Calcolo errore assoluto.
    auto err_ass = [](const auto& pre, const auto& post)
    {
        return (pre - post).norm_2();
    };

    // Esecuzione test.
    auto execute = [&](auto& a, auto start_phi)
    {
        auto exact_solution = a.solve_gauss();

        auto err_ass_from_exact = [&](const auto& s)
        {
            return err_ass(exact_solution, s);
        };

        // Vettori per la conservazione degli errori.
        std::vector<float> jacobi_errors, gseidel_errors;

        // Parametri di default.
        std::size_t max_itr = 10000;
        double acc = 0.00001;

        a.solve_jacobi(max_itr, acc, [&](const auto& x)
            {
                jacobi_errors.emplace_back(err_ass_from_exact(x));
            });

        a.solve_gauss_seidel(start_phi, max_itr, acc, [&](const auto& x)
            {
                gseidel_errors.emplace_back(err_ass_from_exact(x));
            });

        auto min_sz = std::min(jacobi_errors.size(), gseidel_errors.size());
        for(std::size_t i(0); i < min_sz; ++i)
        {
            std::cout << i << " " << jacobi_errors[i] << " "
                      << gseidel_errors[i] << "\n";
        }
    };

    // Ottieni primo argomento da terminale.
    if(ac != 2) return 1;
    int val = std::stoi(av[1]);

    // Stampa dati per gnuplot.
    switch(val)
    {
        case 0: execute(a0, our_phi_3); break;
        case 1: execute(a1, our_phi_3); break;
        case 2: execute(a2, our_phi_3); break;
        case 3: execute(a3, our_phi_3); break;
        case 4: execute(a4, our_phi_4); break;
    }

    return 0;
}
