// ascii.h

extern unsigned char ascii [];

// ___________________________________________
// set de caracteres ASCII
// ___________________________________________

#asm
	._ascii
	DEFB	0, 0; ESPACIO
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 240; CIERRE ADMIRACION
	DEFB	0, 240
	DEFB	0, 240
	DEFB	0, 0
	DEFB	0, 240
	DEFB	0, 0
	DEFB	240, 240; COMILLAS
	DEFB	240, 240
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	15, 0; ASPERSAN
	DEFB	255, 240
	DEFB	15, 0
	DEFB	255, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	15, 240; DOLAR
	DEFB	255, 0
	DEFB	15, 240
	DEFB	255, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	240, 240; PORCENTAJE
	DEFB	0, 240
	DEFB	15, 0
	DEFB	240, 0
	DEFB	240, 240
	DEFB	0, 0
	DEFB	15, 0; AND
	DEFB	240, 240
	DEFB	15, 0
	DEFB	240, 240
	DEFB	255, 0
	DEFB	0, 0
	DEFB	15, 0; COMILLA SIMPLE
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 240; ABRE PARENTESIS
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 240
	DEFB	0, 0
	DEFB	15, 0; CIERRA PARENTESIS
	DEFB	0, 240
	DEFB	0, 240
	DEFB	0, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	15, 0; ASTERISCO
	DEFB	255, 240
	DEFB	15, 0
	DEFB	255, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0; MAS
	DEFB	15, 0
	DEFB	255, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0; COMA
	DEFB	0, 0
	DEFB	0, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0; MENOS
	DEFB	0, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0; PUNTO
	DEFB	0, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 240; BARRA
	DEFB	0, 240
	DEFB	15, 0
	DEFB	240, 0
	DEFB	240, 0
	DEFB	0, 0
	DEFB	255, 240; 0
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	0, 240; 1
	DEFB	15, 240
	DEFB	0, 240
	DEFB	0, 240
	DEFB	0, 240
	DEFB	0, 0
	DEFB	255, 240; 2
	DEFB	0, 240
	DEFB	255, 240
	DEFB	240, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; 3
	DEFB	0, 240
	DEFB	255, 240
	DEFB	0, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	240, 240; 4
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 240
	DEFB	0, 240
	DEFB	0, 0
	DEFB	255, 240; 5
	DEFB	240, 0
	DEFB	255, 240
	DEFB	0, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; 6
	DEFB	240, 0
	DEFB	255, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; 7
	DEFB	0, 240
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	255, 240; 8
	DEFB	240, 240
	DEFB	255, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; 9
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	0, 0; DOS PUNTO
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0; PUNTO Y COMA
	DEFB	15, 0
	DEFB	0, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	0, 0; MENOR
	DEFB	0, 0
	DEFB	0, 240
	DEFB	15, 0
	DEFB	0, 240
	DEFB	0, 0
	DEFB	0, 0; IGUAL
	DEFB	0, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	0, 0; MAYOR
	DEFB	0, 0
	DEFB	15, 0
	DEFB	0, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	15, 0; INTERROGANTE
	DEFB	240, 240
	DEFB	0, 240
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	15, 0; ARROBA
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 0
	DEFB	15, 240
	DEFB	0, 0
	DEFB	255, 240; A
	DEFB	240, 240
	DEFB	255, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	255, 0; B
	DEFB	240, 240
	DEFB	255, 0
	DEFB	240, 240
	DEFB	255, 0
	DEFB	0, 0
	DEFB	15, 240; C
	DEFB	240, 0
	DEFB	240, 0
	DEFB	240, 0
	DEFB	15, 240
	DEFB	0, 0
	DEFB	255, 0; D
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 0
	DEFB	0, 0
	DEFB	255, 240; E
	DEFB	240, 0
	DEFB	255, 240
	DEFB	240, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; F
	DEFB	240, 0
	DEFB	255, 240
	DEFB	240, 0
	DEFB	240, 0
	DEFB	0, 0
	DEFB	15, 240; G
	DEFB	240, 0
	DEFB	240, 240
	DEFB	240, 240
	DEFB	15, 240
	DEFB	0, 0
	DEFB	240, 240; H
	DEFB	240, 240
	DEFB	255, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	255, 240; I
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	0, 240; J
	DEFB	0, 240
	DEFB	0, 240
	DEFB	240, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	240, 240; K
	DEFB	240, 240
	DEFB	255, 0
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	240, 0; L
	DEFB	240, 0
	DEFB	240, 0
	DEFB	240, 0
	DEFB	255, 240
	DEFB	0, 0
	DEFB	240, 240; M
	DEFB	255, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	240, 240; N
	DEFB	255, 240
	DEFB	255, 240
	DEFB	255, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	255, 240; O
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	255, 240; P
	DEFB	240, 240
	DEFB	255, 240
	DEFB	240, 0
	DEFB	240, 0
	DEFB	0, 0
	DEFB	255, 240; Q
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 0
	DEFB	15, 240
	DEFB	0, 0
	DEFB	255, 240; R
	DEFB	240, 240
	DEFB	255, 0
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	15, 240; S
	DEFB	240, 0
	DEFB	15, 0
	DEFB	0, 240
	DEFB	255, 0
	DEFB	0, 0
	DEFB	255, 240; T
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	240, 240; U
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	0, 0
	DEFB	240, 240; V
	DEFB	240, 240
	DEFB	240, 240
	DEFB	240, 240
	DEFB	15, 0
	DEFB	0, 0
	DEFB	240, 240; W
	DEFB	240, 240
	DEFB	240, 240
	DEFB	255, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	240, 240; X
	DEFB	240, 240
	DEFB	15, 0
	DEFB	240, 240
	DEFB	240, 240
	DEFB	0, 0
	DEFB	240, 240; Y
	DEFB	240, 240
	DEFB	15, 0
	DEFB	15, 0
	DEFB	15, 0
	DEFB	0, 0
	DEFB	255, 240; Z
	DEFB	0, 240
	DEFB	15, 0
	DEFB	240, 0
	DEFB	255, 240
	DEFB	0, 0

