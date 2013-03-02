// EEExplorer
//
//  simple shell-like tool for formatting/reading/writing contents of EEProm
// 
//  Scott Lawrence - yorgle@gmail.com
//
//  2013-Mar-01  v002  Added Poke, smarter Print
//  2013-Feb-18  v001  Initial basic version


#include <EEPROM.h>

// kLED - the pin that the indicator LED is connected to.
#define kLED 13

// setup
//   set up our ports and Serial IO
void setup()
{
  pinMode( kLED, OUTPUT );
  
  digitalWrite( kLED, LOW );
  Serial.begin( 9600 );
  while( !Serial ); // Leonardo
  Serial.flush();
   
  digitalWrite( kLED, HIGH );
}


// serialAbout
//   displays information about EEExplorer and help/commands
void serialAbout( void )
{
  Serial.println( "" );
  Serial.println( "EEExplorer v002  Scott Lawrence  yorgle@gmail.com" );
  Serial.println( "" );
  Serial.print( " Flash size: " ); Serial.print( (unsigned) FLASHEND +1 ); Serial.println( " bytes" );
  Serial.print( "   RAM size: " ); Serial.print( RAMEND +1 ); Serial.println( " bytes" );
  Serial.print( "EEProm size: " ); Serial.print( E2END +1 ); Serial.println( " bytes" );
  Serial.println( " " );
  Serial.println( "Commands:" );
  Serial.println( " format    clear the EEProm" );
  Serial.println( " dump      hex dump of the EEProm" );
  Serial.println( " print     text dump of the EEProm" );
  Serial.println( " record    erase EEProm until '.', buffer fill or reset" );
  Serial.println( " poke A D  poke value D into address a (decimal values)" );
}


// getSerialLine
//   gets a line (terminated by \n newline) from the serial port
//   stores it in the buffer pointed to by "buf"
//   "buf" is a maximum of "maxbuf" bytes
//   if echoback is true, it will also print stuff out as it gets it
void getSerialLine( char * buf, int maxbuf, boolean echoback )
{
  int chp = 0;
  
  // read a line or so into our buffer
  do {
    buf[chp] = Serial.read();
    if( echoback ) Serial.write( buf[chp]);   
    chp++;
  } while(    Serial.available() 
           && buf[chp-1] != '\n'
           && chp < maxbuf );
  
  // terminate the buffer
  buf[chp] = '\0';
  
  // strip newline
  if( chp > 0 && buf[ chp-1 ] == '\n' ) buf[chp-1] = '\0';
  
  if( echoback ) Serial.println( "" );
}


// formatEE
//   formats the EEprom
//   writes 0x00 to all bytes
void formatEE( void )
{
  Serial.print( "Formatting EEPROM..." );
  for( int i=0 ; i<=E2END ; i++ )
  {
    EEPROM.write( i, 0x00 );
    digitalWrite( kLED, i & 0x020 );
  }
  Serial.println( "...DONE!" );
}


// hexdump
//   hexdump to serial the first 16 bytes passed in
//   helper function for dumpEE below
void hexdump( unsigned char *buf ) /* implied 16 byte buffer */
{
  int i;
  char s[16];
  
  // A.  hex bytes
  for( i=0 ; i<16 ; i++ ) {
     sprintf( s, "%02x ", buf[i] & 0x0ff );
     Serial.print( s );
     if( i==7 ) Serial.print( " " );
   }
   
   Serial.print( "  " );
   
   s[1] = '\0';
   
   for( i=0 ; i<16 ; i++ ) {
     if( buf[i] >=0x20 && buf[i] <= 0x7e ) {
       s[0] = buf[i];
       Serial.print( s );
     } else {
       Serial.print( "." );
     }
     if( i==7 ) Serial.print( " " );
   }
}


