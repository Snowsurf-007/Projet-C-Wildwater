#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier arfument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort max_vol.dat
	head -n 10 temp2.csv > max_vol10.date
	tail -n 50 temp2.csv > max_vol50.date

fi

gnuplot <<EOF
set terminal png
set output "hitotest.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "max_vol10.date" using 2:xtic(1) notitle
EOF

gnuplot <<EOF
set terminal png
set output "hitotest2.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "max_vol50.date" using 2:xtic(1) notitle
EOF


#cat temp.txt
#echo "deuxieme"
#cat ID.txt #fichier avec les ID
#cat eau.txt	#fichier avec l'eau
