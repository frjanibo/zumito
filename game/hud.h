// void mallinfo(uint *total, uint *largest);
// total   = address of an integer where the total number of free bytes in the heap will be stored
// largest = address of an integer where the size of the largest available block in the heap will be stored

uint total, largest;
unsigned char str[16];

void updateHUD(){
        unsigned char outputString[16];

        mallinfo( &total, &largest );

        sprintf( outputString, "%05lu", score );
        mprint(outputString,0,90, 1, 6);
        
        sprintf( outputString, "%02u", lives  );
        print( outputString, 12, 90);

        sprintf( outputString, "%02u", ENEMIES_NUMBER );
        mprint(outputString,16,90, 1, 6);

        sprintf( outputString, "SPR %02u", adt_ListCount( Z_getSpritesList() ) );
        print( outputString, 24, 90);

        sprintf( outputString, "W %02u", CURRENT_WAVE );
        print( outputString, 36, 90);
        
        //sprintf( outputString, "M %05u", total );
        utoa( 123, str, 10);
        print( str, 46, 90);
        
        memcpy(RADAS_SCREEN_ADDR_1+(64*88),RADAS_SCREEN_ADDR_0+(64*88), 64*8);
        
        set_timeout( 500UL, updateHUD, NULL );
}
