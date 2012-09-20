#include <stdio.h>

void setup( void );
void loop( void );

int main( int argc, char ** argv )
{
    printf( "Starting up TinyBasic Plus...\n\n" );

    setup();
    while( 1 )
	loop();
}
