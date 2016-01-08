#!/bin/bash

# Funzione 1
gnuplot -p -e "plot [-1 : 1] 1/(1+25*(x**2))"

# Funzione 4.1
gnuplot -p -e "plot [-3 : 4][-2 : 2] abs(x)"

# Funzione 4.2
gnuplot -p -e "plot [-2 : 2] abs(x)"

# Funzione 6
gnuplot -p -e "plot [0.1 : 1.5] tan(x)/x"