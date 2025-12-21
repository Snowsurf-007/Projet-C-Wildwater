#!/bin/bash

if [ $# -ne 1 ]
then
	exit 40
fi

if [ $# -eq 1 ]
then
	fichier="$1"
	
	bash histomax.sh "$fichier"
	if [ $ret -ne 0 ] 
	then
		exit 41
	fi
	bash histosrc.sh "$fichier"
	if [ $ret -ne 0 ] 
	then
		exit 42
	fi
	bash historeal.sh "$fichier"
	if [ $ret -ne 0 ] 
	then
		exit 43
	fi
	
	cut -d';' -f2,4 temp.csv > temp2.csv
	
	tail -n 10 vol_all.csv > all_vol10.csv
	head -n 50 vol_all.csv > all_vol50.csv
	
fi
gnuplot <<EOF
set title "Histogramme global des 50 plus petites usines" font ",20" center
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
plot "max_vol50.csv" using 2:xtic(1), "" lc rgb "cyan" using3:xtic(1), "" lc rgb "magenta" using4:xtic(1), "" lc rgb "yellow" title
EOF

gnuplot <<EOF
set title "Histogramme global des 10 plus grandes usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set terminal png
set output "histo_all_grand.png"
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol10.csv" using 2:xtic(1), "" lc rgb "cyan" using3:xtic(1), "" lc rgb "magenta" using4:xtic(1), "" lc rgb "yellow" title
EOF
