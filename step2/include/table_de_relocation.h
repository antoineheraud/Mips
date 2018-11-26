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
	char nom[STRLEN];					/*nom de l'étiquette déclarée dans la table des symboles*/
	unsigned int adresse;					/*le décalage correspondant*/
	/*type type_rel;						/*type de relocation selon l'énumération précédente*/
	void* psymbol;
	struct table_de_relocation* suiv; 			/*l'élément suivant dans la table de relocation*/
}

typedef struct table_de_relocation tabrel;



#endif
