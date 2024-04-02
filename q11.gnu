set title 'Average Land, Average Ocean'
set xlabel 'Years'
set ylabel 'Temperature'
set xtics (1850, 1875, 1900, 1925, 1950, 1975, 2000, 2015)
set yrange [0:20]
set ytics 2
plot 'q11.txt' using 1:2 title "Yearly Average Land Temp" with lines lw 1 lc rgb "red", \
'q11.txt' using 1:3 title "Yearly Average Ocean Temp" with l lc rgb 'blue'