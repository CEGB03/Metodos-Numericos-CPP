set terminal wxt size 1200,700 title 'Comparación de Métodos Numéricos'
# Alternativa si wxt no funciona: set terminal qt

set title 'Comparación de Métodos Numéricos'
set xlabel 'x'
set ylabel 'y'
set grid
set style data linespoints
set key top right
set datafile separator ','

# Controles:
#   Rueda del ratón: Zoom
#   Click + Arrastrar: Pan (mover vista)
#   Click derecho + menú: Exportar a PNG
#   'q': Salir

plot './rk4_0.01.txt' using 1:2 title 'Rk4 (h=0.01)' with linespoints linewidth 2 pointsize 0.8, './rk4_0.10.txt' using 1:2 title 'Rk4 (h=0.1)' with linespoints linewidth 2 pointsize 0.8

# Para exportar a PNG después de hacer zoom/pan:
# set terminal png size 1200,700
# set output 'comparacion_export.png'
# replot
