#!/bin/bash

######### FICHIER DES MACHINES ESCLAVES #########

# Finit de construire l'architecture puis fait le job en boucle jusqu'à interruption par stop_launch.sh ou autre.

cd /cal/homes/aturquetil/hashcode

machine=$1
coptions="-O2 -std=c++11"
thread=$2

# Construction de l'architecture.
mkdir results
mkdir temp_results
mkdir locks
mkdir traductors
# Récupération du verrou en cas de besoin.
rm locks/$machine-$thread
# Chaque machine a son propre executable de traductor afin d'éviter la concurrence. Sinon ça devient assez rapidement messy.
rm traductors/traductor$machine
g++ $coptions traductor.cpp -o traductors/traductor$machine-$thread

# On maintient la meilleure réponse donnée par cette machine car il faut être capable de l'actualiser si on trouve mieux.
if [ -f results/$machine-$thread ]
then
	cur_best=$(traductors/traductor$machine-$thread results/$machine-$thread)
else
	cur_best="-1000000"
fi

# On signale qu'on a récupéré le verrou (sécurité supplémentaire dans l'implémentation, on ne voudrait de thread daemon fous).
mkdir started
touch started/$machine-$thread

# On lance le job tant que le verrou n'a pas été réclamé par l'intermédiaire d'un fichier $machine dans le dossier locks.
# while [ ! -f locks/$machine-$thread ]
# do
	echo "$machine-$thread active !" >&2
	./prog <in >temp_results/$machine-$thread
	cur=$(traductors/traductor$machine-$thread temp_results/$machine-$thread)

	if [ "$cur" -gt "$cur_best" ]
	then
		cp temp_results/$machine-$thread results/$machine-$thread
		cur_best=$cur
	fi
# done