#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier argument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort -k2 -n temp2.csv > temp3.csv
	head -n 50 temp3.csv > max_vol50.date
	tail -n 10 temp3.csv > max_vol10.date
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ $2 = $2 / 1000; print $1, $2 }' temp3.csv > temp3div.csv
	tail -n 10 temp3div.csv > max_vol10.date
	head -n 50 temp3div.csv > max_vol50.date
fi

gnuplot <<EOF
set title "50 plus petites usines" font ",20" center
set terminal png size 1600,800 font "Arial,10"
set lmargin 10
set rmargin 5
set tmargin 5
set bmargin 15
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histolow.png"
set xlabel "Nom des usines"
set ylabel "Volume (M.m^3)"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:1.25]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol50.date" using 2:xtic(1) title ""
EOF

gnuplot <<EOF
set title "10 plus grandes usines" font ",20" center
set terminal png size 1600,800 font "Arial,10"
set lmargin 10
set rmargin 5
set tmargin 5
set bmargin 15
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histohigh.png"
set xlabel "Nom des usines"
set ylabel "Volume (M.m^3)"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:75000]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol10.date" using 2:xtic(1) title ""
EOF
