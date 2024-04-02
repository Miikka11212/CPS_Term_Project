set title "Average, Max, and Min Temperatures per Century"
set ylabel "Temperature (C)"
set yrange [1:18]
set ytics 1
set grid y

set style data histogram
set style histogram clustered gap 1
set boxwidth 1
set style fill pattern 2
set title "Average Temp"
plot "q9.txt" every ::0::0 using 2 linestyle 7 title "19th Century", "q9.txt" every ::1::1 using 2 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 2 linestyle 4 title "21st Century"
set title "Max Temp"
plot "q9.txt" every ::0::0 using 3 linestyle 7 title "19th Century", "q9.txt" every ::1::1 using 3 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 3 linestyle 4 title "21st Century"
set title "Min Temp"
plot "q9.txt" every ::0::0 using 4 linestyle 7 title "19th Century", "q9.txt" every ::1::1 using 4 linestyle 2 title "20th Century", "q9.txt" every ::2::2 using 4 linestyle 4 title "21st Century"