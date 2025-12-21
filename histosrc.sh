#!/bin/bash

if [ $# -ne 1 ]
then
	exit 20
fi

if [ $# -eq 1 ]
then

	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' $1 > temp.csv
	cut -d';' -f3,4 temp.csv > temp1.csv
	touch temp2.csv
	make leaks
	./leaks temp1.csv temp2.csv
	grep -v '^$' temp2.csv > temp3.csv
	sort -k2 -n temp3.csv > temp4.csv
	head -n 50 temp4.csv > src_vol50.csv
	tail -n 10 temp4.csv > src_vol10.csv
fi

gnuplot <<EOF
set title "Histogramme des volumes preleves des 50 plus petites usines" font ",20" center
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
set yrange [0.5:1.5]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "src_vol50.csv" using 2:xtic(1) title "" lc rgb "cyan"
EOF

gnuplot <<EOF
set title "Histogramme des volumes preleves des 10 plus grandes usines" font ",20" center
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
plot "src_vol10.csv" using 2:xtic(1) title "" lc rgb "cyan"
EOF

	sort -k1 -r temp2.csv > vol_src.csv

	#rm temp*.csv
	rm src_vol10.csv
	rm src_vol50.csv

fi
