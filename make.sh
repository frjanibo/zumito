#!/bin/bash
Z88DK_PATH=~/dev/personal/zx/z88dk10
Z80_OZFILES=$Z88DK_PATH/bin
ZCCCFG="${Z88DK_PATH}/lib/config/"

# Compilamos el juego
zcc +zxansi -lndos -create-app -zorg=24200 -o test test.c -lmalloc && zesarux --quickexit --nosplash --machine 48k test.tap
rm test
#zcc +zxansi -lndos -create-app -zorg=24200 -o juego juego.c -lmalloc && zesarux --nowelcomemessage --quickexit --nosplash --machine zxuno juego.tap

