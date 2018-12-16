
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
#include "lecture.h"
#include "dictionnaire.h"
#include "table_de_relocation.h"


typedef enum { INIT, DATA1, BSS1, TEXT } etat;

void machine_etat_2(LISTE listlex, LISTE* collect_ins, LISTE* collect_data, LISTE* collect_bss,LISTE* collect_symb,inst_def_t* dict, int* p_nb_inst,psinst_def_t* pseudo_dict, int* p_nb_pseudo_inst){

  etat S = INIT;
  LEXEM c = listlex->val;
  LISTE l1 = listlex->suiv;
  LEXEM c1 = NULL;
  if (l1 != NULL)  c1 = l1 ->val;
  /*printf("%s\n",c->obj);*/
  /* parametres communs des collections*/
  char token[STRLEN];
  char type[STRLEN];
  char typeR[STRLEN];
  int nbop;
  int line;
  int dec = 0;
  int decb = 0;
  int decbs = 0;
  int pinst;
  int* ppinst = &pinst;
  /* parametres de la collection d'instruction*/


  IT INST;

  /* parametres de la collection de donnees data*/
  OPDD operande;
  DATA DT;
  char data[STRLEN];

  /* parametres de la collection de donnees bss*/
  int valeur;
  BSS BS;
  char bss[STRLEN];

  int symb;
  int sdec;
  int sline;
  char symbole[STRLEN];
  LEXEM s;

  char lower[STRLEN];
  int i = 0;
  printf("%s\n", pseudo_dict[4].symbole);
  printf("mach\n");
  while(l1 != NULL){     printf("%s\n",c->obj);printtype(c->type);
  switch(S){
    case INIT:
    printf("init\n");
    if(c->type == COMMENTS|| c->type == NL) S = INIT;
    else if(!strcmp(c->obj, ".text"))	{S = TEXT;printf("Text\n");}
    else if(!strcmp(c->obj, ".data"))	{S = DATA1;printf("data1\n");}
    else if(!strcmp(c->obj, ".bss"))	{S = BSS1;printf("bss1\n");}
    /*  else if(c1->obj == ':') { S = ETI;printf("etiquette\n")}   */
    break;

    case TEXT:printf("Text\n");/*printf("%s\n",c->obj);*/


    /* fonction pour passer le token en minuscule */
    for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
    /*printf("%s\n",c->obj);*/

    if(!strcmp(c->obj, ".data")){ S = DATA1;line = line+1;printf("1if\n");}

    else  if(!strcmp(c->obj, ".bss")){ S = BSS1;line = line+1;printf("1eif\n");break;}
    else if(!strcmp(c->obj, "\0")) {printf("nl\n");line = line+1;break;}
    else if(!strcmp(c1->obj, ":")) {strcpy(typeR, "NULL");
      printf("nul\n" );
      lecture_etiquette(typeR,c,&line ,&dec, ".text",collect_symb);
      listlex = listlex->suiv;
    }
    else{printf("traitement\n");pinst = 0;symb = 0;
    OPINST opt1 = calloc(1,sizeof(*opt1));/* printf("%p\n",opt1);*/
    OPINST opt2 = calloc(1,sizeof(*opt2));/*printf("%p\n",opt2);*/
    OPINST opt3 = calloc(1,sizeof(*opt3));/*printf("%p\n",opt3);printf("%p\n",&opt3);*/

    listlex=lecture_instruction(typeR,&sdec,&symb,&s ,collect_ins,ppinst, token, type, &nbop, &line, &dec, &opt1,&opt2,&opt3, listlex, dict, p_nb_inst, pseudo_dict, p_nb_pseudo_inst);
    printf("lecture\n");printf("pinst vaut : %d\n",pinst);
    /*printf("%s \n",opt[0].token);*/
    /*printf("%s\n",(opt1)->token);*/
    /*control fonctionnement lecture_instruction */
    /*printf("%s %s %d %d %d\n",token,type,nbop,line,dec);*/
    if (symb == 1){ lecture_etiquette(typeR,s,&sline,&sdec,".text",collect_symb);}
    if (pinst == 0){printf("pinst = 0\n");
    INST = nouvinst(token, type, nbop, line, dec, opt1,opt2,opt3);
    /*printf("op : %s\n",(INST->opt1)->token);
    printf("inst\n");
    /*control fonctionnement nouvinst */
    printf("nbop : %d, line : %d, dec : %d\n", INST->nbop,INST->line,INST->dec);

    printf("inst : %s\n",INST->obj);
    if (nbop>0){
      printf("op : %s\n",(INST->opt1)->token);
      TYPEOPINST typeop = (INST->opt1)->type;
      printtypeI(typeop);
    }
    if (nbop>1){
      printf("op : %s\n",(INST->opt2)->token);
      TYPEOPINST typeop = (INST->opt2)->type;
      if (typeop == REGI) printf("REGI\n");
      if (typeop == ETIQ) printf("ETIQ\n");
      if (typeop == SA) printf("SA\n");
      if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");}

      if(nbop>2){
        printf("op : %s\n",(INST->opt2)->token);
        TYPEOPINST typeop = (INST->opt2)->type;
        if (typeop == REGI) printf("REGI\n");
        if (typeop == ETIQ) printf("ETIQ\n");
        if (typeop == SA) printf("SA\n");
        if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");}

        /* fin du control */

        *collect_ins = entete(*collect_ins, INST);
        printf("entete\n");
        /*  for(i = 0; i<nbop;i++){printf("op : %s\n",(INST->opt[i])->token);
        TYPEOPINST typeop = (INST->opt[i])->type;
        if (typeop == REGI) printf("REGI\n");
        if (typeop == ETIQ) printf("ETIQ\n");
        if (typeop == SA) printf("SA\n");
        if (typeop == IMMEDIATE) printf ("IMMEDIATE\n");
      }*/}
      if (pinst != 0){printf("pinst != 0\n");
      listlex=lecture_instruction(typeR,&sdec,&symb,&s,collect_ins,ppinst, token, type, &nbop, &line, &dec, &opt1,&opt2,&opt3, listlex, dict, p_nb_inst, pseudo_dict, p_nb_pseudo_inst);

    }line = line+1;
  }
  line = line+1;
  break;

  case DATA1:printf("data1\n");printf("%s\n",c->obj);
  for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
  printf("%s\n",c->obj);
  if(!strcmp(c->obj, ".text")) {S = TEXT;line = line+1;}
  else if(!strcmp(c->obj, ".bss")) {S = BSS1;line = line+1;}
  else if(!strcmp(c->obj, "\0")) {printf("nl\n");line = line+1;break;}
  else if(!strcmp(c1->obj, ":")) {
    printf("eti\n" );
    lecture_etiquette(typeR,c, &line, &decb, ".data",collect_symb);
    listlex = listlex->suiv;
  }
  else{printf("traitement\n");symb = 0;
  OPDD operande = calloc(1,sizeof(*operande));
  if (!strcmp(c->obj, ".word")){ printf("OUF");}
  listlex= lecture_data(typeR,&sdec,&symb,&s,data,/* type,*/ &nbop, &line, &decb, operande, listlex);
  printf("pff");
  if (symb == 1){ lecture_etiquette(typeR,s,&sline,&sdec,".data",collect_symb);}
  DT = nouvdata(data, /*type,*/ nbop, line, decb, operande);
  *(collect_data) = entete(*(collect_data), DT);}
  break;

  case BSS1:printf("bss1\n");printf("%s\n",c->obj);
  for (i = 0; c->obj[i];i++)  c->obj[i] = tolower(c->obj[i]);
  printf("%s\n",c->obj);
  if(!strcmp(c->obj, ".text")) {S = TEXT;line = line+1;}
  else if(!strcmp(c->obj, ".data")) {S = DATA1;line = line+1;}
  else if(!strcmp(c->obj, "\0")) {printf("nl\n");line = line+1;break;}
  else if(!strcmp(c1->obj, ":")) {
    printf("obj : %s\n",c->obj );
    lecture_etiquette(typeR,c, /*type,*/ &line, &decbs, ".bss",collect_symb);
    listlex = listlex->suiv;
  }
  else{
    BSS BS = calloc(1,sizeof(*BS));
    listlex = lecture_bss(bss, /*type,*/ &nbop, &line, &decbs, &valeur, listlex);
    printf("nouv\n");
    BS = nouvbss(bss, /*type,*/ nbop, line, decbs, valeur);

    (*collect_bss) = entete((*collect_bss), BS);}
    printf("entete\n");
    break;


  }
  listlex = listlex->suiv;

  if (listlex == NULL) break;
  c = listlex->val;

  l1 = listlex->suiv;
  if (l1 != NULL)  c1 = l1 ->val;
  printf("%s\n",c->obj);printtype(c->type);
}
}


void lecture_etiquette(char* typeR,LEXEM s,int* line,int* dec, char* section, LISTE* collect_symb){
  TS leti = calloc(1,sizeof(*leti));
  printf("lect etiq\n");
  strcpy(leti->etiq, s->obj);
   strcpy(leti->type,typeR);

/*  if (!strcmp(typeR,"IMMEDIATE")) leti->type_rel = R_MIPS_LO16
  if (!strcmp(typeR,"ABS")) leti->type_rel = R_MIPS_26;
  if (!strcmp(typeR,"R_MIPS_32")) leti->type_rel = R_MIPS_LO16;
  if (!strcmp(typeR,"BASE_OFFSET")) leti->type_rel = BASE_OFFSET;*/
  strcpy(leti->section, section);
  leti->line = s->nline;
  leti->dec = *dec;
  *collect_symb = entete((*collect_symb),leti);

}

void machine_3eme_passe(LISTE* table_relocT,LISTE* table_relocD,LISTE listlex, LISTE collect_ins, LISTE collect_data, LISTE collect_bss,LISTE collect_symb){
  /*LISTE collect_ins = collect_ins;*/
  printf("coucou\n");
  LISTE Lsymb = collect_symb;
  LISTE Lsymb2 = collect_symb;
  TS nsymb = Lsymb->val;
  TS nsymb2;
  TS nsymb3;
  TS TRsymb;
  tabrel TR;
  int compteur = 0;
  while(Lsymb != NULL ){printf("bouvle\n");
    nsymb = Lsymb->val;printf("%d\n",nsymb->dec );printf("premiere boucle%s  %d %d\n",nsymb->etiq,nsymb->dec,nsymb->line );
    if (nsymb->dec == -1){printf(" appel\n");printf("a relocer %s  %d\n",nsymb->etiq,nsymb->dec);Lsymb2 = collect_symb;
      if(!strcmp(nsymb->section,".text")){printf("text\n");compteur = 0;
        while (Lsymb2 != NULL){
          nsymb2 = Lsymb2->val;
          printf("while : 1 : %s ; 2 : %s dec : %d\n", nsymb->etiq, nsymb2->etiq, nsymb2->dec);
          if(!strcmp(nsymb->etiq,nsymb2->etiq)&& nsymb2->dec != -1){printf("RELOCATION %s\n",nsymb->section);
            compteur = 1;
            nsymb3 = calloc(1,sizeof(*nsymb3));
            strcpy(nsymb3->etiq,nsymb->etiq);strcpy(nsymb3->type,nsymb->type);nsymb3->line = nsymb->line;
            strcpy(nsymb3->section,nsymb->section);nsymb3->adresserel=nsymb->adresserel;
            nsymb3->dec = nsymb2->dec;
            TR = charger_table_de_relocation_text(nsymb3,nsymb3);
            *table_relocT = entete((*table_relocT),TR);
          }

        Lsymb2 = Lsymb2->suiv;
        }
        if (compteur == 0){
          TR = charger_table_de_relocation_text(nsymb,nsymb);
          *table_relocT = entete((*table_relocT),TR);
        }
      }
      if(!strcmp(nsymb->section,".data")){printf("data\n");compteur = 0;
        while (Lsymb2 != NULL){nsymb2 = Lsymb2->val;
          if(!strcmp(nsymb->etiq,nsymb2->etiq)&& nsymb2->dec != -1){printf("RELOCATION %s\n",nsymb->section);
            compteur = 1;
            nsymb3 = calloc(1,sizeof(*nsymb3));
            strcpy(nsymb3->etiq,nsymb->etiq);strcpy(nsymb3->type,nsymb->type);nsymb3->line = nsymb->line;
            strcpy(nsymb3->section,nsymb->section);nsymb3->adresserel=nsymb->adresserel;
            nsymb3->dec = nsymb2->dec;
            TR = charger_table_de_relocation_data(nsymb3,nsymb3);
            *table_relocD = entete((*table_relocD),TR);
          }
          Lsymb2 = Lsymb2->suiv;
        }
        if (compteur == 0){
          TR = charger_table_de_relocation_data(nsymb,nsymb);
          *table_relocD = entete((*table_relocD),TR);
        }
      }
    }
    Lsymb = Lsymb->suiv;
  }

  /* fin chargement tables de relocation*/
  /*while( collect_symb != NULL){
  if (nsymb->dec == -1){

}
}*/printf("finreloc\n");
}
