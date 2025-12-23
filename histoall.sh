#!/bin/bash

if [ $# -ne 1 ]
then
	exit 40
fi

if [ $# -eq 1 ]
then
	fichier="$1"
	bash histomax.sh "$fichier"
	bash histosrc.sh "$fichier"
	bash historeal.sh "$fichier"
	cd ./fichiers_resultats
	touch temp4.csv
	awk 'NR > 1' vol_max.csv > temp1.csv
	awk 'NR > 1' vol_real.csv > temp2.csv
	awk 'NR > 1' vol_src.csv > temp3.csv
	gcc -o all all.c
	./all temp1.csv temp2.csv temp3.csv temp4.csv
	#paste -d";" temp1.csv temp2.csv temp3.csv> fusion.csv
	#rm temp*.csv
	mv temp4.csv ..
	cd ..
	#cut -d';' -f1,2,4,6 fusion.csv > vol_all.csv
	grep -v '^$' temp4.csv > temp5.csv
	sort -t';' -k2 -n temp5.csv > temp6.csv
	sed  's/;/ /g' temp6.csv > vol_all.csv
	tail -n 10 vol_all.csv > all_vol10.csv
	head -n 50 vol_all.csv > all_vol50.csv
fi
gnuplot <<EOF
set title "Histogramme global des 50 plus petites usines" font ",20" centerx  
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_all_petit.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.5:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
set style histogram rowstacked
plot "all_vol50.csv" using 2:xtic(1) lc rgb "cyan"    title "Colonne 2", \
     ""             using 3          lc rgb "magenta" title "Colonne 3", \
     ""             using 4          lc rgb "yellow"  title "Colonne 4"
EOF
gnuplot <<EOF
set title "Histogramme global des 10 plus grandes usines" font ",20" centerx  
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_all_grands.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.5:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
set style histogram rowstacked
plot "all_vol10.csv" using 2:xtic(1) lc rgb "cyan"    title "Colonne 2", \
     ""             using 3          lc rgb "magenta" title "Colonne 3", \
     ""             using 4          lc rgb "yellow"  title "Colonne 4"
EOF
