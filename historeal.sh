#!/bin/bash

fichier="$1"

if [ $# -ne 1 ]
then
	exit
fi

if [ $# -eq 1 ]
then
	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' "$fichier" > temp.csv
	cut -d';' -f3,4,5 temp.csv > temp1.csv
	sed  's/ //g' temp1.csv > temp2.csv
	touch temp3.csv
	gcc -o real mainreal.c
	./real temp2.csv temp3.csv
	grep -v '^$' temp3.csv > temp4.csv
	sed  's/ //g' temp4.csv > temp5.csv
	sort -t';' -k2 -n temp5.csv > temp6.csv
	sed  's/;/ /g' temp6.csv > temp7.csv
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' temp7.csv | sed 's/,/./g' > temp8.csv
	head -n 50 temp8.csv > real_vol50.csv
	tail -n 10 temp8.csv > real_vol10.csv

gnuplot <<EOF
set title "Histogramme des volumes traités des 50 plus petites usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_real_petit.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "real_vol50.csv" using 2:xtic(1) notitle lc rgb "magenta"
EOF

gnuplot <<EOF
set title "Histogramme des volumes traités des 10 plus grandes usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_real_grand.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "real_vol10.csv" using 2:xtic(1) title "" lc rgb "magenta"
EOF

sort -k1 -r temp2.csv > real_src.csv

	#rm temp*.csv
	#rm src_vol10.csv
	#rm src_vol50.csv

fi
