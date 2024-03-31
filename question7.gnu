set title 'Average Yearly Temperature from 19th and 20th Centuries'
set xlabel 'Years (from start of century)'
set ylabel 'Temperature'
set xtics (0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 99)
set yrange [6:10]
plot 'question7.dat' using 1:2 title "19th Century" with l lc 'red', \
'question7.dat' using 1:3 title "20th Century" with l lc 'blue'
