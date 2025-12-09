#!/bin/bash

#début mesure du temps
debut=$(date +%s.%N)

#verification bon nombre d'arguments
if [ $# -ne 3 ]
then 
	echo "ERREUR: le nombre d'argument donné n'est pas le bon !"
	fin=$(date +%s.%N)
	time=$(echo "($fin - $debut)*1000" | bc)
    	echo "Le programme a mis ${time} ms à être exécuté"
    	exit 1
fi



if [ ! -r "$DATAFILE" ]
then
	echo "ERREUR: fichier d'entrée introuvable ou non lisible !"
	fin=$(date +%s.%N)
	time=$(echo "($fin - $debut)*1000" | bc)
    	echo "Le programme a mis ${time} ms à être exécuté"
	exit 2
fi



#partie appel histogramme
bash 

#partie appel code C

#verif retour code C



fin=$(date +%s.%N)
time=$(echo "($fin - $debut)*1000" | bc)
echo "Durée totale : ${time} ms"

partie histo
if [ $# -ne 3 ]
then
	awk -F';' '$NF ~ /-/' la.csv > temp.csv
	cut -d';' -f2,4  temp.csv > temp2.csv
	sed -i 's/ //g' temp2.csv
	sed -i 's/;/ /g' temp2.csv
	sort 
fi

gnuplot <<EOF
set terminal pdf
set output "hitotest.png"
set style data histograms
set style fill solid 1.0 border -1
set boxwidth 0.8
plot "temp2.txt" using 2:xtic(1) notitle
EOF
