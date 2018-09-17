
void __FASTCALL__ Z_InitEngine() {
        Z_SpritesList = adt_ListCreate();
        init_timeout_system();
}



struct adt_List* Z_getSpritesList(){
        return Z_SpritesList;
}

void __FASTCALL__ Z_Render() {
  check_timeouts();
  
  sprites_store(); // copy working screen background into each sprite blit
  sprites_draw(); // draw sprites on working screen
  Z_switchScreen(); // switch working and visible screens
  sprites_restore(); // restore blits into working screen
  sprites_destroy(); // destroy old sprites
}

void __FASTCALL__ wait_int (void)
{
	#asm
		halt
	#endasm
}

#define VAR_FRAMES ((unsigned int *)23672)

unsigned int ZX_Uno_t = 0UL;
unsigned int __FASTCALL__ millis() {
        // Note: this is a not exact simplification
        // Should be ticks(50 Hz) * 20 ms = 1000 ms,
        // But it is simplified to ticks(50 Hz) * 16 = 800 ms
        // 50 Hz * 16 = 800 ~ 1000 ms / s
        ZX_Uno_t = *VAR_FRAMES;
        return ZX_Uno_t << 4;
}


void __FASTCALL__ Z_setPalette( unsigned char *pal ) {
        unsigned char i=0;
        for(i=0; i<16; i++) {
                outp(0xBF3B, i);
                outp(0xFF3B, *(pal+i) );
        }
}

void Z_setPaletteOffset( unsigned char* pal, unsigned char offset ) {
  while(offset<16) {
		offset++;
        outp(0xBF3B, offset);
        outp(0xFF3B, *(pal+offset) );
  }
}

void Z_exchangePaletteColors( unsigned char* pal, unsigned char a, unsigned char b ) {
  unsigned char a_value, b_value;
  outp(0xBF3B, a);
  a_value = inp(0xFF3B);
  outp(0xBF3B, b);
  b_value = inp(0xFF3B);
  // xor trick
  a_value^=b_value;
  b_value^=a_value;
  a_value^=b_value;
  outp(0xBF3B, a);
  outp(0xFF3B, a_value);
  outp(0xBF3B, b);
  outp(0xFF3B, b_value);
}

unsigned char Z_paletteFadeout(){
  unsigned char i, r,g,b, ret=0;
  do {
    ret=0;
    for(i=0; i<16; i++) {
      outp(0xBF3B, i);
      b = inp(0xFF3B);
      r = (b & 0x1C) >> 2; // 00011100
      g = (b & 0xE0) >> 5; // 11100000
      b = b & 0x03;        // 00000011
      if(r>0) r--;
      if(g>0) g--;
      if(b>0) b--;

      outp(0xFF3B, (r<<2) | (g<<5) |b);
      ret|= (r<<2) | (g<<5) | b;
      
    }
    wait_int();
  } while(ret>0);
}

void __FASTCALL__ Z_turboOn(){
        outp(64571,11);
        outp( 64827, inp(64827) ^ 128 );
}

void __FASTCALL__ Z_radastanModeOn() {
        outp(64571,64);
        outp(64827, 3);
        // rehabilitar modos timex para shadow screen
        outp(64571,15);
        outp(64827,0);
}

void __FASTCALL__ Z_setActiveScreen( unsigned char i ) {
        iCurrentScreen = i;
}
void __FASTCALL__ Z_getActiveScreen() {
        return iCurrentScreen;
}

unsigned int __FASTCALL__ *Z_getWorkingScreenAddress() {
  if(iCurrentScreen == 1) {
	return RADAS_SCREEN_ADDR_1;
  } else {
	return RADAS_SCREEN_ADDR_0;
  }
}

unsigned int __FASTCALL__ *Z_getVisibleScreenAddress() {
  if( iCurrentScreen == 1) return RADAS_SCREEN_ADDR_0;
  else return RADAS_SCREEN_ADDR_1;
}

void __FASTCALL__ Z_switchScreen() {
        outp( 0x00FF, iCurrentScreen );
        iCurrentScreen = !iCurrentScreen;
}

