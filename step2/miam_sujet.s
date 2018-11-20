# TEST_RETURN_CODE = PASS
# allons au ru
.set noreorder
.text
    ADDI $t1,$zero,8
    Lw $t0 , lunchtime
    LW $6, -200($7)

boucle:
    BEQ $t0 , $t1 , byebye
    NOP
    addi $t1 , $t1 , 1
    J boucle
    NOP
byebye:
    JAL viteviteauru

.data
lunchtime:
    .word 12
    .word menu
    .asciiz "ils disent : \"au ru!\""
.bss
menu:
    .space 24
