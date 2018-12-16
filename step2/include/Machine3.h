#ifndef _MACHINE2_H_
#define _MACHINE2_H_




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
#include "dictionnaire.h"


void machine_3eme_passe(LISTE listlex, LISTE collect_ins, LISTE collect_data, LISTE collect_bss,LISTE collect_symb);

#endif