#!/bin/bash

######### FICHIER DE LA MACHINE MAITRE #########

# Permet le lancement à distance sur plusieurs machines du même programme.

domain=".enst.fr"
src=$2
sshoptions="-o StrictHostKeyChecking=no"
coptions="-O2 -std=c++11"

# echo "Enter username"
# read user
user=aturquetil
# echo hey
# echo "Enter password"
# read -s password
# echo hey
read machine < "$1"

# Tous les fichiers nécessaires aux machines esclaves sont présentes sur la machine maitre
# au cas où certains se perdraient. Toute l'architecture des esclaves est reconstruite à
# chaque lancement afin de garantir le comportement des scripts.

# On copie donc tout ce qu'il faut sur l'esclave.
ssh $sshoptions $user@$machine$domain mkdir hashcode
echo "Création du dossier hashcode faite !"
g++ $src $coptions -o to_copy/prog
echo "Compilation de $src faite !"
cp $src $1 "in" to_copy
cd to_copy
for f in `ls`
do
	scp $sshoptions $f $user@$machine$domain:hashcode/$f
done
cd ..
echo "Copie des fichiers nécessaires faite !"

nb_tread=4
# On lance ensuite nb_tread jobs sur chaque machine. Pour l'instant on a fixé nb_thread à 1.
# A voir si le passer à 2 ou 3 pourrait causer des soucis de concurrence et amener à une légère
# modification de l'architecture.
while IFS='' read -r line || [[ -n "$line" ]];do
# 	for i in `seq 1 $nb_thread`
# 	do
# 		sleep 10
		ssh $sshoptions $user@$line$domain hashcode/launch.sh $line 1 2>errr &
# 	done
done < "$1"

while IFS='' read -r line || [[ -n "$line" ]];do
# 	for i in `seq 1 $nb_thread`
# 	do
		ssh $sshoptions $user@$line$domain hashcode/launch.sh $line 2 2>errr &
# 	done
done < "$1"

while IFS='' read -r line || [[ -n "$line" ]];do
# 	for i in `seq 1 $nb_thread`
# 	do
		ssh $sshoptions $user@$line$domain hashcode/launch.sh $line 3 2>errr &
# 	done
done < "$1"

while IFS='' read -r line || [[ -n "$line" ]];do
# 	for i in `seq 1 $nb_thread`
# 	do
		ssh $sshoptions $user@$line$domain hashcode/launch.sh $line 4 2>errr &
# 	done
done < "$1"