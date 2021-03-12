1.{
    a. var1 Word ?
    b. s8 REAL8 ?
    c. wArray Word 1,2,3 
    d. var BYTE 500 DUP("TEST")   ;

}

2.{




}

3.{

    mov al, var1            ;al=-4
    mov ah, var1+3          ;ah=1
    mov ax, var3            ;ax=-16
    mov ax, var3-2          ;ax= 3000h
    mov edx, var4           ;edx=1
    movzx edx, var2         ;edx=
    mov edx, var4+4         ;edx=5
    movsx edx, var1         ;edx=





}


    .code
    myBytes BYTE 10h,20h,30h,40h
    myWords Word 8Ah,3Bh,72h,44h,66h
    myDouble DWORD 1,2,3,4,5
    myPointer DWORD myDouble


6.{
    mov esi ,OFFSET myBytes
    mov al, [esi]               ;AL=
    mov al, [esi+3]             ;AL=
    mov esi, OFFSET myWords + 2
    mov ax, [esi]               ;AX=
    mov edi, 8
    mov edx,[myDouble  +edi]    ;EDX=
    mov edx, myDouble[edi]       ;EDX=
    mov ebx, myPointer
    mov eax, [ebx+4]            ;EAX=

}
