#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_


#include <stdio.h>


enum typeop{
  REGI,
  BASE_OFFSET, /* token  ex "-200($7)" */
  IMMEDIATE, /*valeur entière sur 16 bits / # valeur signée sur 16 bits */
  SA,  /*valeur entière sur  5 bits */
  TARGET, /*adresse de saut sur 28 bits donc sans les 4 bits de poids fort*/
  ETIQ,
};

typedef enum typeop TYPEOPINST;


/* structure opérande */
struct operande {
  char token[STRLEN];
  TYPEOPINST type;
  char typeR[STRLEN];
}  ;
typedef struct operande* OPINST;
/*typedef struct OPINST* POPINST;*/
/* tableau d'opérandes */
/*struct OPINST OPt[2];  tableau de taille 3 */
/*typedef struct OPt[2] OPtableau;  nom du tableau d'opérandes de taille 3*/

/*# structure pour stocker les instructions*/
struct instructiontxt {
  char obj[STRLEN];  /*mettre le token du lexeme instruction exemple ADD*/
  char type[STRLEN]; /*token du type d'instructions */
  int nbop; /* nombre d'opérandes*/
  int line; /*numéro de la ligne */
  int dec;  /* décalage ou adresse relative dans la section*/
  OPINST opt1;
  OPINST opt2;
  OPINST opt3;
  struct instructiontxt* suiv; /* structure pour les opérandes*/
};

typedef struct instructiontxt* IT;

#endif
