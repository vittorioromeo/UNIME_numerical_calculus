#include "nc_cpp.hpp"
#include "../../test/utils/nc_test_utils.hpp"

int main()
{
    // 2) Risolvere un sistema lineare Ax=b con il metodo di Gauss. Perturbare
    // almeno un elemento di A e risolvere nuovamente il sistema mantenendo lo
    // stesso vettore dei termini noti. Confrontare la soluzione ottenuta con
    // quella del sistema non perturbato e spiegare quello che accade,
    // evidenziando la relazione tra l’errore relativo sui dati e quello sulla
    // soluzione.
    {
        // Implementato.
        // `exercises/group_5/gauss_and_perturbation.cpp`
    }

    // 3) Per alcune matrici verificare la crescita del valore assoluto
    // dell’elemento unn nella fattorizzazione A=LU rispetto alla maggiorazione
    // data dal teorema di Wilkinson
    {
        // Implementato.
        // `exercises/group_5/wilkinson_check.cpp`
    }
}
