
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


LISTE lecture_instruction(char* typeR,int* sdec,int *psymb,LEXEM* s,LISTE* collect_ins,int* pinst,char* token, char* type, int* pnbop, int* nline, int* dec, OPINST* opt1,OPINST* opt2,OPINST* opt3, LISTE l, inst_def_t* dict, int* p_nb_inst, psinst_def_t* pseudo_dict, int* p_nb_pseudo_inst){
		LEXEM c = l->val;
		LISTE lp = l;
		LEXEM cp = c;
		OPINST* opt = calloc(3,sizeof(*opt));
		int nb_opm;int j;int nbop;
		printf("lec_it\n");
		if (*pinst == 0){
		printf("%s\n",c->obj);
		OPINST opi = calloc(1,sizeof(*opi));
		int i;int z;
		nbop = 0;
		for(i=0; i< *p_nb_inst; i++){/*printf("boucle1\n");printf("%s\n",c->obj);printf("%s\n", dict[i].symbole);*/
			if(!strcmp(c->obj, dict[i].symbole)){printf("if1\n");printf("nb pseudo dict %d\n",*p_nb_pseudo_inst);
				for(j = 0;j< *p_nb_pseudo_inst;j++){
					printf("%s\n", pseudo_dict[j].symbole);
						if(!strcmp(c->obj, pseudo_dict[j].symbole)){printf("ENFIN\n");
							/*if(!strcmp(c->obj,"lw")){
								lp = lp->suiv;
								cp = lp->val;
								if(cp->type != REG){printf("break REGI\n"); break;}
								lp = lp->suiv;
								lp = lp->suiv;
								cp = lp->val;
								if(cp->type != SYMB ){printf("break SYMB\n");
									*pinst = j;
									return l;
								}
							}*/
							if(!strcmp(c->obj, "nop")){
								printf("YES\n");
								*pinst = j;printf("j vaut %d\n",*pinst);

								return l;
							}
						}
					}
				if(*pinst != 0){break;}
				strcpy(token, c->obj);
				*nline = c->nline;
				strcpy(type, dict[i].type);
				/* nbop = dict[i].nb_op*/
				*dec = *dec + 4;
				nb_opm = dict[i].nb_op;
				l = l-> suiv;
				c = l->val;
				z = i;
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
				*s = c;
				strcpy(typeR, dict[z].types[nbop-1]);
				*sdec = -1;
				*psymb = 1;
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
			if (*pinst != 0){
				printf(" on est dans pinst !\n%s\n",c->obj);
				OPINST opi = calloc(1,sizeof(*opi));
				int i;
				nbop = 0;
				*nline = c->nline;
				/* nbop = dict[i].nb_op*/

				nb_opm = pseudo_dict[*pinst].nb_op;
				l = l-> suiv;
				c = l->val;
				int psint = pseudo_dict[*pinst].nb_pop;
				while (nbop<nb_opm){
					opi = calloc(1,sizeof(*opi));
					nbop= 1+nbop;
					if(c->type == REG || c->type == HEX || c->type == DECIM || c->type == SYMB){
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
										opi->type = SA;}
								}

								opt[nbop - 1] = opi;}
					/*	if (strcmp(opt[nbop-1]->type , pseudo_dict[*pinst].types[nbop-1])){	WARNING_MSG("Mauvais type d'opérande à la ligne %d",*nline);}*/
						if(nbop > dict[i].nb_op){
							printf("Erreur d'incohérence de nombre d'opérandes à la ligne %d \n", *nline);
							return NULL;}
						l = l->suiv;
						c = l->val;
						if (!strcmp(c->obj, ",")){ /*printf ("ouf\n");*/
							l = l->suiv;
							c = l->val;
						}
						if (!strcmp(c->obj, "\0")){
							break;
						}
					}
					for (i=0;i<pseudo_dict[*pinst].nb_pop;i++){
	  				*dec = *dec + 4;
						OPINST* oppst = calloc(3,sizeof(*oppst));
						for (j=0;j<pseudo_dict[*pinst].inst[i].nb_op;j++){printf("j vaut %d\n",j);
							OPINST opps = calloc(1,sizeof(*opps));
							if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "OP1")){
								oppst[i] = opt[0];
							}
							else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "OP2")){
								oppst[i] = opt[1];
							}
							else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "OP3")){
								oppst[i] = opt[2];
							}
							/*else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "up_OP2")){

								oppst[i] = opt[0];
							}*/
							else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "$0")){printf(" $0 OK\n");
								strcpy(opps->token , "$0");
								opps->type = REGI;
								oppst[j] = opps;
							}
							else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "$1")){
								strcpy(opps->token , "$1");
								opps->type = REGI;
								oppst[j] = opps;
							}
							else if (!strcmp(pseudo_dict[*pinst].inst[i].types[j], "0")){printf("0 OK\n");
								strcpy(opps->token , "0");
								opps->type = SA ;
								oppst[j] = opps;
							}
						}
						printf("oppst1 vaut %s\n oppst2 vaut %s\n oppst3 vaut %s\n",oppst[0]->token,oppst[1]->token,oppst[2]->token);
						IT INST = nouvinst(pseudo_dict[*pinst].inst[i].symbole,pseudo_dict[*pinst].inst[i].type,pseudo_dict[*pinst].inst[i].nb_op,*nline,*dec,oppst[0],oppst[1],oppst[2]);
						*collect_ins = entete(*collect_ins, INST);
					  printf("entete\n");
					}
					return l;
				}
			}

/*type donnetype(char* c){


	if (!strcmp(c->obj, ))
}*/
