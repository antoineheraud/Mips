#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>




typedef struct{	char symbole[STRLEN];
				char type[STRLEN];
				int nb_op;} inst_def_t;

typedef struct inst_def_t* pinst_def_t;

void lect_dico_int(char* nomFichierDico, int* p_nb_inst,pinst_def_t* dict);


#endif
