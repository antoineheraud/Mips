
/**
 * @file main.c
 * @author François Portet <francois.portet@imag.fr> from François Cayre
 * @brief Main entry point for MIPS assembler.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#include <global.h>
#include <notify.h>
#include <lex.h>
#include <liste.h>
#include <instruction.h>
#include <donneesdata.h>
#include <donneesbss.h>
#include <tablesymb.h>
#include <lecture.h>
#include <machine2.h>

/**
 * @param exec Name of executable.
 * @return Nothing.
 * @brief Print usage.
 *
 */
void print_usage( char *exec ) {         /*stderr? affiche Usage? */
    fprintf(stderr, "Usage: %s file.s\n",
            exec);
}



/**
 * @param argc Number of arguments on the command line.
 * @param argv Value of arguments on the command line.
 * @return Whether this was a success or not.
 * @brief Main entry point for MIPS assembler.
 *
 */
int main ( int argc, char *argv[] ) {



/*  LISTE lb = nouvliste();
  IT lit = calloc(1,sizeof(*lit));
  char inst = 'ADD';
  strcpy(lit->inst, inst);
  lit->nbop = 1;
  lit->line = 48;
  lit->dec = 12;
  OPINST opi = calloc(1,sizeof(*opi));
  opi->token = "7";
  opi->type = IMMEDIATE;
  lit->opt[0] =  opi;

  lb = entete(lb,lit);

  IT nlit = lb->val;
  printf("nbop : %d, line : %d, dec : %d", lit->nbop,lit->line,lit->dec);
*/


    unsigned int 	nlines 	= 0;
    char         	 *file 	= NULL;
    int i;


    /* exemples d'utilisation des macros du fichier notify.h */
    /* WARNING_MSG : sera toujours affiche */
    WARNING_MSG("Un message WARNING_MSG !");

    /* macro INFO_MSG : uniquement si compilé avec -DVERBOSE. Cf. Makefile*/
    INFO_MSG("Un message INFO_MSG : Debut du programme %s", argv[0]);

    /* macro DEBUG_MSG : uniquement si compilé avec -DDEBUG (ie : compilation avec make debug). Cf. Makefile */
    DEBUG_MSG("Un message DEBUG_MSG !");

    /* La macro suivante provoquerait l'affichage du message
       puis la sortie du programme avec un code erreur non nul (EXIT_FAILURE) */
    /* ERROR_MSG("Erreur. Arret du programme"); */


    /* test nombre d'argument (minimum 2) */
    if ( argc <2 ) {
        print_usage(argv[0]);
        exit( EXIT_FAILURE );
    }

    /* charge la valeur du dernier argument dans file */
    file  	= argv[argc-1];

    /* test si le dernier argument n'est pas vide ( aka bon fonctionnement de l'association nombre arguments
 / valeur argument */
    if ( NULL == file ) {
        fprintf( stderr, "Missing ASM source file, aborting.\n" );
        exit( EXIT_FAILURE );
    }

    LISTE listlex = nouvliste();
    LISTE* plistlex = &listlex;
    /* ---------------- do the lexical analysis -------------------*/
    lex_load_file( file, &nlines, plistlex );
    DEBUG_MSG("source code got %d lines",nlines);
    printf("\n\n\n\n\n");
    reverse(plistlex);
    printL(listlex);

    /* end lexical analysis */

    /* Incrément 2 machine à état non fonctionnelle */
    LISTE collect_ins;
    LISTE* pcollect_ins = &collect_ins;
    LISTE collect_data;
    LISTE* pcollect_data = &collect_data;
    LISTE collect_bss;
    LISTE* pcollect_bss = &collect_bss ;
    printf("Début Machine 2\n");
    inst_def_t* dict;
    int nb_inst;
    dict = lect_dico_int("./dic.txt", &nb_inst);printf("pff\n");
    printf("nombre op %d\n ", nb_inst);
    for (i = 0;i<nb_inst;i++) {printf("%s\n",dict[i].symbole);}

    machine_etat_2(listlex, pcollect_ins,  pcollect_data, pcollect_bss, dict,  &nb_inst);



    printL(listlex);
/* test collection instructions */
    LISTE lb = nouvliste();

      IT lit = calloc(1,sizeof(*lit));

      char inst1[40];

      strcpy(inst1,"ADD");

      strcpy(lit->obj, inst1);

      lit->nbop = 1;

      lit->line = 48;

      lit->dec = 12;

      OPINST opi = calloc(1,sizeof(*opi));
      strcpy(opi->token, "7");
      opi->type = IMMEDIATE;
      lit->opt[0] =  opi;

      lb = entete(lb,lit);

      IT nlit = lb->val;
      printf("nbop : %d, line : %d, dec : %d\n", lit->nbop,lit->line,lit->dec);

      printf("inst : %s\n",lit->obj);

      printf("op : %s\n",(lit->opt[0])->token);
/* fin test collection instructions */


    /* ---------------- Free memory and terminate -------------------*/

    /* TODO free everything properly*/

    exit( EXIT_SUCCESS );
}
