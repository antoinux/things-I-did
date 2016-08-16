#!/bin/bash

######### FICHIER DES MACHINES ESCLAVES #########

# Affiche la meilleure réponse so far :)

cd hashcode
mkdir results
cd results

best="-1000000"
best_i=0

for machine in `ls`
do
	if [ "$machine" != "best" ] && [ "$machine" != "best_score" ]
	then
		cur=$(../traductors/traductor$machine $machine)
		if [ "$cur" -gt "$best" ]
		then
			best=$cur
			best_i=$machine
		fi
	fi
done

read best_s <best_score
if [ "$best" -gt "$best_s" ]
then
	cp $best_i best
	best_s=$best
fi
# Ce script étant la plupart du temps appelé par get_best.sh par le maître en ssh, stdout est relié au stdout du maître,
# donc la réponse est directement affichée dans la console du maître :)

cat best
echo $best_s
