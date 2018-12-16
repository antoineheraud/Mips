#ifndef _TEST_OPERANDES_H_
#define _TEST_OPERANDES_H_

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

OPINST* tableau_de_operandes(IT lit);
int is_registre_text(OPINST* f, int indice);
int is_shift_amount_text(OPINST* f, int indice);
int is_immediate_text(OPINST* f, int indice);
long* tab_base_offset(OPINST* f, int indice);
int is_base_offset_text(OPINST* f, int indice);
int is_relatif_text(OPINST* f, int indice);
int is_absolu_text(OPINST* f, int indice);




#endif
