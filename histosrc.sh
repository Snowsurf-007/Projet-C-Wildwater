#!/bin/bash

if [ $# -ne 1 ]
then
	exit
fi

if [ $# -eq 1 ]
then
	fichier="$1"
	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' "$fichier" > temp.csv
	cut -d';' -f3,4 temp.csv > temp1.csv
	touch temp2.csv
	make histo
	./histo 1 temp1.csv temp2.csv
	grep -v '^$' temp2.csv > temp3.csv
	sed  's/ //g' temp3.csv > temp4.csv
	sort -t';' -k2 -n temp4.csv > temp5.csv
	sed  's/;/ /g' temp5.csv > temp6.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' temp6.csv | sed 's/,/./g' > temp7.csv
	head -n 50 temp7.csv > src_vol50.csv
	tail -n 10 temp7.csv > src_vol10.csv

gnuplot <<EOF
set title "Histogramme des volumes prélevés des 50 plus petites usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_src_petit.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "src_vol50.csv" using 2:xtic(1) title "" lc rgb "magenta"
EOF

gnuplot <<EOF
set title "Histogramme des volumes prélevés des 10 plus grandes usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_src_grand.png"
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "src_vol10.csv" using 2:xtic(1) title "" lc rgb "magenta"
EOF
	
	echo "Nom usine;Volumes prélevés (M.m^3)" > vol_src.csv
	sort -k2 -r src_vol10.csv > temp9.csv
	sort -k2 -r src_vol50.csv >> temp9.csv
	sed  's/ /;/g' temp9.csv >> vol_src.csv
	mv vol_src.csv fichiers_resultats/
	mv histo_src_petit.png histogrammes/
	mv histo_src_grand.png histogrammes/
	
	rm temp*.csv 
	rm src_vol10.csv
	rm src_vol50.csv

fi
