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



/* fonction qui crée une nouvelle cellule BSS */

DATA nouvdata(char* data,char* type, int nbop, int line, int dec, OPDD operande){
	DATA ldata = calloc(1,sizeof(*ldata));
	strcpy(ldata->data, data);
	strcpy(ldata->type, type);
	ldata->nbop = nbop;
	ldata->line = line;
	ldata->dec = dec;
	/*OPDD operande = calloc(1,sizeof(*ldata));
	strcpy(operande->token,optoken);
	operande->type = typeop;*/
	ldata->operande = operande;
	return ldata;
}



LISTE  lecture_data(char* data, char* type, int nbop, int line, int dec, OPDD operande, LISTE l){
		LEXEM c = l->val;
		if(strcmp(c->obj, ".byte") || strcmp(c->obj, ".word") || strcmp(c->obj, ".asciiz") || strcmp(c->obj, ".space")){
			strcpy(data, c->obj);
			line = c->nline;
			strcpy(type, c->obj);
			nbop = 0;
			while(c->type != NL){
				if(c->type == HEX || c->type == DECIM){
					nbop++;
					strcpy(operande.token , c->obj);
					operande.type = INT_DD;
				}
				if(c->type == SYMB){
					nbop++;
					strcpy(operande.token , c->obj);
					operande.type = SYMB_DD;
				}
				l = l->suiv;
				c = l->val;
			}
		}
		return l;
}
