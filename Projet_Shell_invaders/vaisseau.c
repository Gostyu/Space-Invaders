#include <fcntl.h>
#include <poll.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
void initialise_vaisseau()
{
int dessin [3][5];

	dessin[0][0]='O';
	dessin[0][1]='-';
	dessin[0][2]='O';
	dessin[0][3]='-';
	dessin[0][4]='O';

	dessin[1][0]='\x5C';
	dessin[1][1]=' ';
	dessin[1][2]='|';
	dessin[1][3]=' ';
	dessin[1][4]='/';

	dessin[2][0]=' ';
	dessin[2][1]='\x5C';
	dessin[2][2]='*';
	dessin[2][3]='/';
	dessin[2][4]=' ';

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("%c", dessin[i][j]);
		}
	
}
}
int main()
{

initialise_vaisseau();//on l'initialise




return 0;
}
