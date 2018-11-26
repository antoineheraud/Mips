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
#include <lecture.h>

/* fonction qui crée une nouvelle cellule BSS */

BSS nouvbss(char* bss, char* type, int nbop, int line, int dec,int valeur){
	BSS lbss = calloc(1,sizeof(*lbss));
	strcpy(lbss->bss, bss);
	strcpy(lbss->type, type);
	lbss->nbop = nbop;
	lbss->line = line;
	lbss->dec = dec;
	lbss->valeur = valeur;
	return lbss;
}





LISTE lecture_bss(char* bss, char* type, int nbop, int line, int dec, int valeur, LISTE l){
		LEXEM c = l->val;
		if(strcmp(c->obj, ".space")){printf("LOL\n");
			strcpy(bss, c->obj);
			line = c->nline;
			strcpy(type, c->obj);
			nbop = 0;
			printf("1\n");
			while(c->type != NL){printf("bouc\n");
				if(c->type == HEX || c->type == DECIM){
					nbop++;
					valeur = atoi(c->obj);
				}
				l = l->suiv;
				c = l->val;
			}
		}
		printf("end\n");
		return l;
}
