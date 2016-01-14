#include "nc_cpp.hpp"

int main()
{
    // 1. Dati due numeri interi dire se il primo e' multiplo del secondo. Caso
    // particolare dato un numero intero dire se e' pari o dispari.
    {
        // Implementato.
        (void)nc::is_multiple_of(3, 9);
    }

    // 2. Scrivere un programma per la risoluzione delle equazioni di secondo
    // grado. Trasformare il programma in subroutine.
    {
        // Implementato.
        (void)nc::solve_grade2_equation(4, 5, 1);
    }

    // 3. Scrivere i programmi per la sommatoria e la produttoria di n numeri
    // reali.
    {
        // Implementato.
        (void)nc::sum_n_numbers(std::vector<int>{1, 2, 3, 4});
        (void)nc::multiply_n_numbers(std::vector<int>{1, 2, 3, 4});
    }

    // 4. Scrivere un programma che calcola la media di n numeri interi (o
    // reali). Trasformare il programma in una funzione.
    {
        // Implementato.
        (void)nc::average_n_numbers(std::vector<int>{1, 2, 3, 4});
    }

    // 5. Trovare il massimo (o minimo) di un insieme di numeri. Trasformare il
    // programma in una funzione.
    {
        // Implementato.
        (void)nc::max_n_numbers(std::vector<int>{1, 2, 3, 4});
        (void)nc::min_n_numbers(std::vector<int>{1, 2, 3, 4});
    }

    // 6. Studiare il massimo valore del fattoriale di n calcolabile da un
    // elaboratore nel caso di variabili di tipo intero, reale e reale in doppia
    // precisione.
    {
        // Implementato.
        (void)nc::max_representable_factorial<int>();
        (void)nc::max_representable_factorial_real<float>();
        (void)nc::max_representable_factorial_real<double>();
    }

    // 7. Analizzare quanto vale la precisione di macchina in singola e doppia
    // precisione.
    {
        // Implementato.
        (void)nc::find_epsilon<float>();
        (void)nc::find_epsilon<double>();
    }

    // 8. Ordinamento di un insieme di numeri (oppure nomi), stampare l'insieme
    // ordinato.
    {
        // Implementato.
        std::vector<int> v{1, 2, 3, 4};
        (void)nc::sort_vector(v);
    }

    // 9. Ricerca, inserimento e cancellazione di un elemento in un insieme
    // ordinato.
    {
        // Implementato.
        std::vector<int> v{1, 2, 3, 4};
        (void)nc::insert_in_sorted_vector(5, v);
        (void)nc::remove_from_sorted_vector(nc::find_in_sorted_vector(3, v), v);
    }

    // 10. Date due matrici di ordine n calcolare la matrice somma
    {
        // Implementato.
        auto m0 = nc::make_matrix<float, 2, 2>(1, 2, 3, 4);
        auto m1 = nc::make_matrix<float, 2, 2>(1, 2, 3, 4);
        auto sum = m0 + m1;
        (void)sum;
    }

    // 11. Date due matrici di ordine n calcolare la matrice prodotto.
    {
        // Implementato.
        auto m0 = nc::make_matrix<float, 2, 2>(1, 2, 3, 4);
        auto m1 = nc::make_matrix<float, 2, 2>(1, 2, 3, 4);
        auto prod = m0 * m1;
        (void)prod;
    }

    // 12. Trasformare i programmi degli esercizi 9 e 10 della prima parte in
    // subroutine.
    {
        // Implementato.
    }

    // 13. Dati due vettori x e y con n componenti calcolare il prodotto
    // scalare.
    {
        // Implementato.
        auto v0 = nc::make_column_vector<float>(1, 3, 5, 6);
        auto v1 = nc::make_column_vector<float>(1, 3, 5, 6);
        auto prod_scal = nc::vector_scalar_product(v0, v1);
        (void)prod_scal;
    }

    // 14. Dati due vettori x e y con n componenti calcolare il prodotto
    // tensoriale.
    {
        // Implementato.
        auto v0 = nc::make_column_vector<float>(1, 3, 5, 6);
        auto v1 = nc::make_column_vector<float>(1, 3, 5, 6);
        auto prod_tens = nc::vector_tensor_product(v0, v1);
        (void)prod_tens;
    }

    // Matrici notevoli realizzate:
    {
        // Matrice di Hilbert
        {
            (void)nc::make_hilbert_matrix<float, 3>();
        }

        // Matrice di Wilkinson
        {
            // Con segno sia positivo che negativo:
            (void)nc::make_wilkinson_m_matrix<float, 3>();

            // A valori assoluti:
            (void)nc::make_wilkinson_p_matrix<float, 3>();
        }

        // Matrice diagonale dominante
        {
            (void)nc::make_diagonal_dominant_square_matrix(1, 2, 3, 4, 5);
        }

        // Matrice di Vandermonde
        {
            (void)nc::make_vandermonde_matrix<float, 4>(
                nc::make_row_vector<float>(1, 2, 3, 4));
        }
    }
}