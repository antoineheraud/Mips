#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include <global.h>
#include <notify.h>
#include <lex.h>
#include <liste.h>
#include <instruction.h>
#include <donneesdata.h>
#include <donneesbss.h>
#include <tablesymb.h>

LISTE nouvliste(){ return NULL;}

int listevide(LISTE l){
	return !l;
}

/*LISTE enqueue(void* p,LISTE l){
	LISTE nl = calloc(1,sizeof(*nl));
	nl-> val = p;
	nl-> suiv = NULL;

	if (listevide(l)){
		return nl;
	}

	else{
		while(l->suiv != NULL){
			p = p->suiv;
		}
		p->suiv = nl;
	return l;
}
*/
LISTE entete(LISTE l, void* val){
	LISTE nl = nouvliste();
	nl = calloc(1,sizeof(*nl));
	/*if (l == NULL || nl == NULL) exit(EXIT_FAILURE);*/
	nl->val = val;
	nl ->suiv = l;
	return nl;
}
/*
IT nouvinst(char* token, int nbop, int nline, int dec,OPINST* opt){
	int i = 0;
	IT lit = calloc(1,sizeof(*lit));
	strcpy(lit->obj, token);
	lit->nbop = nbop;
	lit->line = nline;
	lit->dec = dec;
	for (i=0;i<nbop;i++){
		OPINST opi = calloc(1,sizeof(*opi));
		strcpy(opi->token, opt[i]-> token);
		opi->type = opt[i]->type;
		lit->opt[0] =  opi;
	}
}

BSS nouvbss(char* type, int nbop, int line, int dec,int valeur){
	BSS lbss = calloc(1,sizeof(*lbss));
	strcpy(lbss->type, type);
	lbss->nbop = nbop;
	lbss->nline = nline;
	lbss->dec = dec;
	lbss->valeur = valeur;
	return lbss;
}

DATA nouvdata(char* type, int nbop, int line, int dec, char* optoken, TYPOP typeop){
	DATA ldata = calloc(1,sizeof(*ldata));
	strcpy(ldata->type, type);
	ldata->nbop = nbop;
	ldata->nline = nline;
	ldata->dec = dec;
	OPDD operande = calloc(1,sizeof(*ldata));
	strcpy(operande->token,optoken);
	operande->type = typeop;
	ldata->operande = operande;
	return ldata;
}
*/

void printL(LISTE l ){


	LEXEM nlex;
	nlex = l->val ;
	while (l != NULL){
		nlex = l->val;

		printtype(nlex->type);
		printf("%s \nnuméro de ligne %d \n",nlex->obj,nlex->nline);
		l = l->suiv;
	}
	printf("NULL\n");
}

void printtype(TYPE_L type){
	if (type == COMMENTS) printf("COMMENT \n");
	if (type == DIRECT) printf("DIRECTIVE \n");
	if (type == CHAIN) printf("CHAIN \n");
	if (type == SYMB) printf("SYMBOLE \n");
	if (type == DECIM) printf("DECIMALE \n");
	if (type == HEX) printf("HEXA \n");
	if (type == REG) printf("REGISTRE \n");
	if (type == DEUX_P) printf("DEUX_POINTS\n");
	if (type == VIRG) printf("VIRGULE \n");
	if (type == NLINE) printf("NOUVELLE LIGNE \n");
	if (type == ZERO) printf("ZERO \n");
	if (type == P_GAU) printf("PARENTHESE GAUCHE \n");
	if (type == P_DROI) printf("PARENTHESE DROITE \n");
	if (type == NL) printf("NOUVELLE LIGNE\n" );
}

void reverse(LISTE *l){
	LISTE inv = *l, tete;
	if (inv && inv->suiv){
		tete = inv->suiv;
		reverse (&(inv->suiv));
		tete->suiv = inv;
		*l = inv->suiv;
		tete->suiv->suiv = NULL;
	}
}
LISTE enchaine(LISTE l, void* val ){
	LISTE nl = nouvliste();
	nl = calloc(1,sizeof(*nl));

	nl->val = val;
	nl->suiv = NULL;

	if (l != NULL){
		LISTE la = l;
		while (la->suiv != NULL){
			la = la->suiv;
		}
		la->suiv = nl;
	}

	return nl;
}
