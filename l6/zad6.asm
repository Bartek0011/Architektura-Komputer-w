global main

extern printf
extern scanf

section .data
	giveX db "X=",0
	fmt db "%lf",0
	aResult db "a) %lf",10,0
	bResult db "b) %lf",10,0
	cResult db "c) %lf",10,0
	dResult db "d) %lf",10,0

section .bss
	x resq 1
	result resq 1
	param1 resq 1
	param2 resq 1
	param3 resq 1
	param4 resq 1

section .text

main:
	finit

	push giveX
	call printf
	add esp,4

	push x
	push fmt
	call scanf
	add esp,8

	fld qword[x]
	call pdpA
        fstp qword[result]
        push dword[result+4]
        push dword[result]
        push aResult
        call printf
        add esp,12
	
	fld qword[x]
	call pdpB
        fstp qword[result]
        push dword[result+4]
        push dword[result]
        push bResult
        call printf
        add esp,12

        fld qword[x]
        call pdpC
        fstp qword[result]
        push dword[result+4]
        push dword[result]
        push cResult
        call printf
        add esp,12
	
        fld qword[x]
        call pdpD
        fstp qword[result]
        push dword[result+4]
        push dword[result]
        push dResult
        call printf
        add esp,12


	ret

pdpA:
	fstp qword[param1]
	fld1
	fld qword[param1]
	fyl2x ;zakaduj log2(x) do licznika
	fldl2e ;zaladuj log2(e) do mianownika

	fdiv

	ret

pdpB:
        ;korzystam ze wzoru x^(a+b) = x^(a) * x^(b)
                ;wyliczenie pierwszego czynnika ktory w wykladniku ma obciecie log2(e)
                ;do czesci ulamkowej przemnozone przez x
        fld st0
	fstp qword[param2]
        fldl2e
        fmulp           ;5*log2(e)
	fld qword[param2]
        fldl2e
	fmulp
        frndint		;Floor[5*log2(e)]
        fsubp		;5*log2(e) - Floor[5*log2(e)]
	ftst	;porownuje z 0
	fstsw ax
	sahf
	ja go
	fld1
	faddp
go:
        f2xm1
        fld1
        faddp
                ;wyliczenie drugiego czynnika ktory w wykladniku ma czesc calkowita log2(e)
		;przemnozona przez x
	fld qword[param2]
        fldl2e
	fmulp		;5*log2(e)
	fld1
        fscale		;1*2^(log2(e))
        fstp ( st1 )	;zdejmujemy 1

                ;wymnozenie dwoch czynnikow, mam wynik w postaci e^(x)
        fmulp

	ret

pdpC:
	fld st0
	fstp qword[param3]
	call pdpB

	fld1
	fld qword[param3]
	call pdpB
	fdivp

	fsubp

	fld1
	fld1
	faddp

	fdivp

ret

pdpD:
	fld st0
	fstp qword[param4]
	fld st0 
	fmulp
	fld1
	faddp
	fsqrt

	fld qword[param4]

	faddp

	call pdpA
ret
