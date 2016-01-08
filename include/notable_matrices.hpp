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
#include "make_vector.hpp"
#include "vector_products.hpp"

namespace nc
{
    // Genera la matrice di Hilbert.
    template <typename T0, std::size_t TDim>
    auto make_hilbert_matrix()
    {
        matrix<T0, TDim, TDim> result;

        result.for_idxs([&result](auto i, auto j)
            {
                result(i, j) = 1.f / ((i + 1.f) + (j + 1.f) - 1.f);
            });

        return result;
    }

    // Dettagli di implementazione per la matrice di Vandermonde.
    namespace impl
    {
        template <typename T0, std::size_t TRows, std::size_t TCols,
            typename TVAccess, typename TV0>
        auto make_vandermonde_matrix(TVAccess&& v_access, const TV0& v)
        {
            matrix<T0, TRows, TCols> result;

            // Assume TRows x TRows
            for(auto i(0); i < TRows; ++i)
                for(auto j(0); j < TRows; ++j)
                {
                    result(i, j) = std::pow(v_access(v, i), j);
                }

            return result;
        }
    }

    // Genera la matrice di Vandermonde.
    template <typename T0, std::size_t TDim, typename TV0>
    auto make_vandermonde_matrix(const TV0& v)
    {
        return impl::make_vandermonde_matrix<T0, TDim, TDim>(
            [](auto& v, auto i)
            {
                return access_row_vector(v, i);
            },
            v);
    }

    // Genera una matrice diagonale dominante.
    template <typename... Ts>
    auto make_diagonal_dominant_square_matrix(Ts&&... xs)
    {
        constexpr auto dim(sizeof...(xs));
        static_assert(dim > 0, "");

        using type = std::common_type_t<Ts...>;
        matrix<type, dim, dim> result{};

        std::size_t i(0);

        for_args(
            [&result, &i](auto x)
            {
                result(i, i) = x;
                ++i;
            },
            xs...);

        return result;
    }

    // Esegue la decomposizione LU di Crout.
    template <typename T0, std::size_t TDim>
    auto make_crout_decomposition(const matrix<T0, TDim, TDim>& a)
    {
        auto n = TDim;

        matrix<T0, TDim, TDim> l;
        matrix<T0, TDim, TDim> u{init_identity{}};

        // Itera sulle righe.
        for(std::size_t i(0); i < n; ++i)
        {
            // Itera sulle colonne, partendo da `i`.
            for(std::size_t j(i); j < n; ++j)
            {
                // Sommatoria.
                T0 sum(0);
                for(std::size_t k(0); k < i; ++k)
                {
                    sum += l(j, k) * u(k, i);
                }

                // Setta valore della matrice L.
                l(j, i) = a(j, i) - sum;
            }

            // Itera sulle colonne, partendo da `i`.
            for(std::size_t j(i); j < n; ++j)
            {
                // Sommatoria.
                T0 sum(0);
                for(std::size_t k(0); k < i; ++k)
                {
                    sum += l(i, k) * u(k, j);
                }

                // Setta valore della matrice U.
                assert(l(i, i) != 0);
                u(i, j) = (a(i, j) - sum) / l(i, i);
            }
        }

        // Restituisci una tupla (l, u).
        return std::make_tuple(std::move(l), std::move(u));
    }

    // Dettagli di implementazione matrice di Wilkinson.
    namespace impl
    {
        template <typename T0, std::size_t TDim, typename TF>
        auto make_wilkinson_matrix_impl(TF&& f)
        {
            // L'ordine deve essere dispari.
            static_assert(is_odd(TDim), "");

            matrix<T0, TDim, TDim> m;

            // Setta la diagonale.
            for(auto k(0); k < TDim; ++k)
            {
                m(k, k) = f(k);
            }

            // Setta valori adiacenti alla diagonale principale.
            for(auto k(0); k < TDim - 1; ++k)
            {
                m(k + 1, k) = 1;
                m(k, k + 1) = 1;
            }

            return m;
        }

        // Calcolo di default (con segno) della matrice di Wilkinson.
        template <std::size_t TDim>
        auto make_wilkinson_calc()
        {
            return [](auto k)
            {
                return std::floor((int)k - ((int)TDim / 2));
            };
        }
    }

    // Genera una matrice di Wilkinson con il segno.
    template <typename T0, std::size_t TDim>
    auto make_wilkinson_m_matrix()
    {
        auto calc = impl::make_wilkinson_calc<TDim>();
        return impl::make_wilkinson_matrix_impl<T0, TDim>(calc);
    }

    // Genera una matrice di Wilkinson con valore assoluto.
    template <typename T0, std::size_t TDim>
    auto make_wilkinson_p_matrix()
    {
        // Compone la funzione `abs` con `calc`.
        auto calc = impl::make_wilkinson_calc<TDim>();
        auto wrapped_calc = [&calc](auto k)
        {
            return std::abs(calc(k));
        };

        return impl::make_wilkinson_matrix_impl<T0, TDim>(wrapped_calc);
    }
}
