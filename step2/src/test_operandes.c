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
#include "test_operandes.h"

OPINST* tableau_de_operandes(IT lit){
		OPINST* f;
		f[1].token = (char)(lit->opt1).token;
		f[1].type = (TYPEOPINST)(lit->opt1).type;
		f[2].token = (char)(lit->opt2).token;
		f[2].type = (TYPEOPINST)(lit->opt2).type;
		f[3].token = (char)(lit->opt3).token;
		f[3].type = (TYPEOPINST)(lit->opt3).type;
		return f;
}

int is_registre_text(OPINST* f, int indice){
    if(f[indice].type != REGI) return 0;
    char** ptr;
    long a = strtol(f[indice].token, ptr, 10);
    if((0 <= a) && (a <= 31)) return 1;
    return 0;
    }

int is_shift_amount_text(OPINST* f, int indice){
    if(f[indice].type != SA) return 0;
    char** ptr;
    long a = strtol(f[indice].token, ptr, 10);
    if((0 <= a) && (a <= 31)) return 1;
    return 0;
}

int is_immediate_text(OPINST* f, int indice){
    if(f[indice].type != IMMEDIATE) return 0;
    char** ptr;
    long a = strtol(f[indice].token, ptr, 10);
    if((-32768 <= a) && (a <= 32767)) return 1;
    return 0;
}

