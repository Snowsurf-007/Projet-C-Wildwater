#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier arfument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort max_vol.dat
	head -n 50 temp2.csv > max_vol.date
	tail -n 50 temp2.csv > max_vol.date
	#awk -F';' '$1 ~ /'$2'/' $1 > usine.csv
fi

gnuplot <<EOF
set terminal png
set output "hitotest.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "max_vol.date" using 2:xtic(1) notitle
EOF

#cat temp.txt
#echo "deuxieme"
#cat ID.txt #fichier avec les ID
#cat eau.txt	#fichier avec l'eau