// dumpEE
//   Do a hex dump of the entire EEProm
void dumpEE( void )
{
  long offset = 0;
  char buf2[16];
  unsigned char buf[32];
  
  Serial.println( "       0  1  2  3  4  5  6  7   8  9  A  B  C  D  E  F" );
  
  for( offset = 0 ; offset < E2END ; offset += 16 )
  {
    sprintf( buf2, "%04x   ", offset );
    Serial.print( buf2 );
    
    
    for( int b=0 ; b<16 ; b++ )
    {
      buf[b] = EEPROM.read( offset + b );
    }
    
    hexdump( buf );
    Serial.println( "" );
  }
  
  Serial.print( E2END + 1 );
  Serial.println( " bytes." );
}


// printEE
//   print out the contents, as-is, printable or not
//   ends when it hits a null or the end of data
void printEE( void )
{
  char buf[3];
  buf[0] = 'X';
  buf[1] = '\0';
  
  Serial.println( "------------------" );
  for( int i=0 ; (i<=E2END) && (buf[0] != '\0') ; i++ )
  {
    buf[0] = EEPROM.read( i );
    
    if( buf[0] == '\0' ) continue;
    
    if( buf[0] ) Serial.print( buf );
  }
  Serial.println( "------------------" );
}


#define kLineBuf 80
char linebuf[ kLineBuf ];

// recordEE 
//   take input and store it right into the EEProm
//   end when we get a line with just a "."
//   will also end if the user hits the reset button on the device
void recordEE( void )
{  
  digitalWrite( kLED, HIGH );
  
  Serial.println( "Recording lines of text to EEProm." );
  Serial.println( "End with '.' starting a line.");
  
  int nbytes = 0;
  boolean done = false;
  do {
    while( !Serial.available() );
    delay( 100 );
    getSerialLine( linebuf, kLineBuf, true );
    
    if( linebuf[0] == '.' ) 
    {
      done = true;
      continue;
    }
    
    //Serial.print( "<." );
    for( int c=0 ; c<kLineBuf && linebuf[c] != '\0' && nbytes < E2END; c++ )
    {
      EEPROM.write( nbytes++, linebuf[c] );
    }
    EEPROM.write( nbytes++, '\n' );
    //Serial.println( ".>" );
    
    if( nbytes >= E2END ) {
      Serial.println( "EEProm space overflow." );
      done = true;
    }
  } while( !done );
  
  Serial.flush();
  
  Serial.print( nbytes, DEC );
  Serial.println( " recorded to EEPROM." );  
}

void pokeEE( char * buf )
{
  char * addrstr = buf;
  while( *buf != '\0' && *buf != ' ' ) buf++;
  *buf = '\0';
  buf++;
  char * datastr = buf;
  
  if( addrstr[0] == '\0' || datastr[0] == '\0' )
  {
    Serial.println( "Specify address and data." );
    return;
  }
  
  int addr = atoi( addrstr );
  int data = atoi( datastr );
  
  Serial.print( "Poking data (" );
  Serial.print( data, DEC );
  Serial.print( ") into address (0x" );
  Serial.print( addr, HEX );
  Serial.println( ")." );
  
  EEPROM.write( addr, data );  
}

void handleSerial()
{
  int chp = 0;
  
  // wait 0.1 seconds to make sure we get a full line
  delay( 100 );

  // read a line in  
  getSerialLine( linebuf, kLineBuf, true );
  
  // command valve
  if(      !strcmp( linebuf, "?" ))        serialAbout();
  else if( !strcmp( linebuf, "format" ))   formatEE();
  else if( !strcmp( linebuf, "dump" ))     dumpEE();
  else if( !strcmp( linebuf, "print" ))    printEE();
  else if( !strcmp( linebuf, "record" ))   recordEE();
  else {
    // hack for now...
    linebuf[4] = '\0';
    if( !strcmp( linebuf, "poke" )) pokeEE( &linebuf[5] );
    else {
      // wut?  print out help.
      Serial.println( "" );
      Serial.println( "Unknown command.  '?' for help." );
    }
  }
  
  // draw the prompt
  Serial.println( "" );
  Serial.print( "> " );
}

void loop()
{ 
  // if there's serial, let's handle it...
  if( Serial.available() ) {
    handleSerial();
  }
  
  // slow pulse on idle...
  digitalWrite( kLED, (millis() & 0x0200)? HIGH:LOW );
}
