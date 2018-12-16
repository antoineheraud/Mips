
/**
* @file main.c
* @author François Portet <francois.portet@imag.fr> from François Cayre
* @brief Main entry point for MIPS assembler.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "table_de_relocation.h"
#include "machine2.h"
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
  int j;


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
  printLex(listlex);

  /* end lexical analysis */

  /* Incrément 2 machine à état non fonctionnelle */
  LISTE collect_ins=NULL;
  LISTE* pcollect_ins = &collect_ins;
  LISTE collect_data=NULL;
  LISTE* pcollect_data = &collect_data;
  LISTE collect_bss=NULL;
  LISTE* pcollect_bss = &collect_bss ;
  LISTE collect_symb=NULL;
  LISTE* pcollect_symb = &collect_symb;
  LISTE table_relocT = NULL;
  LISTE* ptable_relocT = &table_relocT;
  LISTE* table_relocD = NULL;
  LISTE* ptable_relocD = &table_relocD;

  inst_def_t* dict;
  inst_def_t** pdict = &dict;
  psinst_def_t* pseudo_dict;
  psinst_def_t** p_pseudo_dict = &pseudo_dict;

  int nb_inst;
  int nb_pseudo_inst;
  printf("lect dico\n" );
  lect_dico_int("./dic.txt", &nb_inst, pdict);
  printf("lect pseudo dico\n" );
  lect_pseudo_dic("./pseudo_dict.txt", &nb_pseudo_inst, p_pseudo_dict);
  printf("nombre de op %d\n ", nb_inst);
  for (i = 0;i<nb_pseudo_inst;i++) {
    printf("%s\n",pseudo_dict[i].type);
    printf("%s\n", pseudo_dict[i].symbole);
    printf("%d\n",pseudo_dict[i].nb_op);
  }
  printf("\n\n\n\n");
  for (i = 0;i<nb_inst;i++) {
    printf("%s\n", dict[i].symbole);

    printf("%s\n",dict[i].type);

    printf("%d\n",dict[i].nb_op);
    for (j = 0;j<dict[i].nb_op;j++) {
      printf("%s\n",dict[i].types[j]);
    }
  }
  printf("Début Machine 2\n");
  if( !strcmp(dict[27].symbole, "LI")) printf("Good\n");
  machine_etat_2(listlex, pcollect_ins,  pcollect_data, pcollect_bss, pcollect_symb, dict,  &nb_inst, pseudo_dict, &nb_pseudo_inst);
  printf("\nfinmachine à état\n\n");
  reverse(pcollect_ins);
  printf("reverse\n");
  printLINST(collect_ins);

  printf("FIN\n");
  reverse(pcollect_data);
  printf("reverse\n");
  PrintLdata(collect_data);
  printf("FIN\n");
  reverse(pcollect_bss);
  printf("reverse\n");
  PrintLbss(collect_bss);
  printf("FIN\n");
  reverse(pcollect_symb);
  printf("reverse\n");
  print_etiquette(collect_symb);

  machine_3eme_passe(ptable_relocT,ptable_relocD,listlex, collect_ins,collect_data,collect_bss,collect_symb);
  reverse(ptable_relocD);
  reverse(ptable_relocT);
  Printtable_reloc(table_relocT);
  Printtable_reloc(table_relocD);



  printf("FIN\n");



  /* ---------------- Free memory and terminate -------------------*/

  /* TODO free everything properly*/

  exit( EXIT_SUCCESS );
}
