#!/bin/bash

#début mesure du temps
debut=$(date +%s.%N)

#verification bon nombre d'arguments
if [ $# -lt 3 ] #trop peu d'arguments
then 
	echo "ERREUR: commande icomplete, il manque des arguments !"
	#Trouve et donne le temps mis par le programme pour l'executionS
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
	time=$((fin-debut))
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
		option="$3"
		
		case "$option" in
			max) 
				#partie appel fonction histogramme max
				bash histomax.sh "$fichier";;
			src)
				#partie appel fonction histogramme src
				bash histosrc.sh "$fichier";;
			real)
				#partie appel fonction histogramme max
				bash historeal.sh "$fichier";;
			*)
				echo "Commande inconnue, veuillez relancer le programme"
				#Trouve et donne le temps mis par le programme pour l'execution
    				fin=$(date +%s.%N)
				time=$((fin-debut))
				time=`echo "$fin-$debut" | bc`
				time=`echo "$time*1000" | bc`
			    	echo "Le programme a mis $time ms à être exécuté"
    				exit 4;;
		esac;;
	
	#partie fuite en C
	leaks)
		usine="$3"
		#partie appel code C
		#make
		gcc -o leaks leaks.c
		./leaks "$fichier" "$usine"
		#verif retour code C
		ret=$?
		if [ $ret -ne 0 ] 
		then
			echo "Échec du code C !"
			fin=$(date +%s.%N)
			time=$((fin-debut))
			time=`echo "$fin-$debut" | bc`
			time=`echo "$time*1000" | bc`
		    	echo "Le programme a mis $time ms à être exécuté"
			exit 5
		fi
		;;
	*)
		echo "Commande inconnue, veuillez relancer le programme"
		#Trouve et donne le temps mis par le programme pour l'execution
		fin=$(date +%s.%N)
		time=$((fin-debut))
		time=`echo "$fin-$debut" | bc`
		time=`echo "$time*1000" | bc`
	    	echo "Le programme a mis $time ms à être exécuté"
    		exit 5;;
esac


#Trouve et donne le temps mis par le programme pour l'execution
fin=$(date +%s.%N)
time=`echo "$fin-$debut" | bc`
time=`echo "$time*1000" | bc`
echo "Durée totale : $time ms"
