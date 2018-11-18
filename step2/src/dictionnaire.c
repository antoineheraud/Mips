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




/* Charge le fichier dictionnaire nomFichierDico
 Retourne un pointeur sur le tableau dictionnaire
 stocke le nb d'instructions dans *p_nb_inst */
inst_def_t* lect_dico_int(char* nomFichierDico, int* p_nb_inst){	printf("1\n");
	FILE* f1 = NULL;
    int i;
	char s1[STRLEN];
	inst_def_t* tab;


	f1=fopen(nomFichierDico, "r");	printf("1\n");

	if(f1 == NULL){
		puts("Erreur d'ouverture du fichier source");
		return NULL;}
	if(fscanf(f1, "%d", p_nb_inst) != 1){
		puts("Erreur d'avoir le nombre d'instructions dans le fichier source");
		return NULL;}
	printf("10\n");printf("nombre op %d\n ", *p_nb_inst);
	tab=calloc(*p_nb_inst, sizeof(*tab));	printf("2\n");

	if(tab == NULL){
		puts("Erreur d'allocation du tableau");
		return NULL;}
	for(i=0; i< p_nb_inst; i++){
		if(fscanf(f1, "%s %c %d", s1, &(tab[i].type), &(tab[i].nb_op)) != 0){printf("baa\n");
			free(tab);
			puts("Erreur de scanner des éléments dans le fichier source");
			return NULL;}
		tab[i].symbole=strdup(s1);}
	printf("end\n" );
	fclose(f1);
	return tab;
}
