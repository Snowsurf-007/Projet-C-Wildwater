#!/bin/bash
set -x
if [ $# -eq 3 ]
then
exit
fi

if [ $# -ne 3 ]
then
awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' c-wildwater_v3.dat > temp.csv
head temp.csv
cut -d';' -f3,4 temp.csv > temp1.csv
touch temp2.csv
gcc -o temp main.c
./temp temp1.csv temp2.csv
grep -v '^$' temp2.csv > temp3.csv
sed  's/ //g' temp3.csv > temp4.csv
sort -t';' -k2 -n temp4.csv > temp5.csv
sed  's/;/ /g' temp5.csv > temp6.csv
head -n 50 temp6.csv > src_vol50.csv
tail -n 10 temp6.csv > src_vol10.csv
cat src_vol10.csv
cat src_vol50.csv
fi

gnuplot <<EOF
set terminal png
set title "Histogramme des volumes preleves des 50 plus petites usines" font ",20"
set terminal png size 1600,1000 font "Arial,12"
set output "histopetites_src.png"
set lmargin 15
set bmargin 25
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (m³)" font ",16"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
set xtics rotate by -90 font ",8" offset 0,-4 nomirror
set ytics nomirror
set yrange [0:*]
set format y "%.0s%c"
plot "src_vol50.csv" using 2:xtic(1) notitle lc rgb "blue"

EOF

gnuplot <<EOF
gnuplot <<EOF
set terminal png size 1600,1000 font "Arial,12"
set output "histo_max_grand.png"
set title "Histogramme des volumes preleves des 10 plus grandes usines" font ",20"
set lmargin 15
set bmargin 22
set rmargin 5
set tmargin 5
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (m³)" font ",16"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
set xtics rotate by -90 font ",10" offset 0,-3 nomirror
set ytics nomirror
set yrange [0:*]
set format y "%.0s%c"

plot "src_vol10.csv" using 2:xtic(1) notitle lc rgb "red"
EOF


EOF

