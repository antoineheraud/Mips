#ifndef _DONNEESBSS_H_
#define _DONNEESBSS_H_

#include <stdio.h>



enum typeopbss {
  DEC_BSS,
  HEX_BSS,
};

typedef enum typeopbss TYPEOPBSS;



struct bssdonnees {
  char bss[STRLEN]; /*mettre le token du lexeme type de données exemple .word*/
  char type[STRLEN];
  int nbop; /* nombre d'opérandes*/
  int line; /*numéro de la ligne */
  int dec;  /* décalage ou adresse relative dans la section*/
  int valeur; /* structure pour les opérandes*/
};

typedef struct bssdonnees* BSS;

#endif
