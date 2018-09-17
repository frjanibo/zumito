#!/bin/bash
export Z88DK_PATH=/home/fjnieto/dev/personal/zx/z88dk

[[ ":$PATH:" != *":${Z88DK_PATH}/bin:"* ]] && PATH="${Z88DK_PATH}/bin:${PATH}"

export Z80_OZFILES=$Z88DK_PATH/bin
export ZCCCFG="${Z88DK_PATH}/lib/config"

export PNG2RADAS="../png2radas/png2radas.py"
export MAIN="trap.c"

#python /home/fjnieto/dev/personal/zx/uno/kit/png2radas/png2radas.py /home/fjnieto/dev/personal/zx/uno/kit/png2radas/set.png > /home/fjnieto/dev/personal/zx/uno/kit/zukit/lib/graphics.h
python $PNG2RADAS ../../trap/gfx/spriteset.png > game/graphics.h
python $PNG2RADAS --logo ../../trap/gfx/title.png > game/logo.h

python $PNG2RADAS ../../trap/gfx/tileset_0.png --tileset TILESET_Rocks > game/tileset_rocks.h
python $PNG2RADAS ../../trap/gfx/tileset_1.png --tileset TILESET_Spaceship > game/tileset_spaceship.h

python ../png2radas/maps.py ../../trap/tiled/screen1.json room_rocks > game/rooms.h

# Compilamos el juego
# zcc +zx -zorg=30720 -no-cleanup -z80-verb -v $MAIN --c-code-in-asm
zcc +zx -lndos -create-app -zorg=30720 -o trap $MAIN && zesarux --nowelcomemessage --quickexit --nosplash --machine zxuno trap.tap
#zcc +zx -lndos -create-app -zorg=40000 -o test array.c && zesarux --quickexit --nosplash --machine zxuno test.tap
#zcc +zxansi -lndos -create-app -zorg=24200 -o juego juego.c -lmalloc && zesarux --nowelcomemessage --quickexit --nosplash --machine zxuno juego.tap
