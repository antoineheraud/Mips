
/**
 * @file lex.c
 * @author François Portet <francois.portet@imag.fr>
 * @brief Lexical analysis routines for MIPS assembly syntax.
 *
 * These routines perform the analysis of the lexeme of an assembly source code file.
 */

#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include <global.h>
#include <notify.h>
#include <lex.h>
#include <liste.h>


/*definition des etats*/
enum{
     INIT,
     SYMBOLE,
     NLI,
     DEUX_PTS,
     DIRECTIVE,
     REGISTRE,
     DECIMAL_ZERO,
     HEXA,
     DECIMAL,
     VIRGULE,
     CHAINE,
     COMMENT,
     BREAK,
     ERREUR,
     P_G,
     P_D
};

/* test si virgule */
int iscommas( char start){
	if (start == ',') return 1;
	else return 0;
}

int isjump( char start){
	char jump = "\r\n";
	if (start == jump) return 1;
	else  return 0;
}

int isgui( char start){
	if (start == '"') return 1;
	else return 0;
}



/* ATTENTION: getNextToken est juste un exemple -> il est à recoder completement !!! */
/**
 * @param token The pointeur to the lexeme to be extracted.
 * @param current_line The address from which the analysis must be performed.
 * @return the address at which the analysis stopped or NULL if the analysis is terminated.
 * @brief This function get an input line, extracts a token from it and return the pointeur to the next place where the analysis should continue.
 */

/* note that MIPS assembly supports distinctions between lower and upper case*/

/* plus l'original */
char* getNextToken(char** token, char* current_line,int nline, LISTE *listlex) {
    char* start = current_line;
    char* end=NULL;
    int token_size=0;
    TYPE_L type = ZERO;
    int S = INIT;

    /* check input parameter*/
    if (current_line ==NULL) return NULL;

    if (*start == '\0'){
        type = NL;
        *token = calloc(2,sizeof(*start));
        strcpy(*token,"\0");
        LEXEM lexeme = nouvlexeme(*token, NL, nline);
      /*  *listlex = enchaine(*listlex,lexeme); */
    		*listlex = entete(*listlex, lexeme);
    		return end;
      }
    /* eats any blanks before the token*/
    while (*start!='\0' && isblank(*start) ){
	start++;
    }

    /*if ( *start!=',' && *start!='\n' && *start!='"') {*/

    	/* go till next blank or end*/
    	end=start;


    	while (*(end)!='\0' || end==start+1 /*&& !isblank(*end) && !iscommas(*end) && !isjump(*end) */){ /*printf("nul\n");*/
/*mise en oeuvre de l'automate*/
	switch(S){
		case INIT:
			if(isdigit(*end)) {
				if (*end == '0') S= DECIMAL_ZERO;
				else S = DECIMAL ;
			}
			else if(*end == '$') S = REGISTRE;
               		else if(isalpha(*end))S = SYMBOLE;
               		else if(isgui(*end)) S = CHAINE;
			else if(*end == '.') S = DIRECTIVE;
			else if(*end == '#') {start++;S = COMMENT;}
			else if(*end == '-') S = DECIMAL;
      else if(*end == '(') S = P_G;
      else if(*end == ')') S = P_D;
			else S = ERREUR;
			break;
		case DECIMAL_ZERO:
			if ( *end == 'x' || *end == 'X') S = HEXA;
			else if (isdigit(*end)) S = DECIMAL;
			/*	else S = ERREUR;*/


			break;
		case HEXA:
			if (isxdigit(*end)) {
				S = HEXA;
				type = HEX;
				if (!isxdigit(*(end+1))) S = BREAK;
			}
			/*else S = ERREUR;*/
      else if(*end == '(') S = P_G;
			break;
		case DECIMAL:
			type = DECIM;
			if (isdigit(*end)) {
				S = DECIMAL;
				type = DECIM;
				if (!isdigit(*(end+1))) S = BREAK;
			}
			else if (!isdigit(*(end+1))){
				S = BREAK;
				type = DECIM;
				end--;
			}
			/*else S = ERREUR; */
			break;
		case REGISTRE:
			if (isdigit(*end) || isalpha(*end)){
				S = REGISTRE;
				type = REG;
				if (ispunct(*(end+1)) || isblank(*(end+1))) S = BREAK;
			}

			else S = ERREUR;
			break;
		case CHAINE:
			S = CHAINE;
			if (isgui(*end)) S = BREAK;
			else if (*end == '\"') end++;
			S = CHAINE;
			type = CHAIN;

			break;
		/*case DEUX_PTS:
			type = DEUX_P;
			S = BREAK;
			end--;
			break;*/
		case SYMBOLE:
			type = SYMB;
			if (isalpha(*end) || isdigit(*end)){
				S = SYMBOLE;
			}
			else if ( ispunct(*end) || isblank(*end)){
				S = BREAK;
				end= end-1;
			}
			else S = ERREUR;
			break;
		case COMMENT:
			S = COMMENT;
			type = COMMENTS;
			if (isjump(*end)) {
				S = BREAK;
			}

			break;
		case DIRECTIVE:
			if(isalpha(*end)){
				S = DIRECTIVE;
				type = DIRECT;
			}
			else S = BREAK;
			break;
		case ERREUR:
		/*	printf("good");*/
    	WARNING_MSG("Erreur à la ligne %s", current_line);
      S = BREAK;
			/*printf("noob");*/
			break;
    case P_G:
      type = P_GAU;
      S = BREAK;
      end --;
      break;
    case P_D:
      type = P_DROI;
      S = BREAK;
      end --;
      break;



	}
	end++;

	if (S == BREAK) break;

    }

	if (*start==',' ){
		end = start+1;
		type = VIRG;
		}
	if (*start==':' ){
		end = start+1;
		type = DEUX_P;
		}

    /*compute size : if zero there is no more token to extract*/
    	token_size=end-start;
    	if (token_size>0){
		*token 	= calloc(token_size+1,sizeof(*start));
		strncpy(*token,start,token_size);
		(*token)[token_size]='\0';

		LEXEM lexeme = nouvlexeme(*token, type, nline);
  /*  *listlex = enchaine(*listlex,lexeme); */
		*listlex = entete(*listlex, lexeme);
		return end;
    	}

    	return NULL;
}