void Z_copyScreenToShadow(){
  memcopy(Z_getWorkingScreenAddress(), Z_getVisibleScreenAddress(),  RADAS_SCREEN_NUM_BYTES);
}

void Z_put_sprite (unsigned char *posicion, unsigned char x, unsigned char y, unsigned char w, unsigned char h)
{
	unsigned char *pantalla=Z_getWorkingScreenAddress() + (x>>1)+ (y*64);
	unsigned int xx;

	while (h>0)
	{
		xx= w>>1;
		while (xx>0)
		{
			*pantalla= *posicion;
			posicion++;
			pantalla++;
			xx--;
		}
		h--;
		pantalla=pantalla+64- (w>>1);
	}
}


void Z_put_msprite (unsigned char *posicion, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
	unsigned char *pantalla=((Z_getActiveScreen()?RADAS_SCREEN_ADDR_1:RADAS_SCREEN_ADDR_0) + (y*32) );
	unsigned int buffer;
	unsigned int dibuja;
	unsigned int a,b;
	unsigned int xx;


  pantalla+= (x>>1);

	while (h>0)
	{
		xx= w>>1;
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
		pantalla=pantalla+64- (w>>1);
	}
}

void put_sprite_x8 (unsigned char *posicion, unsigned char x, unsigned char y)
{
        // -------------------------------------------
        // RUTINA DE IMPRESION DE UN SPRITE 8x8 PIXELS
        // EN CUALQUIER POSICION DE PIXELS
        // ENTRADAS:
        // D será la posición del cursor vertical en pixels
        // E será la posición del cursor horizontal en pixels
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

        ld a, e
        ex af,af
	    srl e       ; dividimos E entre 2 (son 2 nibbles por byte)

		ld a, d		; recuperamos el valor vertical
		rrca
	    rrca		; rotamos para dejar su valor en múltiplos de 64 (linea, de dos en dos pixels)
		and 192		; 11000000 borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; 00111111 borramos el resto de bits

		ld c,a      ; me guardo A
		ld a, (_iCurrentScreen)  ; pillo el valor de la variable
		rra         ; veo si es 1
		jr c, usa_screen_2

		ld a,c      ; restauro A
		or 0x40     ; a partir de 16384
		jp continua
		usa_screen_2:
		ld a,c
		or 0x60		; 01100000 nos posicionamos a partir de 24576 (16384=96+0 en dos bytes)
		continua:

		ld d, a		; d preparado, ya tenemos la posición en pantalla en DE

		ex af,af
		and 1
		jr z, dibujar_linea_par
        ld bc, 0x0408 ; 4 bytes por linea (8 pixeles), 8 lineas

    bucle_lineas:
        ld a, (de)  ; cargo en A el primer byte de la pantalla
        and 0xF0    ; me interesa quedarme solo con el 1er nibble
        push bc     ; me guardo bc, que la rutina lo corrompe
        jr dibujar_linea_impar_v2
        vuelve_de_linea_impar_v2:
        ld a, 60    ; añadimos 60 para escribir en la siguiente línea
        add a,e
        ld e,a
        adc a,d
        sub e
        ld d,a

        pop bc
        dec c
        jr nz, bucle_lineas
        ret

    dibujar_linea_impar_v2:
        ld c,(hl)   ; me guardo el contenido de HL pues rld lo modifica
        rld         ; T18 si A=ab y (HL)=12, después A=a1 y (HL)=2b
        ld (de),a   ; escribimos a pantalla
        inc de      ; nos movemos a la siguiente posicion de pantalla
        ld a,(hl)   ; cargamos el byte del sprite otra vez (ya está rotado a la izq por rld)
        ld (hl),c   ; restauramos el contenido de (hl)

        inc hl      ; nos movemos al siguiente byte del sprite
        djnz dibujar_linea_impar_v2 ; decrementamos el num de nibbles por linea

        ld a,(de)   ; en A tenemos lo que hay en pantalla
        dec hl      ; el último nibble de la línea, hay que volver atras a por él

        ld c,(hl)
        rld         ; T18 si A=ab y (HL)=12, después A=a1 y (HL)=2b
        ld a,(hl)   ; nos interesa el 2b
        ld (hl),c   ; restauramos hl para no corromper el sprite

        ld (de),a   ; y escribimos a pantalla
        inc hl
        jr vuelve_de_linea_impar_v2

	dibujar_linea_par:
		ld b,8		; Indicamos que vamos a pintar 8 líneas
	draw:		    ; dibujamos 8 pixels (4 bytes)
		ld c,4		; Indicamos que vamos a pintar 4 pares de pixels
		ldi
		ldi
		ldi
		ldi

        ld a, 60    ; añadimos 60 para escribir en la siguiente línea
        add a,e
        ld e,a
        adc a,d
        sub e
        ld d,a

		djnz draw
		ret
	coord_x:
	    defb 0
  #endasm
}

