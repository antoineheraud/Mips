#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include "global.h"
#include "notify.h"
#include "lex.h"
#include "liste.h"
#include "instruction.h"
#include "donneesdata.h"
#include "donneesbss.h"
#include "tablesymb.h"
#include "table_de_relocation.h"


typedef enum typeopdd TYPOPDATA;

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

void printLex(LISTE l ){
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}

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

void printLINST(LISTE l){
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}
	IT ninst = l->val ;
	int i = 0;
	while (l != NULL){
		ninst = l->val;
		;
		printf("%s \nnuméro de ligne %d \nnombre op : %d\ndécalage %d\n",ninst->obj,ninst->line, ninst->nbop,ninst->dec);
		printf("type instruction %s\n",ninst->type);
		if ( ninst->nbop>0){
			printf("op 1 : %s\n",(ninst->opt1)->token);
			TYPEOPINST typeop = (ninst->opt1)->type;
			printf("type  ");
			printtypeI(typeop);
		}
		if ( ninst->nbop>1){
			printf("op 12: %s\n",(ninst->opt2)->token);
			TYPEOPINST typeop = (ninst->opt2)->type;
			printf("type  ");
			printtypeI(typeop);
		}
		if ( ninst->nbop>2){
			printf("op 3 : %s\n",(ninst->opt3)->token);
			TYPEOPINST typeop = (ninst->opt3)->type;
			printf("type  ");
			printtypeI(typeop);
			}

		l = l->suiv;
	}
	printf("NULL\n");
}

void printtypeI(TYPEOPINST type){
	if (type == REGI) printf("REGI \n");
	if (type == BASE_OFFSET) printf("BASE_OFFSET \n");
	if (type == IMMEDIATE) printf("IMMEDIATE \n");
	if (type == SA) printf("SA \n");
	if (type == TARGET) printf("TARGET \n");
	if (type == ETIQ) printf("ETIQ \n");

}

void PrintLdata(LISTE l){
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}
	DATA nouvdata = l->val;
	int i = 0;
	while (l!=NULL){
		nouvdata = l->val;
		printf("\n %s \n",nouvdata->data);
	/*	printf("type : %s \n",nouvdata->type);*/
		printf("line : %d \n",nouvdata->line);
		printf("nbop : %d \n",nouvdata->nbop);
		printf("decalage : %d \n",nouvdata->dec);
		printf(" opérande : %s \ntype :",(nouvdata->operande)->token);
		printtypeDA((nouvdata->operande)->type);
		l=l->suiv;
	}

}

void printtypeDA(TYPOPDATA type){
	if (type == CHAR_DD) printf("CHAR_DD \n");
	if (type == INT_DD) printf("INT_DD \n");
	if (type == UNSIGNED_INT_DD) printf("UNSIGNED_INT_DD \n");
	if (type == CHAIN_DD) printf("CHAIN_DD \n");
	if (type == SYMB_DD) printf("SYMB_DD \n");
}
void PrintLbss(LISTE l){
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}
	BSS nouvbss = l->val;
	int i = 0;
	while (l!=NULL){
		nouvbss = l->val;
		printf("\n %s \n",nouvbss->bss);
	/*	printf("type : %s \n",nouvbss->type);*/
		printf("line : %d \n",nouvbss->line);
		printf("nbop : %d \n",nouvbss->nbop);
		printf("decalage : %d \n",nouvbss->dec);
		printf("valeur : %d\n",nouvbss->valeur);
		l=l->suiv;
	}

}

void Printtable_reloc(LISTE l){printf("print table reloc\n");
	if (l == NULL) {
		printf("table vide\n");
		return ;
	}
	tabrel nouvtr = l->val;
	TS nouvts;
	int i = 0;
	while( l!= NULL){
		nouvtr = l->val;
		printf("\n %s \n", nouvtr->section);
		printf("adresse relative %d \n",nouvtr->adresse);
		printf("type pas encore\n");
		nouvts = nouvtr->psymbol;
		printf("	Symbole : %s",nouvts->etiq);
		printf("	TYPE : %s",nouvts->type);
		printf("	Ligne : %d",nouvts->line);
		printf("	dec : %d\n",nouvts->dec);
		l = l->suiv;
	}
}

void print_etiquette(LISTE l){
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}
	TS nouvts = l->val;
	while(l!=NULL){
		nouvts = l->val;
		printf("\n%s\n", nouvts->etiq);
		printf("type : %s\n",nouvts->type );
		printf("line : %d\n",nouvts->line );
		printf("section : %s\n",nouvts->section );
		printf("décalage : %d\n",nouvts->dec );
		l=l->suiv;
	}
}

void printtypeBS(TYPOPDATA type){
	if (type == DEC_BSS) printf("DEC_BSS \n");
	if (type == HEX_BSS) printf("HEX_BSS\n");
}
void reverse(LISTE *l){printf("reverse\n\n");
	if (l == NULL){
		printf("liste vide\n");
		return ;
	}
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
