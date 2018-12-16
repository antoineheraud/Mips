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

DATA nouvdata(char* data,/*char* type,*/ int nbop, int line, int dec, OPDD operande){
	DATA ldata = calloc(1,sizeof(*ldata));
	strcpy(ldata->data, data);
/*	strcpy(ldata->type, type); */
	ldata->nbop = nbop;
	ldata->line = line;
	ldata->dec = dec;
	/*OPDD operande = calloc(1,sizeof(*ldata));
	strcpy(operande->token,optoken);
	operande->type = typeop;*/
	ldata->operande = operande;
	return ldata;
}



LISTE  lecture_data(char* typeR,int* sdec,int *psymb,LEXEM* s,char* data,/* char* type,*/ int* nbop, int* line, int* dec, OPDD operande, LISTE l){
		LEXEM c = l->val;printf("\n valeur de c->obj : %sT\n",c->obj);
	/*	if(! !strcmp(c->obj, ".word ") || !strcmp(c->obj, ".asciiz ") || !strcmp(c->obj, ".space ")){ */
		if (!strcmp(c->obj, ".word ")){

			printf("lec_dt\n");
			strcpy(data, c->obj);
			*line = c->nline;
			*dec = ((*dec%4)+1)*4;
		/*	strcpy(type, c->obj);*/
			*nbop = 0;
			while(c->type != NL){printf("coucou\n");
				 if(c->type == HEX || c->type == DECIM){printf("1\n");
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = INT_DD;
					printf("2\n");
				}
				if(c->type == SYMB){printf("etiquette\n");printf("3\n");
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = SYMB_DD;
					*s = c;
					strcpy(typeR,"R_MIPS_32");
					*sdec = -1;
					*psymb = 1;

				}
				l = l->suiv;
				c = l->val;
			}
		}
		if (!strcmp(c->obj, ".asciiz ")){
			printf("lec_dt\n");
			strcpy(data, c->obj);
			*line = c->nline;
			int taille = strlen(c->obj);

			*dec = *dec + taille;
			printf("taille : %d\n",taille);
		/*	strcpy(type, c->obj); */
			*nbop = 0;
			while(c->type != NL){printf("coucou\n");
				if(c->type == HEX || c->type == DECIM){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = INT_DD;
				}
				if(c->type == SYMB){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = SYMB_DD;
					s = c;
					*sdec = -1;
					*psymb = 1 ;
				}
				if(c->type == CHAIN){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = CHAIN_DD;
				}
				l = l->suiv;
				c = l->val;
			}
		}
		if (!strcmp(c->obj, ".space ")){
			printf("lec_dt\n");
			strcpy(data, c->obj);
			line = c->nline;
		/*	strcpy(type, c->obj);*/
			*nbop = 0;
			while(c->type != NL){printf("coucou\n");
				if(c->type == HEX || c->type == DECIM){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = INT_DD;
				}
				if(c->type == SYMB){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = SYMB_DD;
				}
				l = l->suiv;
				c = l->val;
			}
		}
		if (!strcmp(c->obj, ".byte ")){
			printf("lec_dt\n");
			strcpy(data, c->obj);
			line = c->nline;
			*dec = *dec + 1;
	/*		strcpy(type, c->obj); */
			*nbop = 0;
			while(c->type != NL){printf("coucou\n");
				if(c->type == HEX || c->type == DECIM){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = INT_DD;
				}
				if(c->type == SYMB){
					*nbop = *nbop +1;
					strcpy(operande->token , c->obj);
					operande->type = SYMB_DD;
				}
				l = l->suiv;
				c = l->val;
			}
		}


		printf("FIN\n");
		return l;
}