void put_sprite_x8m (unsigned char *posicion, unsigned char x, unsigned char y)
{
        // -------------------------------------------
        // RUTINA DE IMPRESION DE UN SPRITE 8x8 PIXELS
        // EN CUALQUIER POSICION DE PIXELS
        // ENTRADAS:
        // D será la posición del cursor vertical en pixels
        // E será la posición del cursor horizontal en pixels
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

        ld a, e
        ex af,af
	    srl e       ; dividimos E entre 2 (son 2 nibbles por byte)

		ld a, d		; recuperamos el valor vertical
		rrca
	    rrca		; rotamos para dejar su valor en múltiplos de 64 (linea, de dos en dos pixels)
		and 192		; 11000000 borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; 00111111 borramos el resto de bits

		ld c,a      ; me guardo A
		ld a, (_iCurrentScreen)  ; pillo el valor de la variable
		rra         ; veo si es 1
		jr c, m_usa_screen_2

		ld a,c      ; restauro A
		or 0x40     ; a partir de 16384
		jp m_continua
    m_usa_screen_2:
		ld a,c
		or 0x60		; 01100000 nos posicionamos a partir de 24576 (16384=96+0 en dos bytes)
    m_continua:

		ld d, a		; d preparado, ya tenemos la posición en pantalla en DE

		ex af,af
		and 1
		jr z, m_dibujar_linea_par
        ld bc, 0x0408 ; 4 bytes por linea (8 pixeles), 8 lineas

    m_bucle_lineas:
        ld a, (de)  ; cargo en A el primer byte de la pantalla
        and 0xF0    ; me interesa quedarme solo con el 1er nibble
        push bc     ; me guardo bc, que la rutina lo corrompe
        jr m_dibujar_linea_impar_v2
    m_vuelve_de_linea_impar_v2:
        ld a, 60    ; añadimos 60 para escribir en la siguiente línea
        add a,e
        ld e,a
        adc a,d
        sub e
        ld d,a

        pop bc
        dec c
        jr nz, m_bucle_lineas
        ret

    m_dibujar_linea_impar_v2:
        ld c,(hl)   ; me guardo el contenido de HL (sprite) pues rld lo modifica
        rld         ; T18 si A=ab y (HL)=12, después A=a1 y (HL)=2b
        push bc
        call m_draw_generic
        pop bc
        inc de      ; nos movemos a la siguiente posicion de pantalla
        ld a,(hl)   ; cargamos el byte del sprite otra vez (ya está rotado a la izq por rld)
        ld (hl),c   ; restauramos el contenido de (hl)

        inc hl      ; nos movemos al siguiente byte del sprite
        djnz m_dibujar_linea_impar_v2 ; decrementamos el num de nibbles por linea

        ld a,(de)   ; en A tenemos lo que hay en pantalla
        dec hl      ; el último nibble de la línea, hay que volver atras a por él

        ld c,(hl)
        rld         ; T18 si A=ab y (HL)=12, después A=a1 y (HL)=2b
        ld a,(hl)   ; nos interesa el 2b
        ld (hl),c   ; restauramos hl para no corromper el sprite

        push bc
        call m_draw_generic
        pop bc
        inc hl
        jr m_vuelve_de_linea_impar_v2

    // DIBUJAR LINEA PAR ______________________________________________
    m_dibujar_linea_par:
		ld b,8		; Indicamos que vamos a pintar 8 líneas
	m_linea_par_start:
		ld c, 4     ; 4 bytes
	m_draw:		    ; dibujamos 8 pixels (4 bytes)
	    push bc
	    ld a,(hl)
	    call m_draw_generic

    m_siguiente_byte:
        pop bc
        inc de
        inc hl
        dec c
        jr nz, m_draw

    m_siguiente_linea:
		ld a, 60    ; añadimos 60 para escribir en la siguiente línea
        add a,e
        ld e,a
        adc a,d
        sub e
        ld d,a

		djnz m_linea_par_start
		ret
	nibble_a:
    	    defb 0
    nibble_b:
            defb 0
    backup:
            defb 0

    m_draw_generic:		    ; dibujamos A en DE (corrompe C)
        ld c,a
        and 0x0F
        ld b,a      ; B= nibble b (a;b)
        ld a,c
        and 0xF0
        ld c,a      ; C= nibble a (a;b)

        cp 1        ; tenemos cargado en A el nibble a
        jr c, m_draw_check_nibble_b_impar      ; si A=0
        ld a,0x0F   ; significa que el primer nibble a es != 0
        ex de,hl
        and (hl)    ; borramos de pantalla el nibble a (a;b)
        or c      ; cargamos el nibble a del sprite
        ex de,hl
        ld (de),a

    m_draw_check_nibble_b_impar:
        ld a,b
        cp 1
        jr c, m_draw_ret
        ld a, 0xF0
        ex de,hl
        and (hl)    ; borramos de pantalla el nibble b (a;b)
        or b
        ex de,hl
        ld (de),a
    m_draw_ret:
        ret

  #endasm
}

