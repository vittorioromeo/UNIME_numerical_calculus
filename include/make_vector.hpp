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
#include "vectors.hpp"

namespace nc
{
    // Crea un vettore riga (matrice 1xN).
    template <typename T0, typename... Ts>
    auto make_row_vector(Ts&&... xs)
    {
        return make_matrix<T0, 1, sizeof...(Ts)>(xs...);
    }

    // Crea un vettore colonna (matrice Nx1).
    template <typename T0, typename... Ts>
    auto make_column_vector(Ts&&... xs)
    {
        return make_matrix<T0, sizeof...(Ts), 1>(xs...);
    }
}
