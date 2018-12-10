#ifndef _LISTE_H_
#define _LISTE_H_


#include <stdio.h>
#include <string.h>


#include "global.h"
#include "notify.h"
/*#include <lex.h>*/
/*#include <instruction.h>
#include <donneesdata.h>
#include <donneesbss.h>
#include <tablesymb.h>*/
typedef enum type TYPE_L;
typedef enum typeop TYPEOPINST;

struct cellule {
	void* val;
	struct cellule* suiv;
};
typedef struct cellule CELLULE;
typedef CELLULE* LISTE;
LISTE nouvliste();
int listevide(LISTE l);
/*LISTE enqueue(void* p,LISTE l);*/
LISTE entete(LISTE l, void* val);
void printLex(LISTE l );
/*IT nouvinst(char* token, int nbop, int nline, int dec,OPINST* opt);*/
LISTE enchaine(LISTE l, void* val );
void reverse(LISTE *l);
void printtype(TYPE_L type);
void printLINST(LISTE l);
void printtypeI(TYPEOPINST type);
void PrintLdata(LISTE l);
void printtypeDA(TYPOPDATA type);
void PrintLbss(LISTE l);
void printtypeBS(TYPOPDATA type);
void print_etiquette(LISTE l);
#endif /* _LISTE_H_ */
