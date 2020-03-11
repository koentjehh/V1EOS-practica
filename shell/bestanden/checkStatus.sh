#!/bin/bash
touch log.txt
for bestand in $(ls); do 
    if command ; then
        echo $bestand " - Command successful" >> log.txt
    else
        echo $bestand " - Command failed" >> log.txt
fi
done