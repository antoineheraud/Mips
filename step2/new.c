#include <limits.h> /* contient des variables pour test des limites
                       ex limite de chaine registre , sa ,offset ,...*/


/**
*Extrait l'id d'un registre depuis un mnemonique de registre
* Retourne -1 si ERREUR
*/

unsugned char mnemoReg_2_regId(char * str){
  char** tabMnem = {
    "zero";
    "at";
    ....
  };

  for (i = 0;i<...; i++){
    if(strcmp(str, tabMnemo) == 0) {
      return i;
    }
  }


  "20.7"
  strtol  /* Pour faire des conversions de chaines de charactères */
  strtoll
  sscanf
}




typedef enum {
  REG,
  IMM,
  ...
} TYPE_VAL_OP;

typedef struct {
  TYPE_VAL_OP type;
  union {
    unsigned char asREG; /* max  31 */
    short asIMM;
    unsigned char asSa ; /* max 5 */
    short asAdresseRel;
    unsigned int asAdressesAbs;
    char* etiq
    struct {
      unsigned char reg;
      short offset;
    } asBaseOffset ;
  } val ;
} operande_value_t;

/* Relocation le sytème choisi à quelle adresse commence le programme. Par exemple j 0x0 alors 0x0 n'est pas une vraie adresse elle doit renvoyer à l'adresse du début de la section .text

table symb etiquette associée à son adrsse après incrément 2

BNE $1,$2,etiquette 1 IL faut réaliser que l'étiquette est déclarée avant,
