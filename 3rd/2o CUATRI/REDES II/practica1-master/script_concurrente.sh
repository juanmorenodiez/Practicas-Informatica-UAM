#!/bin/bash
x=0
while [ $x -le 4 ]
do
  ./client HOLA$x &
  x=$(( $x + 1 ))
done
