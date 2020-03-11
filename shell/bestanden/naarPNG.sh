#!/bin/bash
for bestand in $(find . -name '*.jpg'); do 
convert $bestand -resize 128x128! $bestand.png
done
