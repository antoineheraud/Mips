/**
 * @file lex.h
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexem-related stuff.
 *
 * Contains lexem types definitions, some low-level syntax error codes,
 * the lexem structure definition and the associated prototypes.
 */

#ifndef _LEX_H_
#define _LEX_H_


#include <stdio.h>
#include "liste.h"

enum type{
	ZERO,
	SYMB,
	DECIM,
	HEX,
	DIRECT,
	CHAIN,
	DEUX_P,
	REG,
	COMMENTS,
	VIRG,
	NLINE,
	P_GAU,
	P_DROI,
	NL
};

typedef enum type TYPE_L;

struct lexeme{
	TYPE_L type;
	char obj[STRLEN];
	int nline;
};
typedef struct lexeme* LEXEM;



void lex_read_line( char *line, int nline, LISTE *listlex);
void lex_load_file( char *file, unsigned int *nlines, LISTE *listlex);
char* getNextToken(char** token, char* current_line,int nline, LISTE *listlex);
LEXEM nouvlexeme(char* token, TYPE_L type, int nline);

#endif /* _LEX_H_ */
