#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>



typedef struct{	char symbole[STRLEN];
				char type[STRLEN];
				int nb_op;
				char** types;
				} inst_def_t;

typedef struct inst_def_t* instp_def_t;

void lect_dico_int(char* nomFichierDico, int* p_nb_inst,inst_def_t** dict);

typedef struct{ char symbole[STRLEN];
	char type[STRLEN];
	int nb_op;
	int nb_pop;
	char** types;
	inst_def_t* inst;
} psinst_def_t;

typedef struct psinst_def_t* ppsinst_def_t;

void lect_pseudo_dic(char* nomFichierDico, int* p_nb_inst,psinst_def_t** dict);

#endif
