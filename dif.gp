set terminal pdf
set output "diferenca.pdf"
plot "dif.dat" w l t "(N10-N1000)^2"
set terminal x11
replot