#include <malloc.h>


#define RADAS_SCREEN_ADDR_0 ( ( unsigned int * ) 0x4000U )
#define RADAS_SCREEN_ADDR_1 ( ( unsigned int * ) 0x6000U )
#define RADAS_SIZE_X 128
#define RADAS_SIZE_Y 96
#define RADAS_BITS_SCREEN_WIDTH 6
#define RADAS_SIZE_X2 ( RADAS_SIZE_X >> 1 )
#define RADAS_SCREEN_NUM_BYTES 6144

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int prev_x;
    unsigned int prev_y;
    signed int speed_x;
    signed int speed_y;
    unsigned int *pixels;
    unsigned int blit[32];
    unsigned int shadow_blit[32];
    unsigned int *frames[4];
    unsigned int frame;
} Sprite;

Sprite* Sprite_new( unsigned char *pixels, unsigned char x, unsigned char y ){
  Sprite* s = malloc( sizeof(Sprite) );
  s->pixels = pixels;
  s->x = x;
  s->prev_x = x;
  s->y = y;
  s->prev_y = y;
  s->speed_x =0;
  s->speed_y =0;
  s->frame = 0;
  s->frames[0] = pixels;
  return s;
}

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int *pixels;
} Tile;

Tile* Tile_new( unsigned char *pixels, unsigned char x, unsigned char y ){
  Tile* t = malloc( sizeof(Tile) );
  t->pixels = pixels;
  t->x = x;
  t->y = y;
  return t;
}

void put_sprite_x8m (unsigned char *posicion, unsigned int x, unsigned int y)
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