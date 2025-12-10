set terminal wxt size 1200,700 title 'Comparación de Métodos Numéricos' persist
set title 'Comparación de Métodos Numéricos'
set xlabel 'x'
set ylabel 'y'
set grid
set style data linespoints
set key top right
set datafile separator ','

plot './rk4_0.01.txt' using 1:2 title 'Rk4 (h=0.01)' with linespoints linewidth 2 pointsize 0.8, './rk4_0.10.txt' using 1:2 title 'Rk4 (h=0.1)' with linespoints linewidth 2 pointsize 0.8

# La ventana permanecerá abierta hasta cerrarla manualmente
