// motorzxuno.h

// Los bits del color de paleta van en forma GGGRRRBB
// Los pixels en cada byte van invertidos, el segundo es el primero (al ser los bits de menos peso)
// Es decir 22221111 es el formato de los bits de pixel en cada byte


// Current drawing screen. Initial value is 1 (the one which is not shown))
unsigned int iCurrentScreen = 1;
unsigned short screenAddress = RADAS_SCREEN_ADDR_1;
unsigned int *currentScreen = RADAS_SCREEN_ADDR_1;
unsigned int *theOtherScreen = RADAS_SCREEN_ADDR_0;

unsigned int *radasGetCurrentScreen() {
    return currentScreen;
}

unsigned int *radasGetTheOtherScreen() {
    return theOtherScreen;
}

unsigned int obtenerIndicePantalla() {
    return iCurrentScreen;
}

unsigned char getActiveScreenIndex(){
    return iCurrentScreen;
}

void radasChangeScreens() {

    if ( iCurrentScreen ) {
        port_out( 0x00FF, 1 );
        currentScreen = RADAS_SCREEN_ADDR_0;
        screenAddress = RADAS_SCREEN_ADDR_1;
        theOtherScreen = RADAS_SCREEN_ADDR_1;
        iCurrentScreen = 0;
    }
    else {
        port_out( 0x00FF, 0 );
        currentScreen = RADAS_SCREEN_ADDR_1;
        screenAddress = RADAS_SCREEN_ADDR_0;
        theOtherScreen = RADAS_SCREEN_ADDR_0;
        iCurrentScreen = 1;
    }

}



// Funciones:

// ___________________________________________
// Borra la pantalla a un color
// ___________________________________________

void cls (int color)
{
	#asm
		ld hl,2			;pasamos la variable de entrada al acumulador
		add hl,sp
		ld a, (hl)
		rla			;rotamos 4 bits a la izquierda
		rla
		rla
		rla			;ya tenemos el color del primer pixel
		add a, (hl)		;añadimos el color del segundo pixel

		ld c,a      ; me guardo A
        ld a, (_iCurrentScreen)  ; pillo el valor de la variable
        rra         ; veo si es 1
        jr c, cls_usa_screen_2
        ld hl, 16384
        ld de, 16385
        jp cls_continua

        cls_usa_screen_2:
        ld hl, 24576
        ld de, 24577

        cls_continua:
		ld a,c
		ld bc, RADAS_SCREEN_NUM_BYTES
		ld (hl), a
		ldir
	#endasm
}


// ___________________________________________
// Delay, produce una pausa en el programa
// ___________________________________________

void delay (int delay)
{
	#asm
	ld hl,2
	add hl,sp
	ld c, 0
	ld b, 2
	uno:
	ld e, (hl)	;operando base
	ld d, 0
	dos:
	dec de
	ld a,d
	or e
	jp nz,dos
	dec bc
	ld a,b
	or c
	jp nz,uno
	ret
	#endasm
}

// ___________________________________________
// Función para sacar un dato por un puerto
// ___________________________________________

void port_out (int port, int value)
{
	#asm
	ld hl,2
	add hl,sp
	ld a, (hl)
	inc hl
	inc hl
	ld c, (hl)
	inc hl
	ld b, (hl)
	out (c),a
	#endasm
}

// ___________________________________________
// Definir paleta de color
// ___________________________________________
void escribe_paleta (int indice, int color)
{
	// Los bits del color van en forma GGGRRRBB
	port_out (48955, indice);
	port_out (65339, color);
}


// ___________________________________________
// Función para leer un puerto
// ___________________________________________

int __FASTCALL__ port_in (int port)
{
	#asm
        	ld      b, h
        	ld      c, l
        	ld      h, 0
        	in      l, (c)
	#endasm
}


// ___________________________________________
// Espera interrupción y para la CPU
// ___________________________________________

void __FASTCALL__ wait_int (void)
{
	#asm
		halt
	#endasm
}

// ___________________________________________
// Dibuja un pixel a color
// ___________________________________________

void plot (unsigned char color, unsigned int x, unsigned int y)
{
	#asm
		ld hl,2		; Pasamos la variable de entrada al acumulador
		add hl,sp
		ld d, (hl)	; D es el valor Y
		inc hl
		inc hl
		ld e, (hl)	; E es el valor X
		rr e		; quitamos el valor de las unidades (los pixels van de dos en dos por byte)
		ld a,0
		jr c, next	; si es impar no hacemos nada (se dibuja por defecto a la derecha)
		ld a,1
		next:
		inc hl
		inc hl
		ld l, (hl)	; L es el color
		ld h,a

		ld a, d		; recuperamos el valor vertical
		rrca
	    rrca		; rotamos para dejar su valor en múltiplos de 64 (linea, de dos en dos pixels)
		and 192		; borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; borramos el resto de bits
		or 64		; nos posicionamos a partir de 16384 (16384=64+0 en dos bytes)
		ld d, a		; d preparado, ya tenemos la posición en pantalla

		ld a,(de)
		rr h
		jr c, next2
		and 240
		or l
		jr fin
		next2:
		and 15
		rl l
		rl l
		rl l
		rl l
		or l
		fin:
		ld (de), a		
	#endasm
}

