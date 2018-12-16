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
#include "lecture.h"
#include "dictionnaire.h"




/* Charge le fichier tabionnaire nomFichierDico
 Retourne un pointeur sur le tableau tabionnaire
 stocke le nb d'instructions dans *p_nb_inst */
void lect_dico_int(char* nomFichierDico, int* p_nb_inst,inst_def_t** dict){
	FILE* f1 = NULL;
    int i; int j; int k;
	char s1[STRLEN];



	f1=fopen(nomFichierDico, "r");	printf("1\n");

	if(f1 == NULL){
		puts("Erreur d'ouverture du fichier source");
		}
	if(fscanf(f1, "%d", p_nb_inst) != 1){
		puts("Erreur d'avoir le nombre d'instructions dans le fichier source");
	}
	printf("10\n");printf("nombre op %d\n ", *p_nb_inst);printf("2\n");
	inst_def_t* tab = calloc(*p_nb_inst,sizeof(*tab));

	/*tab=calloc(*p_nb_inst, sizeof(*tab));*/	printf("2\n");

	if(tab == NULL){
		puts("Erreur d'allocation du tableau");
	}
		/*printf("retour du scanf %d\n",fscanf(f1, "%s %c %d", s1, &(tab[i].type), &(tab[i].nb_op)) );*/
	for(i=0; i< *p_nb_inst; i++){printf("\n");
		if( fscanf(f1, "%s ", tab[i].symbole /*s1*/ ) != 1 ) {
			free(tab);
			puts("Erreur de scanner des éléments dans le fichier source");
		}
		/*printf("%s\n", tab[i].symbole);*/
		fscanf(f1, "%s",tab[i].type); /* printf("%s\n",tab[i].type); */
		fscanf(f1, "%d",&tab[i].nb_op); /* printf("%d\n",tab[i].nb_op); */

		for (j = 0; tab[i].symbole[j];j++)  tab[i].symbole[j] = tolower(tab[i].symbole[j]);

		tab[i].types = calloc(tab[i].nb_op, sizeof(char));
		for(k=0; k<tab[i].nb_op; k++){
			tab[i].types[k] = calloc(3, sizeof(char));
			fscanf(f1, "%s", tab[i].types[k]);}

		/*strcpy(tab[i].symbole,s1);*/
		/*(tab[i].symbole)=strdupa(s1); on ne peut pas utiliser strdupa car
																		 cette fonction est dans une extension
																		 de string.h et non dans la librairie de base*/
		/*printf("%s\n",tab[i].symbole);*/}
	printf("\n\n\n\n");

	for (i = 0;i<*p_nb_inst;i++) {
		printf("%s\n",tab[i].type);
		printf("%s\n", tab[i].symbole);
		printf("%d\n",tab[i].nb_op);
	}
	printf("end\n\n" );
	*dict = tab;
	/*if( !strcmp(tab[27].symbole, "LI")) printf("Good\n");*/

	fclose(f1);
}


void lect_pseudo_dic(char* nomFichierDico, int* p_nb_inst,psinst_def_t** dict){
	FILE* f1 = NULL;
    int i; int j; int k;
	char s1[STRLEN];
	inst_def_t* psinst;



	f1=fopen(nomFichierDico, "r");

	if(f1 == NULL){
		puts("Erreur d'ouverture du fichier source");
		}
	if(fscanf(f1, "%d", p_nb_inst) != 1){
		puts("Erreur d'avoir le nombre d'instructions dans le fichier source");
	}
	printf("10\n");printf("nombre op %d\n ", *p_nb_inst);
	psinst_def_t* tab = calloc(*p_nb_inst,sizeof(*tab));
	printf("ouf\n");

	if(tab == NULL){
		puts("Erreur d'allocation du tableau");
	}

	for(i=0; i< *p_nb_inst; i++){printf("\n");
		if( fscanf(f1, "%s ", tab[i].symbole ) != 1 ) {
			free(tab);
			puts("Erreur de scanner des éléments dans le fichier source");
		}
		printf("%s\n",tab[i].symbole);
		fscanf(f1, "%s",tab[i].type);printf("%s \n",tab[i].type);
		fscanf(f1, "%d",&tab[i].nb_op);
		fscanf(f1,"%d",&(tab[i].nb_pop));
		for (j = 0; tab[i].symbole[j];j++)  tab[i].symbole[j] = tolower(tab[i].symbole[j]);
	;
		tab[i].types = calloc(tab[i].nb_op, sizeof(char));
		for(k=0; k<tab[i].nb_op; k++){
			tab[i].types[k] = calloc(16, sizeof(char));
			fscanf(f1, "%s", tab[i].types[k]);}
		psinst = calloc(tab[i].nb_pop,sizeof(*psinst));
		for (j = 0; j<tab[i].nb_pop;j++){
			/*psinst = calloc(tab[i].nb_pop,sizeof(*psinst));*/
			fscanf(f1, "%s" , psinst[j].symbole);
			printf("%s\n",psinst[j].symbole );
			fscanf(f1, "%s",psinst[j].type);
			fscanf(f1, "%d",&psinst[j].nb_op);
			printf("nb op : %d\n",psinst[j].nb_op);
			psinst[j].types = calloc(psinst[j].nb_op,sizeof(char));
			for (k = 0; psinst[j].symbole[k];k++)  psinst[j].symbole[k] = tolower(psinst[j].symbole[k]);
			for(k=0; k<psinst[j].nb_op; k++){
				psinst[j].types[k] = calloc(16,sizeof(char)) ;
				fscanf(f1, "%s", psinst[j].types[k]);printf("type : %s\n",psinst[j].types[k]);}

			tab[i].inst = psinst;
		}

	}
	printf("\n\n\n\n");

	for (i = 0;i<*p_nb_inst;i++) {
		printf("%s\n",tab[i].type);
		printf("%s\n", tab[i].symbole);
		printf("%d\n",tab[i].nb_op);
	}
	printf("START\n\n");
  for (i = 0;i<*p_nb_inst;i++) {
    printf("%s\n",tab[i].type);
    printf("%s\n", tab[i].symbole);
    printf("nombre de op%d\n",tab[i].nb_op);
    printf("nombre pop%d\n",tab[i].nb_pop);
    for (j = 0;j<tab[i].nb_pop;j++){
      printf("%s\n",tab[i].inst[j].symbole);
      printf("%s\n",tab[i].inst[j].type);
      printf("%d\n",tab[i].inst[j].nb_op);
      for (k = 0;k<tab[i].inst[j].nb_op;k++){
        printf("%s\n",tab[i].inst[j].types[k]);

      }
    }
  }
	printf("end lect pseudo dico\n\n" );
	*dict = tab;


	fclose(f1);
}
