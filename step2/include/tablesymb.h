#ifndef _TABLESYMB_H_
#define _TABLESYMB_H_

#include <stdio.h>
#include <liste.h>


struct tablesymb {
  char etiq[STRLEN];
  char type[STRLEN];  /*mettre le token du lexeme type de données exemple .word*/
  int line; /*numéro de la ligne */
  char section[STRLEN];
  int dec;  /* décalage ou adresse relative dans la section*/

};

typedef struct tablesymb* TS;

#endif