// ___________________________________________
// Posiciona un Sprite de 10x10 a color
// ___________________________________________

void put_sprite_x10 (unsigned char *posicion, unsigned int x, unsigned int y)
{
	// -------------------------------------------
	// RUTINA DE IMPRESION DE UN SPRITE 10x10 PIXELS
	// EN CUALQUIER POSICION DE BYTES (cada byte dos pixels horizontales)
	// ENTRADAS:
	// D será la posición del cursor vertical en pixels
	// E será la posición del cursor horizontal en parejas de pixels
	// HL es la posición de memoria donde tenemos el sprite
	// SALIDAS: se escribe en el mapa de pantalla
	// ADVERTENCIAS: no comprueba límites de pantalla
	// -------------------------------------------
	#asm
		ld hl,2		; Pasamos la variable de entrada al acumulador
		add hl,sp
		ld d, (hl)	; D es el valor Y
		inc hl
		inc hl
		ld e, (hl)	; E es el valor X
		inc hl
		inc hl
		ld a, (hl)
	    	inc hl
	    	ld h, (hl)
	    	ld l, a		; HL es el puntero al sprite
	
		ld a, d		; recuperamos el valor vertical
		rrca
	        rrca		; rotamos para dejar su valor en múltiplos de 64 (linea, de dos en dos pixels)
		and 192		; borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; borramos el resto de bits
		or 64		; nos posicionamos a partir de 16384 (16384=64+0 en dos bytes)
		ld d, a		; d preparado, ya tenemos la posición en pantalla
	
		ld b,10		; Indicamos que vamos a pintar 10 líneas
		draw3:		; dibujamos 10 pixels (5 bytes)
		ld c,5		; Indicamos que vamos a pintar 5 pares de pixels
		ldi
		ldi
		ldi
		ldi
		ldi
		ld a,e
		add a,59	; incrementamos una línea y retornamos los pixels dibujados
		ld e,a
		jr nc, sigue3
		inc d		; incrementamos D si sale acarrero al incrementar E en 64 bytes
		sigue3:
		djnz draw3
	
		ret
	
	#endasm
}

// ___________________________________________
// Posiciona un Sprite de 8x8 a color con máscara
// ___________________________________________

void put_msprite_x8 (unsigned char *posicion, unsigned int x, unsigned int y)
{
	// -------------------------------------------
	// RUTINA DE IMPRESION DE UN SPRITE 8x8 PIXELS CON MÁSCARA (color 0 paleta)
	// EN CUALQUIER POSICION DE BYTES (cada byte dos pixels horizontales)
	// ENTRADAS:
	// D será la posición del cursor vertical en pixels
	// E será la posición del cursor horizontal en parejas de pixels
	// HL es la posición de memoria donde tenemos el sprite
	// SALIDAS: se escribe en el mapa de pantalla
	// ADVERTENCIAS: no comprueba límites de pantalla
	// -------------------------------------------
	unsigned int xx;
	unsigned int yy=8;
	unsigned char *pantalla=16384+x+y*64;
	unsigned int buffer;
	unsigned int dibuja;
	unsigned int a,b;

	while (yy>0)
	{
		xx=4;
		while (xx>0)
		{
			buffer=*posicion;
			a = (buffer&15); // 0F
			b = (buffer&240); // F0
			dibuja = 10*(a>0)+(b>0);
			switch(dibuja)
			{
				case 0: dibuja = *pantalla; break;
				case 1: dibuja = b+((*pantalla)&15); break;
				case 10: dibuja = a+((*pantalla)&240); break;
				case 11: dibuja = buffer; break;
			}
			*pantalla=dibuja;
			posicion++;
			pantalla++;
			xx--;
		}
		yy--;
		pantalla=pantalla+60;
	}
}

void put_msprite (unsigned char *posicion, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
	unsigned char *pantalla=16384+x+y*64;
	unsigned int buffer;
	unsigned int dibuja;
	unsigned int a,b;
	unsigned int xx;

	while (h>0)
	{
		xx= w/2;
		while (xx>0)
		{
			buffer=*posicion;
			a = (buffer&15);
			b = (buffer&240);
			dibuja = 10*(a>0)+(b>0);
			switch(dibuja)
			{
				case 0: dibuja = *pantalla; break;
				case 1: dibuja = b+((*pantalla)&15); break;
				case 10: dibuja = a+((*pantalla)&240); break;
				case 11: dibuja = buffer; break;
			}
			*pantalla=dibuja;
			posicion++;
			pantalla++;
			xx--;
		}
		h--;
		pantalla=pantalla+64- (w/2);
	}
}

