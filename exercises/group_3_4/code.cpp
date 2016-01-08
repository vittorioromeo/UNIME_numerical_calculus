#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    // 1) Confrontare su alcune matrici, con ordine n > 7, il valore delle
    // quattro norme matriciali studiate. Usare la routine della libreria IMSL
    // per il calcolo del raggio spettrale.
    {
        // Implementato.
        for(auto i = 0; i < 10; ++i)
        {
            confront_norms(
                "Matrice casuale " + std::to_string(i), make_rnd_matrix_8());
        }
    }

    // 2) Fare il grafico dell'andamento delle norme matriciali di alcune
    // famiglie di matrici confrontabili, perché generate dalla stessa regola di
    // costruzione, al crescere dell'ordine n. Analizzare e commentare i
    // risultati.
    {
        // Implementato.
        // `exercises/group_3/norm_comparison.sh
    }

    // 3) Verificare le seguenti principali relazioni tra le varie norme
    // matriciali studiate:
    {
        // Implementato.
        // `test/nc/group_2/es1.cpp`
    }

    // (gruppo 4)
    // Studiare, analizzando i risultati, l’indice di condizionamento di alcune
    // classi di matrici rispetto ad una delle norme studiate. Fare il grafico
    // dell’andamento dell’indice di condizionamento al crescere dell’ordine n
    // da 2 a 10 per alcune tra le famiglie di matrici confrontabili, perché
    // generate dalla stessa regola di costruzione.
    {
        // Implementato.
        // `exercises/group_3/norm_comparison.sh
    }
}