void put_sprite_x8_even (unsigned char *posicion, unsigned char x, unsigned char y)
{
        // -------------------------------------------
        // RUTINA DE IMPRESION DE UN SPRITE 8x8 PIXELS
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

		ld c,a      ; me guardo A
        ld a, (_iCurrentScreen)  ; pillo el valor de la variable
        rra         ; veo si es 1
        jr c, usa_screen_2_fast

        ld a,c      ; restauro A
        or 0x40     ; a partir de 16384
        jp continua_fast
       usa_screen_2_fast:
        ld a,c
        or 0x60		; 01100000 nos posicionamos a partir de 24576 (16384=96+0 en dos bytes)
       continua_fast:

		ld d, a		; d preparado, ya tenemos la posición en pantalla

		ld b,8		; Indicamos que vamos a pintar 8 líneas
	draw_fast:		; dibujamos 8 pixels (4 bytes)
		ld c,4		; Indicamos que vamos a pintar 4 pares de pixels
		ldi
		ldi
		ldi
		ldi
		ld a,e
		add a,60	; incrementamos una línea y retornamos los pixels dibujados
		ld e,a
		jr nc, sigue_fast
		inc d		; incrementamos D si sale acarrero al incrementar E en 64 bytes
	sigue_fast:
		djnz draw_fast
		ret
  #endasm
}

