#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUF 1024
#define BUF2 2
//Fonction qui sert a copier une carte , on utilse cette fonction pr ne pas modifier nos carte d'origine
//Fonction vu en TD
int cpy_carte (char *fichier)
{
    size_t c,d,e;
    FILE *cur = fopen(fichier,"r");
    FILE *cur2= fopen("modes/niveaux/carteAjour","w+");
    if (cur==NULL || cur2 == NULL)
    {
	perror("Erreurr ouverture copy carte");
	return 0;
    }
    char buff[100];
    while (!feof(cur)) 
    {
        c = fread(buff, 1, 100, cur);
        e=0;
        while (c>0) 
	{
	    d = fwrite(buff+e, 1, c, cur2);
            // TODO: rajouter la gestion des erreurs
            e+=d;
            c-=d;
        }       
    }
    fclose(cur);
    fclose(cur2);
    return 0;
}
