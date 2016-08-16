#!/bin/bash

######### FICHIER DES MACHINES ESCLAVES #########

# Arrête les jobs sur les machines préentes dans le fichier "started", c'est à dire qu'elles ont signalé avoir récupéré le verrou.

cd /cal/homes/aturquetil/hashcode
mkdir locks
mkdir started
cd started

# On remarque que "rm $s" est commentée : Normallement on pourrait le décommenter mais ça ne coûte pas grand chose de garder une trace
# des machines ayant lancé un job récemment, et en cas de problème de daemon fou (ce qu'on aimerait éviter, encore une fois),
# ça rend le stop plus robuste : Si il fail une fois pour une raison obscure, on peut retenter autant qu'on veut.

nb_thread=4
for s in `ls`
do
	touch ../locks/$s
# 	rm $s
done