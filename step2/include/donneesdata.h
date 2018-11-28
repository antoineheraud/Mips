#ifndef _DONNEESDATA_H_
#define _DONNEESDATA_H_

#include <stdio.h>


/*  Peut servir mais flemme d'avoir trop d'enum*/
enum typeopdd {
  CHAR_DD,
  INT_DD,
  UNSIGNED_INT_DD,
  CHAIN_DD,
  SYMB_DD,
};

typedef enum typeopdd TYPOPDATA;

struct operandedd {
  char token[STRLEN];
  TYPOPDATA type; /*Soit DEC soit DECIM soit CHAIN (pour l'instant on n'a pas les binaires) */
};

typedef struct operandedd* OPDD;

struct datadonnees {
  char data[STRLEN];/*mettre le token du lexeme type de données exemple .word*/
/*  char type[STRLEN]; */
  int nbop; /* nombre d'opérandes*/
  int line; /*numéro de la ligne */
  int dec;  /* décalage ou adresse relative dans la section*/
  OPDD operande; /* structure pour les opérandes*/
  struct datadonnees* suiv;
};

typedef struct datadonnees* DATA;

#endif
