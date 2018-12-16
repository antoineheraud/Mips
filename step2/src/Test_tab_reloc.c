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
#include "table_de_relocation.h"


tabrel charger_table_de_relocation_text(void* ptabsym,TS tabsym){
	tabrel tabreloc = calloc(1,sizeof(*tabreloc));													/*fonction qui gère et classifie les étiquettes dans la table de symboles*/
			/*cette fonction crée la table de relocation TEXT*/
		strcpy(tabreloc->section , tabsym->section);				/*le nom de la section du tableau de relocation*/
		tabreloc->adresse = tabsym->dec;				/*l'adresse du tableau de relocation = son décalage dans la table de symboles*/
		/*il faut que le décalage soit positif, regarder la fonction lecture de 2 collections
		correspondantes*/
		tabreloc->psymbol = ptabsym;
							/*pointeur pointe vers la case correspondant dans la table de symboles*/
		return tabreloc;
	}



	tabrel charger_table_de_relocation_data(void* ptabsym,TS tabsym){
		tabrel tabreloc = calloc(1,sizeof(*tabreloc));														/*fonction qui gère et classifie les étiquettes dans la table de symboles*/
				/*cette fonction crée la table de relocation DATA*/
			strcpy(tabreloc->section , tabsym->section);				/*le nom de la section du tableau de relocation*/
			tabreloc->adresse = tabsym->dec;				/*l'adresse du tableau de relocation = son décalage dans la table de symboles*/
			/*il faut que le décalage soit positif, regarder la fonction lecture de 2 collections
			correspondantes*/
			tabreloc->psymbol = ptabsym;
							/*pointeur pointe vers le case correspondant dans la table de symboles*/
			return tabreloc;
		}




		TS erreur_table_de_relocation(LISTE TBR, char eti[STRLEN]){				/*fonction qui cherche si une étiquette existe ou non*/
			TS pts;																/*pointeur sur la case de l'étiquette indiquée*/
			if(TBR == NULL) return NULL;					/*si table symbole est vide, pas d'étiquettes*/
			while(TBR != NULL){
				pts = TBR->val;
				if(!strcmp(pts->etiq, eti))	return pts;				/*retourner l'adresse de cette étiquette dans la table de symboles*/
				TBR = TBR->suiv;
			}
			return NULL;																								/*retourner NULL car l'étiquette n'existe pas*/
		}
