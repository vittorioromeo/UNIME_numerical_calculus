#pragma once

#include <cstddef>
#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <limits>
#include <vrm/core/static_if.hpp>

#include "utilities.hpp"
#include "multiples.hpp"
#include "equations.hpp"
#include "folds.hpp"
#include "representations.hpp"
#include "sorted_vector.hpp"
#include "matrix.hpp"
#include "make_matrix.hpp"

namespace nc
{
    // I nostri vettori sono implementati come matrici.
    // Definiamo qui due alias per i tipi di matrici che rappresentano i
    // vettori, uno per colonna, uno per riga.

    // Alias per vettore riga (1 riga, N colonne).
    // `T0` è il tipo di dato.
    template <typename T0, std::size_t TComponentCount>
    using row_vector = matrix<T0, 1, TComponentCount>;

    // Alias per vettore colonna (N righe, 1 colonna).
    template <typename T0, std::size_t TComponentCount>
    using column_vector = matrix<T0, TComponentCount, 1>;

    // Per evitare errori durante l'accesso ai dati dei vettori, definiamo due
    // funzioni che permettono di ottenere la n-esima componente.

    // Accedi alla j-esima componente di un vettore riga.
    template <typename T>
    decltype(auto) access_row_vector(T&& v, std::size_t j) noexcept
    {
        return v(0, j);
    }

    // Accedi alla i-esima componente di un vettore colonna.
    template <typename T>
    decltype(auto) access_column_vector(T&& v, std::size_t i) noexcept
    {
        return v(i, 0);
    }

    // Restituisce la dimensione di un vettore.
    template <typename T>
    constexpr auto vector_dimension(const T& v)
    {
        constexpr auto rc = v.row_count();
        constexpr auto cc = v.column_count();

        static_assert(rc == 1 || cc == 1, "");
        return rc < cc ? cc : rc;
    }
}
