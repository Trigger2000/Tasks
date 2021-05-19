set terminal svg enhanced size 1000 1000

set output "plot_insert.svg"
set xlabel "n"
set ylabel "t"
plot "./data_insert.dat" using 1:2 with lines

set output "plot_delete.svg"
set xlabel "n"
set ylabel "t"
plot "./data_delete.dat" using 1:2 with lines