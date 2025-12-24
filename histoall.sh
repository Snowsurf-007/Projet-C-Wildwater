
#!/bin/bash

if [ $# -ne 1 ]
then
	echo "la"
	exit 40
fi

if [ $# -eq 1 ]
then
	fichier="$1"
	#src
	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' "$fichier" > tempsrc.csv
	cut -d';' -f3,4 tempsrc.csv > tempsrc1.csv
	touch tempsrc2.csv
	gcc -o histosrc histosrc.c
	./histosrc tempsrc1.csv tempsrc2.csv
	grep -v '^$' tempsrc2.csv > tempsrc3.csv
	sed 's/ //g' tempsrc3.csv > tempsrc4.csv
	sort tempsrc4.csv > tempsrc5.csv
	sed 's/;/ /g' tempsrc5.csv > tempsrc6.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' tempsrc6.csv > tempsrc7.csv
	sed 's/ /;/g' tempsrc7.csv > tempsrc8.csv
	sed 's/,/./g' tempsrc8.csv > tempsrc9.csv
	cut -d';' -f2 tempsrc9.csv > tempsrc10.csv
	cut -d';' -f1 tempsrc9.csv > tempnom.csv
	#max
	awk -F';' '$NF ~ /-/' $1 > tempmax.csv
	cut -d';' -f2,4 tempmax.csv > tempmax2.csv #garde uniquement la colonne 2 et la colonne 4
	sed 's/ //g' tempmax2.csv > tempmax.csv #suppression des espaces
	sed 's/;/ /g' tempmax.csv > tempmax2.csv #remplace ; par un espace
	sort tempmax2.csv > tempmax.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' tempmax.csv > tempmax2.csv
	sed 's/ /;/g' tempmax2.csv > tempmax3.csv 
	sed 's/,/./g' tempmax3.csv > tempmax4.csv 
	cut -d';' -f2 tempmax4.csv > tempmax5.csv
	#real
	awk -F';' '$1 ~ /-/ && $2 != "-" && $3 != "-" && $4 != "-" &&  $NF != "-"' "$fichier" > tempreal.csv
	cut -d';' -f3,4,5 tempreal.csv > tempreal1.csv
	sed  's/ //g' tempreal1.csv > tempreal2.csv
	touch tempreal3.csv
	gcc -o historeal historeal.c
	./historeal tempreal2.csv tempreal3.csv
	grep -v '^$' tempreal3.csv > tempreal4.csv
	sed  's/ //g' tempreal4.csv > tempreal5.csv
	sort tempreal5.csv > tempreal6.csv
	sed  's/;/ /g' tempreal6.csv > tempreal7.csv
	#transforme les chiffres de la deuxiemes colones en flottant et divise
	awk '{ printf "%s %.3f\n", $1, $2 / 1000 }' tempreal7.csv > tempreal8.csv
	sed  's/ /;/g' tempreal8.csv > tempreal9.csv
	sed  's/,/./g' tempreal9.csv > tempreal10.csv
	cut -d';' -f2 tempreal10.csv > tempreal11.csv
	touch tempnv.csv
	gcc -o all all.c
	./all tempnom.csv tempmax5.csv tempreal11.csv tempsrc10.csv tempnv.csv
	grep -v '^$' tempnv.csv > temp6.csv
	sort -k2 -n temp6.csv > temp7.csv
	sed  's/;/ /g' temp7.csv > vol_all.csv
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
