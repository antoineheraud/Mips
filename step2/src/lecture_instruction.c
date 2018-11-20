
#include <stdio.h>



#include <global.h>
#include <notify.h>
#include <lex.h>
#include <liste.h>
#include <instruction.h>
#include <donneesdata.h>
#include <donneesbss.h>
#include <tablesymb.h>
#include <dictionnaire.h>


/* fonction qui crée une nouvelle cellule BSS */

IT nouvinst(char* token, char* type, int nbop, int nline, int dec, OPINST opt[]){
	int i = 0;
	IT lit = calloc(1,sizeof(*lit));
	strcpy(lit->obj, token);
	strcpy(lit->type, type);
	lit->nbop = nbop;
	lit->line = nline;
	lit->dec = dec;
	for (i=0;i<nbop;i++){
		OPINST opi = calloc(1,sizeof(*opi));
		strcpy(opi->token, opt[i]-> token);
		opi->type = opt[i]->type;
		lit->opt[0] =  opi;
	}
	lit->suiv = NULL;
	return lit;
}


LISTE lecture_instruction(char* token, char* type, int* nbop, int* nline, int* dec, OPINST* opt, LISTE l, inst_def_t* dict, int* p_nb_inst){
		LEXEM c = l->val;
		int nb_opm;int j;
		printf("lec_it\n");
		int i;
		for(i=0; i< *p_nb_inst; i++){printf("boucle1\n");printf("%s\n",c->obj);printf("%s\n", dict[i].symbole);
			if(!strcmp(c->obj, dict[i].symbole)){printf("if1\n");
				strcpy(token, c->obj);
				*nline = c->nline;
				strcpy(type, "SYMB");
				/* *nbop = dict[i].nb_op*/;
				nb_opm = dict[i].nb_op;
				*nbop = 0;
				printf("ici\n");
				l = l-> suiv;
				c = l->val;
				break;
			}
		}

		while (*nbop<nb_opm){printf("boucle\n");printf("%s",c->obj);
				/*while(c->obj != '\0'){printf("while\n" );*/

			if(c->type == REG || c->type == HEX || c->type == DECIM){printf("nbop %d\n", *nbop); printf("w2\n");
				*nbop = *nbop + 1;printf("nbop %d\n", *nbop);
					if(c->type = REG){printf("REG\n");
							strcpy(opt[*nbop-1]->token, c->obj);printf("1\n");
							opt[*nbop-1]->type = REGI;printf("2\n");
						}

					else if(c->type = HEX){printf("HEX\n");
						if(!strcmp(dict[i].symbole, "ADDI") || !strcmp(dict[i].symbole, "LUI") || !strcmp(dict[i].symbole, "LI")){
							strcpy(opt[*nbop-1]->token, c->obj);
							opt[*nbop-1]->type = IMMEDIATE;
							}
						else if(!strcmp(dict[i].symbole, "ROTR") || !strcmp(dict[i].symbole, "SLL") || !strcmp(dict[i].symbole, "SRL")){
							strcpy(opt[*nbop-1]->token, c->obj);
							opt[*nbop-1]->type = SA;
							}
						}

					else if(c->type = DECIM){printf("DECIM\n");
						if(((LEXEM)l->suiv->val)->type == P_GAU){   /* endroit intéréssant*/
							opt[*nbop-1]->type = BASE_OFFSET;
							while(c->type != P_DROI){
								strcat(opt[*nbop-1]->token, c->obj);
								l = l->suiv;
								c = l->val;
							}
						}
						else if(!strcmp(dict[i].symbole, "ADDI") || !strcmp(dict[i].symbole, "LUI") || !strcmp(dict[i].symbole, "LI")){
							strcpy(opt[*nbop-1]->token, c->obj);
							opt[*nbop-1]->type = IMMEDIATE;
							}
						else if(!strcmp(dict[i].symbole, "ROTR") || !strcmp(dict[i].symbole, "SLL") || !strcmp(dict[i].symbole, "SRL")){
								strcpy(opt[*nbop-1]->token, c->obj);
								opt[*nbop-1]->type = SA;
								}

						}
						l = l->suiv;
						c = l->val;
						printf("finw2\n");printf("nbop %d\n", *nbop);
					}

				if(*nbop > dict[i].nb_op){
					printf("Erreur d'incohérence de nombre d'opérandes à la ligne %d \n", *nline);
					return NULL;}
				printf (" hey\n");printf("%s\n",c->obj);
				if (!strcmp(c->obj, ",")){printf ("ouf\n");
					l = l->suiv;
					c = l->val;
					*nbop = *nbop - 1;
				}
				if (!strcmp(c->obj, "\0")){
					break;
				}
				l = l->suiv;
				c = l->val;

					};

			return l;}
