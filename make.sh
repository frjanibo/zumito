#!/bin/bash
#export Z88DK_PATH=/home/fjnieto/dev/personal/zx/z88dk10
#export Z80_OZFILES=$Z88DK_PATH/bin
#export ZCCCFG="${Z88DK_PATH}/lib/config/"

# Compilamos el juego
zcc +zx -lndos -create-app -zorg=40000 -o test test.c -lmalloc && zesarux --quickexit --nosplash --machine zxuno test.tap
rm test
#zcc +zxansi -lndos -create-app -zorg=24200 -o juego juego.c -lmalloc && zesarux --nowelcomemessage --quickexit --nosplash --machine zxuno juego.tap

