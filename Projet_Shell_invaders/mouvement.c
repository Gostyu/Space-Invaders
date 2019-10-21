#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include "carte.h"
#define BUF 2

int mouvement(char *carte)
{

  char buf[BUF]= "\0";
  char buf2[BUF];
  int pos;
  int fd2=0;
  char* vaisseau = "T";
  int pos_depart = 1600;
  char* q="q";
  char* d="d";
  char* e="e";
  /*Fonction qui verifie autour si il y a un mur 0 ou un ennemi 1 */
  int mvmt_col(int fd,char *move, int pos)
  { 
    /*on lis le caractere si c'est un 0 ou si c un 1 alors on retourne 20 et on remet fd 
    a la position initial*/
 

	if(strcmp(move,q)== 0)
	{ 
	  pos = pos-1;
	  lseek(fd,pos,SEEK_SET);
	  read(fd,buf,1);
	  pos = pos+1;
	  lseek(fd,pos,SEEK_SET);

	  if((strcmp(buf,"0")!= 0)&&(strcmp(buf,"1")!= 0))
	  {
	    return 10;
	  }
	  return 20;
	}
	if(strcmp(move,d)== 0)
	{ 
	  pos = pos+1;
	  lseek(fd,pos,SEEK_SET);
	  read(fd,buf,1);
	  pos = pos-1;
	  lseek(fd,pos,SEEK_SET);

	  if((strcmp(buf,"0")!= 0)&&(strcmp(buf,"1")!= 0))
	  {
	    return 10;
	  }
	  return 20;
	}
    return -1;
  }
  /*POUR LE MODE NON CANONIQUE*/
  //On cree deux structure de type termios
  struct termios origine;
  struct termios new;
  //On recupere la configuration initial du terminal et on la copie dans la new structure, on modifie enfin le flag
  if (tcgetattr(STDIN_FILENO,& origine)<0)
  perror("Erreur tcgetattr 1 : ");
  new =  origine;
  //On le met en mode non canonique (ICANON pas positioné)
  new.c_lflag = !ICANON; 
  //et on veut 1 caractere par 1  caractere
  new.c_cc[VMIN]=1;
  //temps qu"on a pas un caractere tapé on attend lis le man de termios vers le bas pour ne pas faire entrer a chaque fois*/
  new.c_cc[VTIME]=0;
  
  
  
  //On appique cette nouvelle configuration(new)
  if (tcsetattr(STDIN_FILENO,TCSANOW,&new)<0)
  perror("Erreur tcgetattr 2 : ");
  //FInc non cano
  fd2=open(carte,O_RDWR);
//   write(fd2,buf,taille);
  
  if(fd2==-1){perror("Erreur Ouverture Carte 3");EXIT_FAILURE;}
  //On lis les 2 premier caracteres,pr savoir la largeur, 
  
  read(fd2,buf2,2);
  
  lseek(fd2,3,SEEK_SET);	//on se positionne apres l'epace pr lire la longeur
  read(fd2,buf2,2);  
  lseek(fd2,pos_depart,SEEK_SET);
  write(fd2,vaisseau,1);
 
  //On affiche une fois la carte
  print_carte("modes/niveaux/carteAjour");
  //Config de poll pour l'écoute de l'entré standard donc clavier
  struct pollfd fds[1];
  fds[0].fd=STDIN_FILENO;
  fds[0].events=POLLIN;
  pos=pos_depart;
  while (1)
  {
    poll(fds,1,-1);
    if(fds[0].revents & POLLIN)
    {
  
	read(fds[0].fd,buf,1);
	
	
	if(strcmp(buf,q)== 0)
	{ 
	  lseek(fd2,pos,SEEK_SET);
	  if (mvmt_col(fd2,buf,pos)==10)
	  {
	      write(fd2," ",1);
	      pos = pos-1;
	      lseek(fd2,pos,SEEK_SET);
	      write(fd2,vaisseau,1);
	      print_carte("modes/niveaux/carteAjour"); 
	  }
	}
	if(strcmp(buf,d)== 0)
	{ 
	  lseek(fd2,pos,SEEK_SET);
	  if (mvmt_col(fd2,buf,pos)==10)
	  {    
	      write(fd2," ",1);
	      pos = pos+1;
	      lseek(fd2,pos,SEEK_SET);
	      write(fd2,vaisseau,1);
	      print_carte("modes/niveaux/carteAjour");
	  }
	}
	if(strcmp(buf,e)== 0)
	{
	  close(fd2);
	  unlink("modes/niveaux/carteAjour");
	  //On remet la configuration d'orgine
	  if (tcsetattr(STDIN_FILENO,TCSANOW,& origine)<0)
	  perror("Erreur tcgetattr 3: ");
	  break;
	}
      }
  }
  return 0;
}
