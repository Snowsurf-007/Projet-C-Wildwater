#!/bin/bash

#début mesure du temps
debut=$(date +%s.%N)

#verification bon nombre d'arguments
if [ $# -lt 3 ] #trop peu d'arguments
then 
	echo "ERREUR: commande incomplete, il manque des arguments !"
	
	#Trouve et donne le temps mis par le programme pour l'execution
	fin=$(date +%s.%N)
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
    	exit 1
fi

if [ $# -gt 3 ] #trop d'arguments
then 
	echo "ERREUR: trop d'argument !"
	
	#Trouve et donne le temps mis par le programme pour l'execution
	fin=$(date +%s.%N)
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
    	exit 2
fi

fichier="$1"

#verification fichier
if [ ! -r "$fichier" ]
then
	echo "ERREUR: fichier d'entrée introuvable ou non lisible !"
	
	#Trouve et donne le temps mis par le programme pour l'execution
	fin=$(date +%s.%N)
	time=`echo "$fin-$debut" | bc`
	time=`echo "$time*1000" | bc`
    	echo "Le programme a mis $time ms à être exécuté"
	exit 3
fi


#appel du bon programme en fct de la commande entrée
commande="$2"

case "$commande" in
	#partie histogramme en shell
	
	histo) 
		
		mkdir -p histogrammes
		mkdir -p fichiers_resultats
		
		option="$3"
		
		case "$option" in
			max) 
				#partie appel fonction histogramme max
				bash histomax.sh "$fichier"
				#verif retour code
				ret=$?
				if [ $ret -ne 0 ] 
				then
					echo "Échec de la création de l'histogramme !"
					fin=$(date +%s.%N)
					time=`echo "$fin-$debut" | bc`
					time=`echo "$time*1000" | bc`
		    			echo "Le programme a mis $time ms à être exécuté"
					exit 4
				fi
				;;
				
			src)	
				#partie appel fonction histogramme src
				bash histosrc.sh "$fichier"
				#verif retour code
				ret=$?
				if [ $ret -ne 0 ] 
				then
					echo "Échec de la création de l'histogramme !"
					fin=$(date +%s.%N)
					time=`echo "$fin-$debut" | bc`
					time=`echo "$time*1000" | bc`
		    			echo "Le programme a mis $time ms à être exécuté"
					exit 5
				fi
				;;
			real)
				bash historeal.sh "$fichier"
				#verif retour code
				ret=$?
				if [ $ret -ne 0 ] 
				then
					echo "Échec de la création de l'histogramme !"
					fin=$(date +%s.%N)
					time=`echo "$fin-$debut" | bc`
					time=`echo "$time*1000" | bc`
		    			echo "Le programme a mis $time ms à être exécuté"
					exit 6
				fi
				;;
			all)	
				bash histoall.sh "$fichier"
				#verif retour code
				ret=$?
				if [ $ret -ne 0 ] 
				then
					echo "Échec de la création de l'histogramme !"
					fin=$(date +%s.%N)
					time=`echo "$fin-$debut" | bc`
					time=`echo "$time*1000" | bc`
		    			echo "Le programme a mis $time ms à être exécuté"
					exit 7
				fi
				;;
			*)
				echo "Commande inconnue, veuillez relancer le programme"
				
				#Trouve et donne le temps mis par le programme pour l'execution
    				fin=$(date +%s.%N)
					time=`echo "$fin-$debut" | bc`
					time=`echo "$time*1000" | bc`
			    	echo "Le programme a mis $time ms à être exécuté"
    				exit 8;;
		esac;;
	
	#partie fuite en C
	leaks)
		usine="$3"
		
		awk -F';' -v var="$usine" '$1 ~ ("^" var) { print }' "$fichier" > leaks_usine.csv
		awk -F';' -v var="$usine" '$2 ~ ("^" var) { print }' "$fichier" >> leaks_usine.csv
		awk -F';' -v var="$usine" '$3 ~ ("^" var) { print }' "$fichier" >> leaks_usine.csv
		awk -F';' -v var="$usine" '$3 ~ ("^" var) { print }' leaks_usine.csv > temp.csv
		awk -F';' -v var="$usine" '$1 ~ /-/ && $3 $3 ~ ("^" var) {print $2 ";" $3 ";" $4 ";" $5}' temp.csv > SU.dat
		cut -d';' -f2,3,5 leaks_usine.csv > fichier_filtré.csv
		awk -F';' '$1 ~ /-/ && $3 ~ /-/ {print $2 ";" $4}' leaks_usine.csv > US.dat
		cut -d';' -f2,3,5 leaks_usine.csv > fichier_filtré.csv
		awk -F';' '$2 ~ /Storage #[A-Za-z0-9]+/' fichier_filtré.csv >> US.dat
		awk -F';' '$1 ~ /Storage #[A-Za-z0-9]+/' fichier_filtré.csv > SJ.dat
		awk -F';' '$1 ~ /Junction #[A-Za-z0-9]+/' fichier_filtré.csv > JR.dat
		awk -F';' '$1 ~ /Service #[A-Za-z0-9]+/' fichier_filtré.csv > RU.dat
		
		#partie appel code C
		make leaks
		./leaks SU.dat US.dat SJ.dat JR.dat RU.dat > fuites.dat		
		
		#verif retour code C
		retc=$?
	
		if [ $retc -ne 0 ] 
		then
			clear
			echo "Échec du code C !"
			fin=$(date +%s.%N)
			time=`echo "$fin-$debut" | bc`
			time=`echo "$time*1000" | bc`
		    	echo "Le programme a mis $time ms à être exécuté"
			exit 9
		fi
		
		mv fuites.dat fichiers_resultats/
		
		;;
	*)
		echo "Commande inconnue, veuillez relancer le programme"
		
		#Trouve et donne le temps mis par le programme pour l'execution
		fin=$(date +%s.%N)
		time=`echo "$fin-$debut" | bc`
		time=`echo "$time*1000" | bc`
	    echo "Le programme a mis $time ms à être exécuté"
    	exit 10;;
esac

#Trouve et donne le temps mis par le programme pour l'execution
fin=$(date +%s.%N)
time=`echo "$fin-$debut" | bc`
time=`echo "$time*1000" | bc`
echo "Durée totale : $time ms"
