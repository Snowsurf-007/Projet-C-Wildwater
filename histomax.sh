#!/bin/bash

#Verification du bon nombre d'arguments
if [ $# -ne 1 ]
then
	exit 10
fi

if [ $# -eq 1 ]
then
	awk -F';' '$NF ~ /-/' $1 > temp.csv #mettre le nom du fichier en premier argument
	cut -d';' -f2,4 temp.csv > temp2.csv #garde uniquement la colonne 2 et la colonne 4
	sed  's/ //g' temp2.csv > temp.csv #suppression des espaces
	sed  's/;/ /g' temp.csv > temp2.csv #remplace ; par un espace
	sort -k2 -n temp2.csv > temp.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' temp.csv | sed 's/,/./g' > temp2.csv
	#crée 2 fichiers avec les grandes et petites valeurs
	tail -n 10 temp2.csv > max_vol10.csv
	head -n 50 temp2.csv > max_vol50.csv

#gnuplot histogramme petit
gnuplot <<EOF
set title "Histogramme des capacités maximales des 50 plus petites usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set output "histo_max_petit.png"
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol50.csv" using 2:xtic(1) title "" lc rgb "blue"
EOF

#gnuplot histogramme grand
gnuplot <<EOF
set title "Histogramme des capacités maximales des 10 plus grandes usines" font ",20" center
set terminal png size 1600,1000 font "Arial,12"
set lmargin 13
set rmargin 5
set tmargin 5
set bmargin 20
set xtics rotate by -90 offset 0,-2 nomirror
set output "histo_max_grand.png"
set xlabel "Nom des usines" font ",16"
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
plot "max_vol10.csv" using 2:xtic(1) title "" lc rgb "blue"
EOF

	#fichier de sortie propre dans le bon format
	echo "Nom usine;Capacité maximale (M.m^3)" > vol_max.csv #ajoute une entete au fichier
	sort -k2 -r max_vol10.csv > temp9.csv #tris dans le sens décroissant en fct de la colonne 2 et met dans temp9
	sort -k2 -r max_vol50.csv >> temp9.csv #tris dans le sens décroissant en fct de la colonne 2 et ajoute a temp9
	sed  's/ /;/g' temp9.csv >> vol_max.csv #remplace les epaces par ; et ajoute temp9 rié dans vol_max.csv

	#ranger le fichier de sortie dans le dossier
	mv vol_max.csv fichiers_resultats/
	mv histo_max_petit.png histogrammes/
	mv histo_max_grand.png histogrammes/

	#supprimer les fichiers intermédiaires
	rm temp*.csv
	rm max_vol10.csv
	rm max_vol50.csv

fi
