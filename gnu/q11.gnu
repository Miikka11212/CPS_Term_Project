set title 'Average Land, Average Ocean'
set xlabel 'Years'
set ylabel 'Temperature'
set xtics (1850, 1875, 1900, 1925, 1950, 1975, 2000, )
set yrange [0:20]
set ytics 2
plot 'question8.dat' using 1:2 title "Yearly Average Temp" with l lw 4, \
'question8.dat' using 1:3 title "Average Yearly Max Temp" with l lc 'red', \
'question8.dat' using 1:4 title "Average Yearly Min Temp" with l lc 'blue'