void get_sprite_x8 (unsigned char *posicion, unsigned char x, unsigned char y)
{
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

	    ld a,e
	    ex af,af     ; me guardo la X para comprobar después si es par/impar
	    srl e       ; dividimos E entre 2 (son 2 nibbles por byte)

		ld a, d		; recuperamos el valor vertical
		rrca
	    rrca		; rotamos para dejar su valor en múltiplos de 64 (linea, de dos en dos pixels)
		and 192		; 11000000 borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; 00111111 borramos el resto de bits

        ld c,a      ; me guardo A
		ld a, (_iCurrentScreen)  ; pillo el valor de la variable
		rra         ; veo si es 1
		jr c, get_usa_screen_2

		ld a,c      ; restauro A
		or 0x40     ; a partir de 16384
		jp get_continua
		get_usa_screen_2:
		ld a,c
		or 0x60		; 01100000 nos posicionamos a partir de 24576 (16384=96+0 en dos bytes)
		get_continua:

		ld d, a		; d preparado, ya tenemos la posición en pantalla en DE

        ex af,af      ; recuperamos la X
		and 1       ; es par/impar?
		jr z, get_par

        ld b, 4     ; 4 bytes por linea (8 pixeles)
        ld c, 8     ; 8 lineas
        ex de,hl    ; intercambio la pantalla y el area de blit

    bucle_lineas_get:
        push bc     ; me guardo bc, que la rutina lo corrompe
        jp get_linea_impar
        vuelve_de_linea_impar:
        ld bc, 60   ; añadimos 60 para escribir en la siguiente línea
        add hl, bc
        pop bc
        dec c
        jr nz, bucle_lineas_get
        ret

    get_linea_impar:
        ; hl -> pantalla
        ; de -> blit
        ld a,(hl)   ; leo el byte de la pantalla
        rlca
        rlca
        rlca
        rlca
        and 0xF0    ; lo rotamos 4 veces a la izq y le borramos el nibble de la derecha
        inc hl      ; siguiente byte de pantalla
        ex af,af     ; me guardo A
        ld a,(hl)   ; cargo el byte de pantalla en A
        rrca
        rrca
        rrca
        rrca
        and 0x0F    ; rotar 4 a la derecha y borrar el nible de la izq
        ld c,a      ; lo pongo en C
        ex af,af      ; recupero A
        or c        ; y mezclo C y A (nible der y izq)
        ld (de),a
        inc de
        djnz get_linea_impar
        jp vuelve_de_linea_impar

	get_par:
		ld b,8		; Indicamos que vamos a pintar 8 líneas
		; pantalla en DE, blit en HL
		ex de,hl
		; pantalla en HL, blit en DE
	leer:		    ; dibujamos 8 pixels (4 bytes)
		ld c,4		; Indicamos que vamos a pintar 4 pares de pixels
		ldi
		ldi
		ldi
		ldi
		push bc
		ld bc,60
		add hl,bc
		pop bc
		djnz leer
		ret

  #endasm
}


void fastcls (int color)
{
  #asm
		ld hl,2			;pasamos la variable de entrada al acumulador
		add hl,sp
		ld a, (hl)
		rla			;rotamos 4 bits a la izquierda
		rla
		rla
		rla			;ya tenemos el color del primer pixel
		add a, (hl)	;añadimos el color del segundo pixel

		ld c,a      ; me guardo A
        ld a, (_iCurrentScreen)  ; pillo el valor de la variable
        rra         ; veo si es 1
        jr c, fc_cls_usa_screen_2
        ld hl, 16384 + RADAS_SCREEN_NUM_BYTES
        jp fc_cls_continua

       fc_cls_usa_screen_2:
        ld hl, 24576 + RADAS_SCREEN_NUM_BYTES

       fc_cls_continua:
        di
        ld (stack_restore + 1), sp  ;sobreescribimos el valor de SP en stack_restore
        ld sp, hl   ; apunto la pila al final de la pantalla
        ld h, c    ; en hl me guardo el color
        ld l, c

        ld b, 0 ; pongo b=0, hace que el bucle se repita 256 veces. 256*24 bytes = 6144
       fc_loop:
        push hl
        push hl
        push hl
        push hl

        push hl
        push hl
        push hl
        push hl

        push hl
        push hl
        push hl
        push hl
        djnz fc_loop
	   stack_restore:
		ld sp, 0 ; el 0 será sobreescrito
		ei
  #endasm
}

void memcopy( uchar* destiny, uchar* origin, unsigned int size) {
	while(size-- > 0) {
		*(destiny+size) = *(origin+size);
	}
}

char* itoa_10(unsigned int num, unsigned char* str, unsigned char digits)
{
    int i = 0;
 
	for(i=0;i<digits; i++) str[i]='0';
	str[i]='\0';
	
    if (num == 0) return str;
  
    // Process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[--i] = rem + '0';
        num = num/10;
    }
	return str;
}