#endasm

// ___________________________________________
// Posiciona una letra a color
// ___________________________________________

void put_letra (unsigned char *posicion, unsigned int x, unsigned int y)
{
	// -------------------------------------------
	// RUTINA DE IMPRESION DE UNA LETRA DE 4x6 PIXELS
	// EN CUALQUIER POSICION DE BYTES (cada byte dos pixels horizontales)
	// ENTRADAS:
	// D ser� la posici�n del cursor vertical en pixels
	// E ser� la posici�n del cursor horizontal en parejas de pixels
	// HL es la posici�n de memoria donde tenemos el sprite
	// SALIDAS: se escribe en el mapa de pantalla
	// ADVERTENCIAS: no comprueba l�mites de pantalla
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
	        rrca		; rotamos para dejar su valor en m�ltiplos de 64 (linea, de dos en dos pixels)
		and 192		; borramos el resto de bits por si las moscas
		or e		; sumamos el valor horizontal
		ld e, a		; e preparado
		ld a, d		; cargamos el valor vertical
		rrca
		rrca		; rotamos para quedarnos con los bits altos
		and 63		; borramos el resto de bits
		or 64		; nos posicionamos a partir de 16384 (16384=64+0 en dos bytes)
		ld d, a		; d preparado, ya tenemos la posici�n en pantalla

		ld b,6		; Indicamos que vamos a pintar 6 l�neas
		.draw2		; dibujamos 4 pixels (2 bytes)
		ld c,2		; Indicamos que vamos a pintar 2 pares de pixels
		ldi
		ldi
		ld a,e
		add a,62	; incrementamos una l�nea y retornamos los pixels dibujados
		ld e,a
		jr nc, sigue2
		inc d		; incrementamos D si sale acarrero al incrementar E en 64 bytes
		.sigue2
		djnz draw2

		ret

	#endasm
}

// ___________________________________________
// Posiciona una letra a color con fondo transparente
// ___________________________________________

void put_mletra (unsigned char *posicion, unsigned int x, unsigned int y)
{
	unsigned int xx;
	unsigned int yy=6;
	unsigned char *pantalla=16384+x+y*64;
	unsigned int buffer;
	unsigned int dibuja;
	unsigned int a,b;

	while (yy>0)
	{
		xx=2;
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
		yy--;
		pantalla=pantalla+62;
	}
}

// ___________________________________________
// Escribe un texto
// Detecta si se excede la pantalla
// ___________________________________________

void print (char *texto, char x, char y)
{
  char *InicioFuente = ascii - (int)(32*12);// - 32*12; /* de esta forma, InicioFuente apunta 32 caracteres antes del espacio */
  char *InicioSprite;

  while (*texto)
  {
    InicioSprite = (*texto)*12+InicioFuente;
    put_letra (InicioSprite,x, y);
    x+=2; /* siguiente posici�n de car�cter */
    if (x>=63)
    {
      y+=6;
      x = 0;
    }
    texto++;
  }
}

// ___________________________________________
// Escribe un texto con m�scara (color 0)
// Detecta si se excede la pantalla
// ___________________________________________

void mprint (char *texto, char x, char y)
{
  char *InicioFuente = ascii - (int)(32*12);// - 32*12;
  /* de esta forma, InicioFuente apunta 32 caracteres antes del espacio */
  char *InicioSprite;

  while (*texto)
  {
    InicioSprite = (*texto)*12+InicioFuente;
    put_mletra (InicioSprite,x, y);
    x+=2;
    // siguiente posición de carácter
    if (x>=63) {
      y+=6;
      x = 0;
    }
    texto++;
  }

}

