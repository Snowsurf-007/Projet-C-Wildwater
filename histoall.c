#!/bin/bash

if [ $# -ne 1 ]
then
	echo "la"
	exit 40
fi

if [ $# -eq 1 ]
then
	fichier="$1"
	bash histomax.sh "$fichier"
	bash histosrc.sh "$fichier"
	bash historeal.sh "$fichier"
	touch temp4.csv
	cd ./fichiers_resultats
	awk 'NR > 1' vol_max.csv > temp1.csv
	awk 'NR > 1' vol_real.csv > temp2.csv
	awk 'NR > 1' vol_src.csv > temp3.csv
	mv temp1.csv ../
	mv temp2.csv ../
	mv temp3.csv ../
	cd ..
	make histo
	./histo 3 temp1.csv temp2.csv temp3.csv temp4.csv
	paste -d";" temp1.csv temp2.csv temp3.csv> fusion.csv
	cut -d';' -f1,2,4,6 fusion.csv > vol_all.csv
	grep -v '^$' temp4.csv > temp5.csv
	sort -t';' -k2 -n temp5.csv > temp6.csv
	sed  's/;/ /g' temp6.csv > vol_all.csv
	tail -n 10 vol_all.csv > all_vol10.csv
	head -n 50 vol_all.csv > all_vol50.csv

#gnuplot histogramme petit
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
set style histogram rowstacked
plot "all_vol50.csv" using 2:xtic(1) lc rgb "cyan" title "Capacité max", \
     "" using 3 lc rgb "magenta" title "Vol. prélevés", \
     "" using 4 lc rgb "yellow" title "Vol. traités"
EOF

#gnuplot histogramme grand
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
set xlabel "Nom des usines" font ",16" offset 0, -5
set ylabel "Volume (M.m^3)" font ",16"
set xtics rotate by -90 font ",10" nomirror
set yrange [0.5:*]
set style fill solid 1.0 border -1
set style data histograms
set boxwidth 1
set style histogram rowstacked
plot "all_vol10.csv" using 2:xtic(1) lc rgb "cyan" title "Capacité max", \
     "" using 3 lc rgb "magenta" title "Vol. prélevés", \
     "" using 4 lc rgb "yellow" title "Vol. traités"
EOF

	#fichier de sortie propre dans le bon format
	echo "Nom usine;Capacité maximale (M.m^3);Volumes prélevés (M.m^3);Volume totale traités (M.m^3)" > vol_max.csv #ajoute une entete au fichier
	sort -k2 -r all_vol10.csv > temp7.csv #tris dans le sens décroissant en fct de la colonne 2 et met dans temp9
	sort -k2 -r all_vol50.csv >> temp7.csv #tris dans le sens décroissant en fct de la colonne 2 et ajoute a temp9
	sed  's/ /;/g' temp7.csv >> vol_all.csv #remplace les epaces par ; et ajoute temp7 trié dans vol_max.csv

	#ranger le fichier de sortie dans le dossier
	mv vol_all.csv fichiers_resultats/
	mv histo_all_petit.png histogrammes/
	mv histo_all_grand.png histogrammes/

	#supprimer les fichiers intermédiaires
	rm temp*.csv
	rm fusion.csv
	rm all_vol10.csv
	rm all_vol50.csv
fi
