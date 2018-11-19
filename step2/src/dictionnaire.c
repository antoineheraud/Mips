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




/* Charge le fichier tabionnaire nomFichierDico
 Retourne un pointeur sur le tableau tabionnaire
 stocke le nb d'instructions dans *p_nb_inst */
void lect_dico_int(char* nomFichierDico, int* p_nb_inst,pinst_def_t* dict){
	FILE* f1 = NULL;
    int i;
	char s1[STRLEN];



	f1=fopen(nomFichierDico, "r");	printf("1\n");

	if(f1 == NULL){
		puts("Erreur d'ouverture du fichier source");
		}
	if(fscanf(f1, "%d", p_nb_inst) != 1){
		puts("Erreur d'avoir le nombre d'instructions dans le fichier source");
	}
	printf("10\n");printf("nombre op %d\n ", *p_nb_inst);printf("2\n");
	inst_def_t tab[*p_nb_inst];
	*dict = tab;
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

	/*if( !strcmp(tab[27].symbole, "LI")) printf("Good\n");*/

	fclose(f1);
}
