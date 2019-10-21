#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define BUF 2000
#define BUF2 2

/*mettre en argument les bonnes carte*/
int print_carte()
{
  char buf[BUF];
  char buf2[BUF2];
  int fd ;
  int largeur=17;
  int longueur=0;
  int taille=0;
  int c=0;
  //On ouvre le fichier de la carte 
  fd=open("modes/niveaux/carteAjour",O_RDONLY);
  if(fd==-1){perror("Erreur Ouverture Carte");EXIT_FAILURE;}
  //On lis les 2 premier caracteres,pr savoir la largeur, 
  read(fd,buf2,2);
  largeur = atoi(buf2);//on convertie cette chaine de caractere en entier
  
  lseek(fd,3,SEEK_SET);	//on se positionne apres l'epace pr lire la longeur
  read(fd,buf2,2);
  longueur = atoi(buf2);//on convertie cette chaine de caractere en entier
  
  taille = largeur*longueur + largeur; // On multiple les 2 entiers puis on rajoute 10 pour compter les \n
  
  lseek(fd,6,SEEK_SET); // on se postionne sur la carte pr la lire
  
  c=read(fd,buf,taille);	// On lit la carte de taille taille  dans le buf
  if(c==0){perror("Erreur Lecture Carte");EXIT_FAILURE;}
  write(1,buf,taille);	// et on l'ecris sur la	sortie standard
  close(fd);

return 0;
}
