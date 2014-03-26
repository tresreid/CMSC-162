#!/bin/bash


if [ $1 != "--empty" -a $1 != "--list" ]
then
    FILE=$1

elif [ $2 != "--empty" -a $2 != "--list" ]
then 
    FILE=$2
elif [ $3 != "--empty" -a $2 != "--list" ]
then 
    FILE=$3
fi

mv "$FILE" ~/.trash

if [[ $1 == "--empty" ]] || [[ $2 == "--empty" ]] || [[ $3 == "--empty" ]]
then
    rm ~/.trash/*
fi

if [[ $1 == "--list" ]] || [[ $2 == "--list" ]] || [[ $3 == "--list" ]]
then
    cd ~/.trash
    ls
fi

