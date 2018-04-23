
.text
.global main
main:

addi r1, r0, 1
addi r2, r0, 1
addi r3, r0, 2
addi r4, r0, 4
addi r5, r5, 2

nop

loop: 

add r1, r0, r2
nop
add r2, r0, r3
nop
add r3, r2, r1
nop
addi r5, r5, 1
nop
slt r6, r5, r4
nop
nop
nop
bnez r6, loop
nop
nop
nop
finished:

nop:
trap 0



