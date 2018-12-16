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
#include "table_de_relocation.h"



void machine_3eme_passe(LISTE listlex, LISTE collect_ins, LISTE collect_data, LISTE collect_bss,LISTE collect_symb){
  /*LISTE collect_ins = collect_ins;*/
  /*LISTE Lreloc = NULL;
  tabrel TBR;
  Lreloc = entete(Lreloc, TBR);*/
  LISTE Lsymb = collect_symb;
  TS nsymb = Lsymb->val;
  
  while(collect_symb != NULL ){
    nsymb = Lsymb->val;
    if (nsymb->dec != -1){
      if(!strcmp(nsymb->section,".text")){
        charger_table_de_relocation_text(nsymb);
      }
      if(!strcmp(nsymb->section,".data")){
        charger_table_de_relocation_data(nsymb);
      }
      if(!strcmp(nsymb->section,".bss")){
      /*  charger_table_de_relocation_bss(nsymb);*/
      }
    }
    collect_ins = collect_ins->suiv;
  }
  /* fin chargement tables de relocation*/
  /*while( collect_symb != NULL){
    if (nsymb->dec == -1){

    }
  }*/
}
