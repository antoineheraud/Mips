
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
OPINST* nouvopt(){
	OPINST* op = calloc(STRLEN,sizeof(*op));
	return op;
}
IT nouvinst(char* token, char* type, int nbop, int nline, int dec, OPINST* opt1,OPINST* opt2,OPINST* opt3){
	int i = 0;
	IT lit = calloc(1,sizeof(*lit));
	strcpy(lit->obj, token);
	strcpy(lit->type, type);
	lit->nbop = nbop;
	lit->line = nline;
	lit->dec = dec;
	/*for (i=0;i<nbop;i++){
		OPINST opi = calloc(1,sizeof(*opi));
		strcpy(opi->token, opt[i]-> token);
		opi->type = opt[i]->type;
		lit->opt[0] =  opi;
	}*/
	lit->opt1 = opt1;
	lit->opt2 = opt2;
	lit->opt3 = opt3;
	lit->suiv = NULL;
	return lit;
}


LISTE lecture_instruction(char* token, char* type, int* pnbop, int* nline, int* dec, OPINST* opt1,OPINST* opt2,OPINST* opt3, LISTE l, inst_def_t* dict, int* p_nb_inst){
		LEXEM c = l->val;
		OPINST* opt = calloc(3,sizeof(*opt));
		int nb_opm;int j;int nbop;
		printf("lec_it\n");
		printf("%s\n",c->obj);
		OPINST opi = calloc(1,sizeof(*opi));
		int i;
		nbop = 0;
		printf("%d\n",*p_nb_inst);
		for(i=0; i< *p_nb_inst; i++){/*printf("boucle1\n");printf("%s\n",c->obj);printf("%s\n", dict[i].symbole);*/
			if(!strcmp(c->obj, dict[i].symbole)){printf("if1\n");
				strcpy(token, c->obj);
				*nline = c->nline;
				strcpy(type, dict[i].type);
				/* nbop = dict[i].nb_op*/
				*dec = *dec + 4;
				nb_opm = dict[i].nb_op;
				nbop = 0;
				printf("ici\n");
				l = l-> suiv;
				c = l->val;
				break;
			}
		}

		while (nbop<nb_opm){/*printf("boucle2\n");printf("%s",c->obj);*/
			opi = calloc(1,sizeof(*opi));

			nbop= 1+nbop;/*printf("nbop %d\n", nbop);*/
			if(c->type == REG || c->type == HEX || c->type == DECIM || c->type == SYMB){ /*printf("w2\n");*/

				if(c->type == SYMB){printf("SYMB\n");
				strcpy(opi->token, c->obj);
				opi->type = ETIQ;
			}

				if(c->type == REG){printf("REG\n");
							strcpy(opi->token, c->obj);
							opi->type = REGI;
						}

					else if(c->type == HEX){printf("HEX\n");
						if(!strcmp(dict[i].symbole, "ADDI") || !strcmp(dict[i].symbole, "LUI") || !strcmp(dict[i].symbole, "LI")){
							strcpy(opi->token, c->obj);
							opi->type = IMMEDIATE;
							}
						else if(!strcmp(dict[i].symbole, "ROTR") || !strcmp(dict[i].symbole, "SLL") || !strcmp(dict[i].symbole, "SRL")){
							strcpy(opi->token, c->obj);
							opi->type = SA;
							}
						}

					else if(c->type == DECIM){printf("DECIM\n");
						if(((LEXEM)l->suiv->val)->type == P_GAU){   /* endroit intéréssant*/
							opi->type = BASE_OFFSET;
							while(c->type != P_DROI){ printf("P\n");
								strcat(opi->token, c->obj);
								l = l->suiv;
								c = l->val;
							}
							strcat(opi->token, c->obj);
						}
						else if(!strcmp(dict[i].symbole, "addi") || !strcmp(dict[i].symbole, "lui") || !strcmp(dict[i].symbole, "li")){
							strcpy(opi->token, c->obj);
							opi->type = IMMEDIATE;
							}
						else if(!strcmp(dict[i].symbole, "rotr") || !strcmp(dict[i].symbole, "sll") || !strcmp(dict[i].symbole, "srl")){
								strcpy(opi->token, c->obj);
								opi->type = SA;
								}

						}

					/*	printf("finw2\n");printf("nbop %d\n", nbop);  */
						opt[nbop - 1] = opi;
					} /* fin if reg/hex/decim */



				if(nbop > dict[i].nb_op){
					printf("Erreur d'incohérence de nombre d'opérandes à la ligne %d \n", *nline);
					return NULL;}
			/*	printf (" hey\n");printf("%s\n",c->obj);/*
			/*	strcpy(opi->token,c->obj);  */
				l = l->suiv;
				c = l->val;
				if (!strcmp(c->obj, ",")){ /*printf ("ouf\n");*/
					l = l->suiv;
					c = l->val;

				}
				if (!strcmp(c->obj, "\0")){
					break;
				}   /* fin if saut de ligne */


			};   /* fin du grand while */
			*pnbop = nbop;
			printf("%p",*opt2);
			printf("valeur opt[1] %s\n", opt[0]->token);
			*opt1 = opt[0];

			printf("valeur opt[1] %s\n", (*opt1)->token);

			*opt2 = opt[1];
			printf("valeur opt[2] %s\n", (*opt2)->token);
			*opt3 = opt[2];
			printf("valeur opt[3] %s\n", (*opt3)->token);

		/*	opt[nbop+1] = opi; */
			return l;}
