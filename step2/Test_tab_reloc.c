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


tabrel charger_table_de_relocation_text(TS tabsym){		
	tabrel tabreloc;														/*fonction qui gère et classifie les étiquettes dans la table de symboles*/
	tabrel tabreloc1 = tabreloc;
	while(tabsym != NULL){
		if(!strcmp(tabsym->section, "TEXT"){			/*cette fonction crée la table de relocation TEXT*/ 
			tabreloc->nom = tabsym->section;				/*le nom de la section du tableau de relocation*/ 
			tabreloc->adresse = tabsym->dec;				/*l'adresse du tableau de relocation = son décalage dans la table de symboles*/
																							/*il faut que le décalage soit positif, regarder la fonction lecture de 2 collections 
																							  correspondantes*/
			tabreloc->psymbol = tabsym;							/*pointeur pointe vers la case correspondant dans la table de symboles*/
			tabreloc = tabreloc->suiv;
		}
			tabsym = tabsym->suiv;
	}
		tabreloc->suiv = NULL;
		return tabreloc1;
}


tabrel charger_table_de_relocation_data(TS tabsym){		
	tabrel tabreloc;														/*fonction qui gère et classifie les étiquettes dans la table de symboles*/
	tabrel tabreloc1 = tabreloc;
	while(tabsym != NULL){
		if(!strcmp(tabsym->section, "DATA"){			/*cette fonction crée la table de relocation DATA*/ 
			tabreloc->nom = tabsym->section;				/*le nom de la section du tableau de relocation*/ 
			tabreloc->adresse = tabsym->dec;				/*l'adresse du tableau de relocation = son décalage dans la table de symboles*/
																							/*il faut que le décalage soit positif, regarder la fonction lecture de 2 collections 
																							  correspondantes*/
			tabreloc->psymbol = tabsym;							/*pointeur pointe vers le case correspondant dans la table de symboles*/
			tabreloc = tabreloc->suiv;
		}
			tabsym = tabsym->suiv;
	}
		tabreloc->suiv = NULL;
		return tabreloc1;
}
	
		
		
TS erreur_table_de_relocation(tabrel tabreloc, char eti[STRLEN]){				/*fonction qui cherche si une étiquette existe ou non*/
	TS pointeur;																/*pointeur sur la case de l'étiquette indiquée*/
	while(tabreloc != NULL){	
		pointeur = tabreloc->psymbol; 
		if(!strcmp(pointeur->etiq, eti))	return pointeur;				/*retourner l'adresse de cette étiquette dans la table de symboles*/
		tabreloc = tabreloc->suiv;
	}
	return NULL;																								/*retourner NULL car l'étiquette n'existe pas*/
}
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
