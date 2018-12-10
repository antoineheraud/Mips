
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

void machine_etat_2(LISTE listlex, LISTE* collect_ins, LISTE* collect_data, LISTE* collect_bss,LISTE* collect_symb,inst_def_t* dict, int* p_nb_inst,psinst_def_t* pseudo_dict, int* p_nb_pseudo_inst){

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
    int dec = 0;
    int decb = 0;
    int decbs = 0;
    int pinst;
    int* ppinst = &pinst;
    /* parametres de la collection d'instruction*/


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
    printf("%s\n", pseudo_dict[4].symbole);
    printf("mach\n");
    while(l1 != NULL){     printf("%s\n",c->obj);printtype(c->type);
    	switch(S){
    	    case INIT:
              printf("init\n");
    	        if(c->type == COMMENTS|| c->type == NL) S = INIT;
				      else if(!strcmp(c->obj, ".text"))	{S = TEXT;printf("Text\n");}
				      else if(!strcmp(c->obj, ".data"))	{S = DATA1;printf("data1\n");}
				      else if(!strcmp(c->obj, ".bss"))	{S = BSS1;printf("bss1\n");}
            /*  else if(c1->obj == ':') { S = ETI;printf("etiquette\n")}   */
    	        break;

			case TEXT:printf("Text\n");/*printf("%s\n",c->obj);*/


      /* fonction pour passer le token en minuscule */
        for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
        /*printf("%s\n",c->obj);*/

				if(!strcmp(c->obj, ".data")){ S = DATA1;printf("1if\n");}

				else  if(!strcmp(c->obj, ".bss")){ S = BSS1;printf("1eif\n");break;}
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("nul\n" );
          lecture_etiquette(c->obj/*, type*/, &line, &dec, ".text",collect_symb);
          listlex = listlex->suiv;
        }
				else{printf("traitement\n");pinst = 0;
          OPINST opt1 = calloc(1,sizeof(*opt1));/* printf("%p\n",opt1);*/
          OPINST opt2 = calloc(1,sizeof(*opt2));/*printf("%p\n",opt2);*/
          OPINST opt3 = calloc(1,sizeof(*opt3));/*printf("%p\n",opt3);printf("%p\n",&opt3);*/

          listlex=lecture_instruction(collect_ins,ppinst, token, type, &nbop, &line, &dec, &opt1,&opt2,&opt3, listlex, dict, p_nb_inst, pseudo_dict, p_nb_pseudo_inst);
          printf("lecture\n");printf("pinst vaut : %d\n",pinst);
          /*printf("%s \n",opt[0].token);*/
          /*printf("%s\n",(opt1)->token);*/
          /*control fonctionnement lecture_instruction */
          /*printf("%s %s %d %d %d\n",token,type,nbop,line,dec);*/

          if (pinst == 0){printf("pinst = 0\n");
				        INST = nouvinst(token, type, nbop, line, dec, opt1,opt2,opt3);
          /*printf("op : %s\n",(INST->opt1)->token);
          printf("inst\n");
          /*control fonctionnement nouvinst */
            printf("nbop : %d, line : %d, dec : %d\n", INST->nbop,INST->line,INST->dec);

            printf("inst : %s\n",INST->obj);
            if (nbop>0){
              printf("op : %s\n",(INST->opt1)->token);
              TYPEOPINST typeop = (INST->opt1)->type;
              printtypeI(typeop);
            }
            if (nbop>1){
              printf("op : %s\n",(INST->opt2)->token);
              TYPEOPINST typeop = (INST->opt2)->type;
              if (typeop == REGI) printf("REGI\n");
              if (typeop == ETIQ) printf("ETIQ\n");
              if (typeop == SA) printf("SA\n");
              if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");}

              if(nbop>2){
                printf("op : %s\n",(INST->opt2)->token);
                TYPEOPINST typeop = (INST->opt2)->type;
                if (typeop == REGI) printf("REGI\n");
                if (typeop == ETIQ) printf("ETIQ\n");
            if (typeop == SA) printf("SA\n");
            if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");}

          /* fin du control */

		 		     *collect_ins = entete(*collect_ins, INST);
             printf("entete\n");
        /*  for(i = 0; i<nbop;i++){printf("op : %s\n",(INST->opt[i])->token);
          TYPEOPINST typeop = (INST->opt[i])->type;
          if (typeop == REGI) printf("REGI\n");
          if (typeop == ETIQ) printf("ETIQ\n");
          if (typeop == SA) printf("SA\n");
          if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");
      }*/}
          if (pinst != 0){printf("pinst != 0\n");
            listlex=lecture_instruction(collect_ins,ppinst, token, type, &nbop, &line, &dec, &opt1,&opt2,&opt3, listlex, dict, p_nb_inst, pseudo_dict, p_nb_pseudo_inst);

          }
      }

		 		 break;

		 	case DATA1:printf("data1\n");printf("%s\n",c->obj);
        for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
        printf("%s\n",c->obj);
		 		if(!strcmp(c->obj, ".text")) S = TEXT;
				else if(!strcmp(c->obj, ".bss")) S = BSS1;
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("eti\n" );
          lecture_etiquette(c->obj/*,type*/, &line, &decb, ".data",collect_symb);
          listlex = listlex->suiv;
        }
		 		else{printf("traitement\n");
        OPDD operande = calloc(1,sizeof(*operande));
        if (!strcmp(c->obj, ".word")){ printf("OUF");}
		 		listlex= lecture_data(data,/* type,*/ &nbop, &line, &decb, operande, listlex);
        printf("pff");
				DT = nouvdata(data, /*type,*/ nbop, line, decb, operande);
		 		*(collect_data) = entete(*(collect_data), DT);}
		 		break;

		 	case BSS1:printf("bss1\n");printf("%s\n",c->obj);
        for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
        printf("%s\n",c->obj);
		 		if(!strcmp(c->obj, ".text")) S = TEXT;
				else if(!strcmp(c->obj, ".data")) S = DATA1;
        else if(!strcmp(c->obj, "\0")) {printf("nl\n");break;}
        else if(!strcmp(c1->obj, ":")) {
          printf("obj : %s\n",c->obj );
          lecture_etiquette(c->obj, /*type,*/ &line, &decbs, ".bss",collect_symb);
          listlex = listlex->suiv;
        }
				else{
        BSS BS = calloc(1,sizeof(*BS));
				listlex = lecture_bss(bss, /*type,*/ &nbop, &line, &decbs, &valeur, listlex);
        printf("nouv\n");
				BS = nouvbss(bss, /*type,*/ nbop, line, decbs, valeur);

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


void lecture_etiquette(char* token,/*char* type,*/int* line,int* dec, char* section, LISTE* collect_symb){
  TS leti = calloc(1,sizeof(*leti));
  printf("lect etiq\n");
  strcpy(leti->etiq, token);
/*  strcpy(leti->type,type);*/
  strcpy(leti->section, section);
  leti->line = *line;
  leti->dec = *dec;
  *collect_symb = entete((*collect_symb),leti);

}
