#!/bin/bash
mkdir Afbeeldingen
for i in find $1 \(- name '*.jpg' -o - name '*.png' \) -exec mv{}; do 
$1/Afbeeldingen\;
	mv $1 $1/Afbeeldingen
done