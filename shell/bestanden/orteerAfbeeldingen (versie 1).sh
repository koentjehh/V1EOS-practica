#!/bin/bash
mkdir Afbeeldingen
for bestand in $(find . -name '*.jpg' -o -name '*.png'); do 
mv "$bestand" Afbeeldingen;
done
