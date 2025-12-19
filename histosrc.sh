#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' $1 > temp.csv
	cut -d';' -f3,4 temp01.csv > temp2.csv
	gcc -o src calc2.c 
	./src temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort -k2 -n temp2.csv > temp3.csv
	head -n 50 temp3.csv > max_vol50.csv
	tail -n 10 temp3.csv > max_vol10.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' temp3.csv | sed 's/,/./g' > vol_max.csv
	tail -n 10 vol_max.csv > max_vol10.csv
	head -n 50 vol_max.csv > max_vol50.csv
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
set yrange [0:2]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol50.csv" using 2:xtic(1) title "" lc rgb "cyan"
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
plot "max_vol10.csv" using 2:xtic(1) title "" lc rgb "cyan"
EOF

rm temp.csv
rm temp2.csv
rm max_vol10.csv
rm max_vol50.csv
