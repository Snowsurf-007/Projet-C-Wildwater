#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier arfument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort -k2 -n temp2.csv > temp3.csv
	head -n 50 temp3.csv > max_vol50.date
	tail -n 10 temp3.csv > max_vol10.date
	#transform les chiffres de la deuxiemes colones en flottant et divise
	awk '$2/1000 ' temp3.csv > temp3div.csv
	tail -n 10 temp3div.csv > max_vol10.date
	head -n 50 temp3div.csv > max_vol50.date
fi

gnuplot <<EOF
set terminal png font "Arial,3"
set terminal png
set output "histopetits.png"
set style data histograms
set yrange [0:*]   # 0 jusqu’au max automatique
set style fill solid 1.0 border -1
set boxwidth 0.8
 #font réduit la taille de la police à 6
set xtics rotate by -90 font ",5" nomirror
set ylabel " en 10^-3 M.m^3 (eau traiter par an)"
set xlabel " Nom des usines"
plot "max_vol50.date" using 2:xtic(1) title "50 plus petites usines"
EOF

gnuplot <<EOF
set xtics rotate by -90 font ",6" nomirror
set terminal png font "Arial,3"
set terminal png
set xlabel " Nom des usines"
set output "histogrands.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
set ylabel " en 10^-3 M.m^3 (eau traiter par an)"
plot "max_vol10.date" using 2:xtic(1) title "10 plus grandes usines"
EOF
