#!/bin/bash
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier arfument
	cut -d';' -f2,4 temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort temp2.csv
	head -n 10 temp2.csv > max_vol10.date
	tail -n 50 temp2.csv > max_vol50.date

fi

gnuplot <<EOF
set terminal png
set output "histogrands.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "max_vol10.date" using 2:xtic(1) title "10 premiers"
EOF

gnuplot <<EOF
set terminal png
set output "histopetits.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "max_vol50.date" using 2:xtic(1) title "50 derniers"
EOF


#cat temp.txt
#echo "deuxieme"
#cat ID.txt #fichier avec les ID
#cat eau.txt	#fichier avec l'eau


#cat temp.txt
#echo "deuxieme"
#cat ID.txt #fichier avec les ID
#cat eau.txt	#fichier avec l'eau
