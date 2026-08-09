set grid
set xlabel 'Number of elements (n)'
set ylabel 'Operation Count'
set key outside
set xrange [0:1000]

set title 'Search Operation'
plot 'operations.dat' using 1:2 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:3 with lines lw 2 title 'Sorted Array','operations.dat' using 1:4 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:5 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:6 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:7 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Insert Operation'
plot 'operations.dat' using 1:8 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:9 with lines lw 2 title 'Sorted Array','operations.dat' using 1:10 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:11 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:12 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:13 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Delete Operation'
plot 'operations.dat' using 1:14 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:15 with lines lw 2 title 'Sorted Array','operations.dat' using 1:16 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:17 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:18 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:19 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Minimum Operation'
plot 'operations.dat' using 1:20 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:21 with lines lw 2 title 'Sorted Array','operations.dat' using 1:22 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:23 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:24 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:25 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Maximum Operation'
plot 'operations.dat' using 1:26 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:27 with lines lw 2 title 'Sorted Array','operations.dat' using 1:28 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:29 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:30 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:31 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Predecessor Operation'
plot 'operations.dat' using 1:32 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:33 with lines lw 2 title 'Sorted Array','operations.dat' using 1:34 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:35 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:36 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:37 with lines lw 2 title 'Doubly Sorted'
pause -1
set title 'Successor Operation'
plot 'operations.dat' using 1:38 with lines lw 2 title 'Unsorted Array','operations.dat' using 1:39 with lines lw 2 title 'Sorted Array','operations.dat' using 1:40 with lines lw 2 title 'Singly Unsorted','operations.dat' using 1:41 with lines lw 2 title 'Singly Sorted','operations.dat' using 1:42 with lines lw 2 title 'Doubly Unsorted','operations.dat' using 1:43 with lines lw 2 title 'Doubly Sorted'
pause -1
