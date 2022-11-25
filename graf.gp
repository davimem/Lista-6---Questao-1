set terminal pdf
set output "graf.pdf"
set key left top
plot"n10.dat" w p pt 7 t "N=10","n100.dat" w p pt 4 t "N=100","n1000.dat" w p pt 6 ps 0.3 t "N=10000"
set terminal x11
replot