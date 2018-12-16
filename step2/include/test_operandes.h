#ifndef _TABLESYMB_H_
#define _TABLESYMB_H_

#include <stdio.h>

OPINST* tableau_de_operandes(IT lit);
int is_shift_amount_text(OPINST* f, int indice);
int is_immediate_text(OPINST* f, int indice);
long* tab_base_offset(OPINST* f, int indice);
int is_base_offset_text(OPINST* f, int indice);
int is_relatif_text(OPINST* f, int indice);
int is_absolu_text(OPINST* f, int indice);
