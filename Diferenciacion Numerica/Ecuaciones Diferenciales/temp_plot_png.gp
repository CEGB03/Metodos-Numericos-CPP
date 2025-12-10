set terminal png size 1400,800 enhanced
set output 'comparacionrk4_h0.01_0.1.png'
set title 'Comparación de Métodos Numéricos'
set xlabel 'x'
set ylabel 'y'
set grid
set style data linespoints
set key top right
set datafile separator ','

plot '/home/cegb03/Documentos/Metodos-Numericos-Cpp/Diferenciacion Numerica/Ecuaciones Diferenciales/./rk4_0.01.txt' using 1:2 title 'Rk4 (h=0.01)' with linespoints linewidth 2 pointsize 0.8, '/home/cegb03/Documentos/Metodos-Numericos-Cpp/Diferenciacion Numerica/Ecuaciones Diferenciales/./rk4_0.10.txt' using 1:2 title 'Rk4 (h=0.1)' with linespoints linewidth 2 pointsize 0.8
