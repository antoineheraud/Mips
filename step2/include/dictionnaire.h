#ifndef _DICTIONNAIRE_H_
#define _DICTIONNAIRE_H_


#include <stdio.h>
#include <liste.h>




typedef struct{	char* symbole;
				char type;
				int nb_op;} inst_def_t;

inst_def_t* lect_dico_int(char* nomFichierDico, int* p_nb_inst);


#endif
