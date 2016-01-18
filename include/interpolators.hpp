// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

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
#include "notable_matrices.hpp"

namespace nc
{
    // Calcola la base monomiale.
    template <typename T0, typename T1>
    auto monomial_basis(const T0& x, const T1& n) noexcept
    {
        return std::pow(x, n);
    }

    // Calcola la base di Lagrange.
    template <typename TNodeVector, typename T>
    auto lagrange_basis(const TNodeVector& nodes, const T& k) noexcept
    {
        constexpr auto n = vector_dimension(nodes);

        return [n, nodes, k](auto x)
        {
            double res(1);
            const auto& x_k(access_column_vector(nodes, k));

            loop_skipping(0, n, k, [&res, &nodes, &x, &x_k, k](auto i)
                {
                    const auto& x_i(access_column_vector(nodes, i));
                    res *= (x - x_i) / (x_k - x_i);
                });

            return res;
        };
    }

    // Calcola la base di Newton.
    template <typename TNodeVector, typename T>
    auto newton_basis(const TNodeVector& nodes, const T& j) noexcept
    {
        return [nodes, j](auto x)
        {
            double res(1);
            for(int i = 0; i < j; ++i)
            {
                const auto& x_i(access_column_vector(nodes, i));
                res *= x - x_i;
            }

            return res;
        };
    }

    // Genera un interpolatore monomiale.
    template <std::size_t TN, typename TXV, typename TFXV>
    auto monomial_interpolator(const TXV& x, const TFXV& fx)
    {
        // Verifica validità dei campioni.
        static_assert(vector_dimension(x) == vector_dimension(fx), "");
        static_assert(vector_dimension(x) > 0, "");

        // Crea matrice di Vandermonde con grado `TN`.
        // La matrice rappresenta un sistema lineare.
        // I coefficenti della matrice sono ottenuti dal vettore `x`.
        auto vmm = impl::make_vandermonde_matrix<float, TN, TN + 1>(
            [](const auto& v, auto i)
            {
                return access_column_vector(v, i);
            },
            x);

        // Setta i termini noti del sistema lineare di Vandermonde.
        for(auto k(0); k < TN; ++k)
        {
            vmm(k, TN) = access_column_vector(fx, k);
        }

        // Risolvi il sistema con il metodo Gauss.
        // Troviamo così i coefficenti del polinomio interpolatore.

        auto solved_vmm = vmm.solve_gauss();

        // TODO:
        /*
        for(auto k(0); k < TN; ++k)
        {
            std::cout << access_column_vector(solved_vmm, k) << "\n";
        }
        */

        // Restiusce la funzione interpolatrice.
        return [=](auto value)
        {
            // Accumulatore del risultato.
            float acc = 0;

            for(auto k(0); k < TN; ++k)
            {
                // `k`-esimo coefficiente.
                auto coeff = solved_vmm(k, 0);

                // Base monomiale.
                auto basis = monomial_basis(value, k);

                // Calcola il monomio di grado `k`.
                acc += coeff * basis;
            }

            return acc;
        };
    }


    // Genera un interpolatore di Lagrange.
    template <typename TVector>
    auto lagrange_interpolator(const TVector& x, const TVector& fx)
    {
        // Verifica validità dei campioni.
        static_assert(vector_dimension(x) == vector_dimension(fx), "");
        static_assert(vector_dimension(x) > 0, "");

        // Restituisce la funzione interpolante.
        return [x, fx](float value)
        {
            // Numero dei campioni.
            constexpr auto x_size = vector_dimension(x);

            // Accumulatore del risultato.
            float result = 0;

            // Esecuzione formula.
            for(int k = 0; k < x_size; k++)
            {
                auto basis = lagrange_basis(x, k);
                result += basis(value) * access_column_vector(fx, k);
            }

            return result;
        };
    }

    template <typename TVector>
    auto newton_interpolator(TVector x, TVector fx)
    {
        // Verifica validità dei campioni.
        static_assert(vector_dimension(x) == vector_dimension(fx), "");
        static_assert(vector_dimension(x) > 0, "");

        // Numero di campioni.
        constexpr auto n = vector_dimension(x);

        // Tabella delle differenze divise.
        matrix<double, n, n + 1> table;

        // Generazione della tabella: prime due colonne.
        for(int i = 0; i < n; ++i)
        {
            // Colonna 0: valori di `x`.
            table(i, 0) = access_column_vector(x, i);

            // Colonna 1: valori di `fx`.
            table(i, 1) = access_column_vector(fx, i);
        }

        // Generazione della tabella: resto delle colonne.
        // Esegue l'algoritmo delle differenze divise.
        for(int c = 2; c < n + 1; ++c)
        {
            // Riga corrente.
            int curr = 0;

            for(int r = c - 1; r < n; ++r)
            {
                // Indici precedenti riga/colonna.
                auto prev_r = r - 1;
                auto prev_c = c - 1;

                // Valori precedenti numeratore.
                auto prev0 = table(r, prev_c);
                auto prev1 = table(prev_r, prev_c);

                // Differenza dei valori precedenti.
                // (Numeratore.)
                auto num = prev0 - prev1;

                // Valori precedenti denominatore.
                auto den_v0 = table(r, 0);
                auto den_v1 = table(curr, 0);

                // Differenza dei valori precedenti.
                // (Denominatore.)
                auto den = den_v0 - den_v1;

                // Divisione delle differenze.
                auto frac = num / den;

                // TODO:
                // std::cout << r << ", " << c << " -> " << frac << "\n";

                table(r, c) = frac;
                ++curr;
            }
        }

        // TODO:
        /*
        for(int ix = 0; ix < n; ++ix)
        {
            for(int iy = 0; iy < n + 1; ++iy)
            {
                std::cout << table(ix, iy) << "\t";
            }

            std::cout << "\n";
        }
        */

        // Restituisce la funzione interpolatrice.
        return [n, table, x](auto value)
        {
            // Restituisce l'`u`-esimo coefficiente.
            auto uesimo = [=](auto u)
            {
                // TODO:
                /*
                    std::cout << "uesimo(" << u << ") = " << table(u, u + 1)
                              << "\n";
                */

                return table(u, u + 1);
            };

            // Accumulatore del risultato.
            double acc = 0;

            // Itera sul grado.
            for(int i = 0; i < n; ++i)
            {
                // Accumulatore dei fattori interni.
                double pacc = 1;
                for(int j = 0; j < i; ++j)
                {
                    pacc *= value - access_column_vector(x, j);
                }

                acc += uesimo(i) * pacc;

                // Esempio:
                // `(x-x0)(x-x1) * f[x0,x1,x2]`
                // Il `pacc` equivale a: `(x-x0)(x-x1)`.
                // L'`uesimo` equivale a: `f[x0,x1,x2]`.
            }

            return acc;
        };
    }
}
