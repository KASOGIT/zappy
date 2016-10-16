#!/bin/sh
## launch_ai.sh for launch_ai in /home/julien_k/PSU_2015_zappy
## 
## Made by Kévin Julien
## Login   <julien_k@epitech.net>
## 
## Started on  Sun Jun 26 15:42:26 2016 Kévin Julien
## Last update Sun Jun 26 20:18:11 2016 
##

cmpt=0
while [ $cmpt -lt $1 ] ; do
    cmpt=$(($cmpt+1))
    ./zappy_ai -n team1 -p 4242 -h localhost &
    sleep 0.2
done
    
