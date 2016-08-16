#!/bin/bash

######### FICHIER DES MACHINES ESCLAVES #########

# Fonctionnalité abandonnée car peu utile finalement.

# EVITER DONC DE LANCER CE SCRIPT !

cd results

# cur=$(../traductor ../temp_results/c130-17)
# echo $cur

if [ -f best ]
then
	cur=$(../traductor results)
else
	cur_best="0"
fi

while [ 1=1 ]
do
	for machine in `ls`
	do
		if [ "$machine" != "best" ]
		then
			cur=$(../traductor $machine)
			if (( cur > cur_best ))
			then
				cur_best=$cur
				cp $machine best
			fi
		fi
	done
	sleep 1
done