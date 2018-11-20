#include <stdio.h>
#include <string.h>


#include "global.h"
#include "notify.h"
#include "liste.h"
#include "instruction.h"
#include "donneesdata.h"
#include "donneesbss.h"
#include "tablesymb.h"
#include "dictionnaire.h"

/* regroupe les fonctions qui conercnent les 3 collections */

IT nouvinst(char* token, char* type, int nbop, int nline, int dec, OPINST* opt);
LISTE lecture_instruction(char* token, char* type, int* nbop, int* nline, int* dec, OPINST opt[], LISTE l,inst_def_t* dict, int* p_nb_inst);
DATA nouvdata(char* data,char* type, int nbop, int line, int dec, OPDD operande);
LISTE lecture_data(char* data, char* type, int nbop, int line, int dec, OPDD operande, LISTE l);
BSS nouvbss(char* bss, char* type, int nbop, int line, int dec,int valeur);
LISTE lecture_bss(char* bss, char* type, int nbop, int line, int dec, int valeur, LISTE l);
