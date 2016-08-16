#!/bin/bash

######### FICHIER DE LA MACHINE MAITRE #########

# Fais une requête pour trouver la meilleure réponse donnée par tous les esclaves.

sshoptions="-o StrictHostKeyChecking=no"
domain=".enst.fr"

# echo "Enter username"
# read user
user=aturquetil

# echo "Connexion to $user@$domain"
# echo "Enter password"
# read -s password

read machine < "$1"

# On appelle simplement find_best.sh sur les esclaves. C'est lui qui s'occupe effectivement de la recherche.
ssh $sshoptions $user@$machine$domain hashcode/find_best.sh