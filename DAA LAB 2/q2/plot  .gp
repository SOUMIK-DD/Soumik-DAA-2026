set title "2-Way vs 3-Way Merge Sort"
set xlabel "Input Size (n)"
set ylabel "Number of Comparisons"

set grid

plot "data.txt" using 1:2 with linespoints title "2-Way Merge Sort", \
     "data.txt" using 1:3 with linespoints title "3-Way Merge Sort"

pause -1 "Press Enter to close the graph"