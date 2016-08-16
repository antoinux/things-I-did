#!/bin/bash

domain=".enst.fr"
read s < machines

# echo "Enter username"
# read user
user=aturquetil

# echo "Enter password"
# read -s password
password=

sshpass -p $password scp -o StrictHostKeyChecking=no hashcode_main.cpp $user@$s$domain:hashcode_main.cpp