/**
 * @param line String of the line of source code to be analysed.
 * @param nline the line number in the source code.
 * @return should return the collection of lexemes that represent the input line of source code.
 * @brief This function performs lexical analysis of one standardized line.
 *
 */
void lex_read_line( char *line, int nline, LISTE *plistlex) {
    char* token = NULL;
    char* current_address=line;
    LEXEM lexeme;




    while( (current_address= getNextToken(&token, current_address, nline, plistlex)) != NULL){
	LISTE listlex1 = *plistlex;
        lexeme = listlex1->val;
	/*if (lexeme->type == COMMENTS) printf("COMMENT \n");
	if (lexeme->type == DIRECT) printf("DIRECTIVE \n");
	if (lexeme->type == CHAIN) printf("CHAIN \n");
	if (lexeme->type == SYMB) printf("SYMBOLE \n");
	if (lexeme->type == DECIM) printf("DECIMALE \n");
	if (lexeme->type == HEX) printf("HEXA \n");
	if (lexeme->type == REG) printf("REGISTRE \n");
	if (lexeme->type == DEUX_P) printf("DEUX_POINTS\n");
	if (lexeme->type == VIRG) printf("VIRGULE \n");
	if (lexeme->type == NL) printf("NOUVELLE LIGNE \n");*/
        /*puts(token);*/
/*	printf("%s \n",lexeme->obj */

    }

    return;
}

/**
 * @param file Assembly source code file name.
 * @param nlines Pointer to the number of lines in the file.
 * @return should return the collection of lexemes
 * @brief This function loads an assembly code from a file into memory.
 *
 */
void lex_load_file( char *file, unsigned int *nlines,LISTE *listlex) {

    FILE        *fp   = NULL;
    char         line[STRLEN]; /* original source line */



    fp = fopen( file, "r" );
    if ( NULL == fp ) {
        /*macro ERROR_MSG : message d'erreur puis fin de programme ! */
        ERROR_MSG("Error while trying to open %s file --- Aborts",file);
    }

    *nlines = 0;

    while(!feof(fp)) {

        /*read source code line-by-line */
        if ( NULL != fgets( line, STRLEN-1, fp ) ) {
            line[strlen(line)-1] = '\0';  /* eat final '\n' */
            (*nlines)++;

            if ( 0 != strlen(line) ) {
                lex_read_line(line,*nlines, listlex);
            }
        }
    }

    fclose(fp);
    return;
}

LEXEM nouvlexeme(char* token, TYPE_L type, int nline){
	LEXEM l = calloc(1,sizeof(*l));
	l->type = type;
	strcpy(l->obj, token);
	l->nline = nline;
	return l;
}
