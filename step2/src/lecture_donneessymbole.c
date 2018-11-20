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
#include <dictionnaire.h>


int islabel(LISTE l){
	LEXEM c = l->val;
	if(c->type == SYMB){
		if(((LEXEM)l->suiv->val)->type == DEUX_P)	return 1;
		else return 0;
	}
	return 0;
}

TS nouvts(LISTE l, TS tabsym){
	LEXEM c = l->val;
		strcpy(tabsym->etiq, c->obj);
		strcpy(tabsym->type, "SYMB");
		tabsym->line = c->nline;
		strcpy(tabsym->section, "TEXT");
		tabsym->dec = 4;
		tabsym->suiv = NULL;
	return tabsym;	
}


