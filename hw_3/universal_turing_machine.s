.data

tm: .word 0, 0, s0, 0, 1, s1, 0, 5, s2, 1, 0, s3, 1, 1, s4, 1, 6, s5, 2, 0, s4, 2, 1, s6, 2, 6, s7, 6, 1, 1, 1, 5

.text
.global main

main:
addi r4, r0, 120
addi r2, r0, 0
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop


search:
addi r5, r0, 0

loop:
lw r10, tm(r5)
nop
nop
seq r6, r2, r10
nop
nop
addi r5, r5, 4
nop
nop
nop
lw r10, tm(r5)
nop
nop
seq r7, r1, r10
nop
nop
nop
and r8, r6, r7
nop
addi r5, r5, 8
nop
beqz r8, loop
nop
nop
subi r5, r5, 4
nop
nop
nop
lw r3, tm(r5)
nop
nop
jr r31
nop
nop


s0:
addi r2, r0, 0
nop
nop
nop
addi r9, r0, 0
nop
nop
nop
sw tm(r4), r9
nop
nop
addi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s1:
addi r2, r0, 0
nop
nop
nop
addi r9, r0, 1
nop
nop
nop
sw tm(r4), r9
nop
nop
addi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s2:
addi r2, r0, 2
nop
nop
nop
addi r9, r0, 5
nop
nop
nop
sw tm(r4), r9
nop
nop
subi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s3:
addi r2, r0, 1
nop
nop
nop
addi r9, r0, 0
nop
nop
nop
sw tm(r4), r9
nop
nop
subi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s4:
addi r2, r0, 1
nop
nop
nop
addi r9, r0, 1
nop
nop
nop
sw tm(r4), r9
nop
nop
subi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s5:
addi r2, r0, 3
nop
nop
nop
addi r9, r0, 6
nop
nop
nop
sw tm(r4), r9
nop
nop
nop
nop
j fin
nop
nop

s6:
addi r2, r0, 2
nop
nop
nop
addi r9, r0, 0
nop
nop
nop
sw tm(r4), r9
nop
nop
subi r4, r4, 4
nop
nop
lw r1, tm(r4)
nop
nop
jal search
nop
nop
jr r3
nop
nop

s7:
addi r2, r0, 3
nop
nop
nop
addi r9, r0, 1
nop
nop
nop
sw tm(r4), r9
nop
nop
nop
nop
nop
j fin
nop
nop


fin:
trap 0
