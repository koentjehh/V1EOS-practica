#!/bin/bash
case $1 in
	*.py) 
	python3 $1
	;;
	*sh)
	./$1 
	;;
	*.cc)
	cat $1
	 ;;
	*)
	echo 'gebruik voeruit [file.py|.sh|.cc]'
esac