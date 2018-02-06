        global main
        extern printf
        extern scanf

        section .data
		msg db "Podaj dzialanie: ",0
		wynik db "Wynik %lf",10,0
		error db "Podano bledny znak!",10,0
		fmt db "%lf %c %lf",0
        section .bss
        	firNum resq 1
		secNum resq 1
		result resq 1
		sign resb 4
        section .text
main:
	finit
      	;czytanie dzialania
        push msg
	call printf
	add esp,4

	push secNum
	push sign
	push firNum
	push fmt
	call scanf
	add esp,16


        fld qword[firNum]
        fld qword[secNum]

	cmp dword[sign],'+'
	jne go1
	faddp
	call giveResult
	ret
go1:

        cmp dword[sign],'-'
        jne go2
        fsubp
        call giveResult
        ret
go2:

        cmp dword[sign],'*'
        jne go3
        fmul
        call giveResult
        ret
go3:

        cmp dword[sign],'/'
        jne go4
        fdiv
        call giveResult
        ret
go4:

	push error
	call printf
	add esp,4

	ret

giveResult:
        fst qword[result]
        push dword[result+4]
        push dword[result]
        push wynik
        call printf
        add esp,12

