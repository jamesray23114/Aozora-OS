#!/bin/bash

MAJOR=$(sed '1!d' build/VERSION)
MINOR=$(sed '2!d' build/VERSION)
PATCH=$(sed '3!d' build/VERSION)
export VERSTRING="Aozora-OS-$MAJOR.$MINOR.$PATCH ->"
PATCH=$(($PATCH+1))
printf "$MAJOR\n$MINOR\n$PATCH" > build/VERSION