#include <stdio.h>
#include "carte.h"
#include "cpycarte.h"
#include "mouvement.h"
int main()
{
  cpy_carte("modes/niveaux/1");
  mouvement("modes/niveaux/carteAjour");
  return 0;
}
