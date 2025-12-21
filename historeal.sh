#!/bin/bash

if [ $# -ne 1 ]
then
	exit 30
fi

if [ $# -eq 1 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier argument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed  's/ //g' temp2.csv > temp.csv
	sed  's/;/ /g' temp.csv > temp2.csv
	sort -k2 -n temp2.csv > temp.csv
	head -n 50 temp.csv > max_vol50.csv
	tail -n 10 temp.csv > max_vol10.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' temp.csv | sed 's/,/./g' > temp2.csv
	tail -n 10 temp2.csv > max_vol10.csv
	head -n 50 temp2.csv > max_vol50.csv

gnuplot <<EOF
set title "Histogramme des capacités maximales des 50 plus petites usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_max_petit.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.5:1.5]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol50.csv" using 2:xtic(1) title "" lc rgb "blue"
EOF

gnuplot <<EOF
set title "Histogramme des capacités maximales des 10 plus grandes usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_max_grand.png"
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:75000]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol10.csv" using 2:xtic(1) title "" lc rgb "blue"
EOF

	sort -k1 -r temp2.csv > vol_real.csv

	rm temp*.csv
	rm real_vol10.csv
	rm real_vol50.csv

fi
