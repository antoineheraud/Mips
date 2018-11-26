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

int is_registre_text(IT lit, int indice);
int is_shift_amount_text(IT lit, int indice);
int is_immediate_text(IT lit, int indice);




#endif
