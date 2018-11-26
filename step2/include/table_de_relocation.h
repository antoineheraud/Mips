#ifndef _TABLE_DE_RELOCATION_H_
#define _TABLE_DE_RELOCATION_H_


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


/*enum type{R_MIPS_32=2, R_MIPS_26=4, R_MIPS_HI16=5, R_MIPS_LO16=6};*/

struct table_de_relocation{
	char nom[STRLEN];					/*nom de la section, soit .text soit .data*/
	unsigned int adresse;					/*le décalage correspondant*/
	/*type type_rel;					/*type de relocation selon l'énumération précédente*/
	void* psymbol;						/*pointeur vers l'étiquette ou le symbole dans la table des symboles*/
	struct table_de_relocation* suiv; 			/*l'élément suivant dans la table de relocation*/
}

typedef struct table_de_relocation tabrel;

tabrel charger_table_de_relocation_text(TS tabsym);
tabrel charger_table_de_relocation_data(TS tabsym);
TS erreur_table_de_relocation(tabrel tabreloc, char eti[STRLEN]){


#endif
