.name "lldi"
.comment "lldi"

add r1, r1, r2
add r2, r2, r2
add r2, r2, r2
add r2, r2, r2
add r2, r2, r2
lldi -1, r3, r4
lldi -165654654654, r3, r4
lldi -51, r3, r4
sti r4, %500, %100
lldi -1024, r3, r4
sti r4, %600, %100
lldi -2048, r3, r4
sti r4, %700, %100
lldi -4096, r3, r4
sti r4, %800, %100
lldi -545465, r3, r4
sti r4, %900, %100
lldi -512, %-512, r4
lldi -1024, %-4096, r4
lldi -2048, %-2048 , r4
lldi -4096, %-512, r4
lldi -545465, %-512, r4
lldi 40961, r3, r4
lldi 654684, r3, r4
lldi %-54465, r3, r4
lldi -1, %565464684684, r4
lldi -1, r3, r4
lldi -1, %4096, r4
sti r4, r2, r2
