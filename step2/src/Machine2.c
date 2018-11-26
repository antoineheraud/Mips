
#include <stdio.h>
#include <string.h>



#include "global.h"
#include "notify.h"
#include "lex.h"
#include "liste.h"
#include "instruction.h"
#include "donneesdata.h"
#include "donneesbss.h"
#include "tablesymb.h"
#include "lecture.h"
#include "dictionnaire.h"


typedef enum { INIT, DATA1, BSS1, TEXT } etat;

void machine_etat_2(LISTE listlex, LISTE* collect_ins, LISTE* collect_data, LISTE* collect_bss,LISTE* collect_symb,inst_def_t* dict, int* p_nb_inst){

    etat S = INIT;
    LEXEM c = listlex->val;
    LISTE l1 = listlex->suiv;
    LEXEM c1 = NULL;
    if (l1 != NULL)  c1 = l1 ->val;
    /*printf("%s\n",c->obj);*/
    /* parametres communs des collections*/
    char token[STRLEN];
    char type[STRLEN];
    int nbop;
    int line;
    int dec;
    /* parametres de la collection d'instruction*/
    OPINST opt[STRLEN];

    IT INST;

    /* parametres de la collection de donnees data*/
    OPDD operande;
    DATA DT;
    char data[STRLEN];

    /* parametres de la collection de donnees bss*/
    int valeur;
    BSS BS;
    char bss[STRLEN];

    char lower[STRLEN];
    int i = 0;

    printf("mach\n");
    while(l1 != NULL){     printf("%sT\n",c->obj);printtype(c->type);
    	switch(S){
    	    case INIT:
              printf("init\n");
    	        if(c->type == COMMENTS|| c->type == NL) S = INIT;
				      else if(!strcmp(c->obj, ".text"))	{S = TEXT;printf("Text\n");}
				      else if(!strcmp(c->obj, ".data"))	{S = DATA1;printf("data1\n");}
				      else if(!strcmp(c->obj, ".bss"))	{S = BSS1;printf("bss1\n");}
            /*  else if(c1->obj == ':') { S = ETI;printf("etiquette\n")}   */
    	        break;

			case TEXT:printf("Text\n");printf("%s\n",c->obj);
      /* fonction pour passer le token en minuscule */
        for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
        printf("%s\n",c->obj);

				if(!strcmp(c->obj, ".data")){ S = DATA1;printf("1if\n");}

				else  if(!strcmp(c->obj, ".bss")){ S = BSS1;printf("1eif\n");break;}
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("nul\n" );
          lecture_etiquette(token, type, &line, &dec, ".text",collect_symb);
          listlex = listlex->suiv;
        }
				else{printf("traitement\n");
          listlex=lecture_instruction(token, type, &nbop, &line, &dec, opt, listlex, dict, p_nb_inst);
          printf("lecture\n");
          printf("%s \n",opt[2]->token);
          dec = 4;

          /*control fonctionnement lecture_instruction */
          printf("%s %s %d %d %d\n",token,type,nbop,line,dec);
          for (i = 0;i<nbop;i++){
            printf("%s ",opt[i]->token);
          }
          printf("\n");
          /* fin du control lecture_instruction */

				  INST = nouvinst(token, type, nbop, line, dec, opt);
          printf("op : %s\n",(INST->opt[2])->token);
          printf("inst\n");
          /*control fonctionnement nouvinst */
          printf("nbop : %d, line : %d, dec : %d\n", INST->nbop,INST->line,INST->dec);

          printf("inst : %s\n",INST->obj);

          for(i = 0; i<nbop;i++){printf("op : %s\n",(INST->opt[i])->token);
          TYPEOPINST typeop = (INST->opt[i])->type;
          if (typeop == REGI) printf("REGI\n");
          if (typeop == ETIQ) printf("ETIQ\n");
          if (typeop == SA) printf("SA\n");
          if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");
        }
          /* fin du control */

		 		  *collect_ins = entete(*collect_ins, INST);
          printf("entete\n");
          }

		 		 break;

		 	case DATA1:printf("data1\n");printf("%s\n",c->obj);
		 		if(!strcmp(c->obj, ".text")) S = TEXT;
				else if(!strcmp(c->obj, ".bss")) S = BSS1;
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("eti\n" );
          lecture_etiquette(token, type, &line, &dec, ".text",collect_symb);
          listlex = listlex->suiv;
        }
		 		else{printf("traitement\n");
        if (!strcmp(c->obj, ".word")){ printf("OUF");}
		 		listlex= lecture_data(data, type, nbop, line, dec, operande, listlex);
        printf("pff");
				DT = nouvdata(data, type, nbop, line, dec, operande);
		 		*(collect_data) = entete(*(collect_data), DT);}
		 		break;

		 	case BSS1:printf("bss1\n");printf("%s\n",c->obj);
		 		if(!strcmp(c->obj, ".text")) S = TEXT;
				else if(!strcmp(c->obj, ".data")) S = DATA1;
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("nul\n" );
          lecture_etiquette(token, type, &line, &dec, ".text",collect_symb);
          listlex = listlex->suiv;
        }
				else{
				listlex = lecture_bss(bss, type, nbop, line, dec, valeur, listlex);
        printf("nouv\n");
				BS = nouvbss(bss, type, nbop, line, dec, valeur);

		 		(*collect_bss) = entete((*collect_bss), BS);}
        printf("entete\n");
		 		break;


		}
    listlex = listlex->suiv;

		if (listlex == NULL) break;
    c = listlex->val;

    l1 = listlex->suiv;
    if (l1 != NULL)  c1 = l1 ->val;
    printf("%s\n",c->obj);printtype(c->type);
	}
}


void lecture_etiquette(char* token,char* type,int* line,int* dec, char* section, LISTE* collect_symb){
  TS leti = calloc(1,sizeof(*leti));
  strcpy(leti->etiq, token);
  strcpy(leti->type,type);
  strcpy(leti->section, section);
  leti->line = line;
  leti->dec = dec;
  *collect_symb = entete((*collect_symb),leti);

}
