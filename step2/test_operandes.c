#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


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
		int nb_op = lit->nbop;
		if(nb_op == 0) return NULL;
		OPINST* f = calloc(nb_op, sizeof(*f));
		if(nb_op == 1){
		strcpy(f[1]->token, (char*)(lit->opt1)->token);
		f[1]->type = (TYPEOPINST)(lit->opt1)->type;}
		else if(nb_op == 2){
		strcpy(f[1]->token, (char*)(lit->opt1)->token);
		f[1]->type = (TYPEOPINST)(lit->opt1)->type;
		strcpy(f[2]->token, (char*)(lit->opt2)->token);
		f[2]->type = (TYPEOPINST)(lit->opt2)->type;}
		else if(nb_op == 3){
		strcpy(f[1]->token, (char*)(lit->opt1)->token);
		f[1]->type = (TYPEOPINST)(lit->opt1)->type;
		strcpy(f[2]->token, (char*)(lit->opt2)->token);
		f[2]->type = (TYPEOPINST)(lit->opt2)->type;
		strcpy(f[3]->token, (char*)(lit->opt3)->token);
		f[3]->type = (TYPEOPINST)(lit->opt3)->type;}
		return f;
}

int is_registre_text(OPINST* f, int indice){
    if(f[indice]->type != REGI) return 0;
    char** ptr;
    long a = strtol(f[indice]->token, ptr, 10);
    if((0 <= a) && (a <= 31)) return 1;
    return 0;
    }

int is_shift_amount_text(OPINST* f, int indice){
    if(f[indice]->type != SA) return 0;
    char** ptr;
    long a = strtol(f[indice]->token, ptr, 10);
    if((0 <= a) && (a <= 31)) return 1;
    return 0;
}

int is_immediate_text(OPINST* f, int indice){
    if(f[indice]->type != IMMEDIATE) return 0;
    char** ptr;
    long a = strtol(f[indice]->token, ptr, 10);
    if((-32768 <= a) && (a <= 32767)) return 1;
    return 0;
}

long* tab_base_offset(OPINST* f, int indice){
		char* start = f[indice]->token;
    char* end=start;
    char* token;
    int token_size=0;
    long* tab;
    char** ptr;
    while(isdigit(*end)) end = end +1; 				/*partie offset*/
		token_size=end-start;
		printf("Nombre de size de la partie offset de base offset %d", token_size);
    if(token_size>0){
		token = calloc(token_size+1,sizeof(*start));
		strncpy(token,start,token_size);
		token[token_size]='\0';}
		tab[0] = strtol(token, ptr, 10);
		end = end + 2;
		start = end;
		while(isdigit(*end)) end = end +1;		/*partie base*/
		token_size=end-start;
		printf("Nombre de size de la partie base de base offset %d", token_size);
		if(token_size>0){
		token	= calloc(token_size+1,sizeof(*start));
		strncpy(token,start,token_size);
		token[token_size]='\0';}
		tab[1] = strtol(token, ptr, 10);
		return tab;
}


int is_base_offset_text(OPINST* f, int indice){
    long* tab = tab_base_offset(f, indice);
    if(f[indice]->type != BASE_OFFSET) return 0;
    if((-32768 <= tab[0]) && (tab[0] <= 32767) && (0 <= tab[1]) && (tab[1] <= 31)) return 1;
		else return 0;
}

int is_relatif_text(OPINST* f, int indice){
		if(f[indice]->type != RELATIF) return 0;
		char** ptr;
    long a = strtol(f[indice]->token, ptr, 10);
    if((-32768 <= a) && (a <= 32767) && (a % 4 == 0)) return 1;
    else return 0;
}

int is_absolu_text(OPINST* f, int indice){
		if(f[indice]->type != RELATIF) return 0;
		char** ptr;
    long a = strtol(f[indice]->token, ptr, 10);
    if((-33554432 <= a) && (a <= 33554431) && (a % 4 == 0)) return 1;
    else return 0;
}
