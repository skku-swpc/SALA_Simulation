set output "0.5_time_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:100]
set xlabel "Time (min)"
plot "0.5_time_error.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "1.0_time_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:100]
set xlabel "Time (min)"
plot "1.0_time_error.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "0.5_motion_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:200]
set xlabel "Motion Error (cm)"
plot "0.5_motion_error.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "1.0_motion_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:200]
set xlabel "Motion Error (cm)"
plot "1.0_motion_error.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "0.5_iot_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:250]
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "0.5_iot_error.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "1.0_iot_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:250]
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "1.0_iot_error.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "0.5_time_room.png"
set terminal png truecolor
set ylabel "Localization Accuracy (%)"
set yrange[70:110]
set ytics ("0"70, 80, 90, 100, ""110)
set xlabel "Time (min)"
plot "0.5_time_room.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "1.0_time_room.png"
set terminal png truecolor
set ylabel "Localization Accuracy (%)"
set yrange[70:110]
set ytics ("0"70, 80, 90, 100, ""110)
set xlabel "Time (min)"
plot "1.0_time_room.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "0.5_time_room2.png"
set terminal png truecolor
set ylabel "Localization Accuracy (%)"
set yrange[0:120]
set ytics (0, 20, 40, 60, 80, 100, ""120)
set xlabel "Time (min)"
plot "0.5_time_room2.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "1.0_time_room2.png"
set terminal png truecolor
set ylabel "Localization Accuracy (%)"
set yrange[0:120]
set ytics (0, 20, 40, 60, 80, 100, ""120)
set xlabel "Time (min)"
plot "1.0_time_room2.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "0.5_iot_room.png"
set terminal png truecolor
set yrange[0:3]
set ytics (""0, "False"1, "True"2, ""3)
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "0.5_iot_room.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "1.0_iot_room.png"
set terminal png truecolor
set yrange[0:3]
set ytics (""0, "False"1, "True"2, ""3)
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "1.0_iot_room.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "0.5_iot_room2.png"
set terminal png truecolor
set yrange[0:3]
set ytics (""0, "False"1, "True"2, ""3)
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "0.5_iot_room2.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "1.0_iot_room2.png"
set terminal png truecolor
set yrange[0:3]
set ytics (""0, "False"1, "True"2, ""3)
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "1.0_iot_room2.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "passive_time_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:50]
set xlabel "Time (min)"
plot "passive_time_error.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

reset
set output "passive_iot_error.png"
set terminal png truecolor
set ylabel "Localization Error (cm)"
set yrange[0:80]
set xlabel "IoT Device ID"
set style data histograms
set style fill solid 1.00 border -1
plot "passive_iot_error.txt" using 2:xtic(1) title "Convex" lc rgb "#000000", '' using 3 title "RSSI" lc rgb "#666666", '' using 4 title "SALA" lc rgb "#bbbbbb"

reset
set output "0.5_motion_room2.png"
set terminal png truecolor
set ylabel "Localization Accuracy (%)"
set yrange[0:120]
set ytics (0, 20, 40, 60, 80, 100, ""120)
set xlabel "Motion Error (cm)"
plot "0.5_motion_room2.txt" using 2:xtic(1) title "Convex" pt 6 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 3 title "RSSI" pt 3 ps 2 lw 2 lc rgb "#000000" with linespoints, '' using 4 title "SALA" pt 4 ps 2 lw 4 lc rgb "#000000" with linespoints

