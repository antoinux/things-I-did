#!/bin/bash

######### FICHIER DE LA MACHINE MAITRE #########

# Commande l'arrêt de tout les jobs à distance.

sshoptions="-o StrictHostKeyChecking=no"
domain=".enst.fr"

# echo "Enter username"
# read user
user=aturquetil

# echo "Enter password"
# read -s password

read machine < "$1"

# On appelle simplement le fichier d'arrêt présent sur les esclaves. C'est stop_launch.sh qui arrête effectivement les processus.
ssh $sshoptions $user@$machine$domain hashcode/stop_launch.sh