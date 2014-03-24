; declare i32 @printf(i8* nocapture noalias, i64 nocapture noalias)
declare i32 @printf(i8*, i64)

define fastcc i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
	%tmp = mul i32 %x, %y
	%tmp2 = add i32 %tmp, %z
	ret i32 %tmp2
}

define fastcc i8* @add_ptr(i8* %xp, i8* %yp) {
entry:
	%x64p = bitcast i8* %xp to i64*
	%y64p = bitcast i8* %yp to i64*
	%x = load i64* %x64p
	%y = load i64* %y64p
	%sum = add i64 %x, %y
	%sump = alloca i64
	store i64 %sum, i64* %sump
	%sum8p = bitcast i64* %sump to i8*
	ret i8* %sum8p
}

define fastcc { i8, i8* } @add_ptr_dyn({ i8, i8* } %dynx, { i8, i8* } %dyny) {
entry:
	%xp8 = extractvalue { i8, i8* } %dynx, 1
	%xp64 = bitcast i8* %xp8 to i64*
	%x64 = load i64* %xp64

	%yp8 = extractvalue { i8, i8* } %dyny, 1
	%yp64 = bitcast i8* %yp8 to i64*
	%y64 = load i64* %yp64

	%sum64 = add i64 %x64, %y64
	%sum64p = alloca i64
	store i64 %sum64, i64* %sum64p
	%sum8p = bitcast i64* %sum64p to i8*
	%dynsum0 = insertvalue { i8, i8* } undef, i8 64, 0
	%dynsum1 = insertvalue { i8, i8* } %dynsum0, i8* %sum8p, 1

	ret { i8, i8* } %dynsum1
}

; @dyntype = global type { i8, i8* }

@str = private unnamed_addr constant [6 x i8] c": %d\0a\00"
@ints = private unnamed_addr constant [2 x i8] [ i8 22, i8 33 ]
@inta = private unnamed_addr constant i64 555
@intb = private unnamed_addr constant i64 666
; @dyninta = private unnamed_addr constant { i8, i8* } { i8 0, i8* bitcast(i64* getelementptr(i64* @inta, i64 0) to i8*) }
; @dynintb = private unnamed_addr constant { i8, i8* } { i8 0, i8* bitcast(i64* getelementptr(i64* @intb, i64 0) to i8*) }

define i64 @main() {
myshit:
	%formatstr = getelementptr [6 x i8]* @str, i64 0, i64 0

	%res = call fastcc i32 @mul_add(i32 1, i32 2, i32 3)

	; ; %xp = getelementptr [2 x i8]* @ints, i8 0, i8 0
	; %xp = alloca i8
	; store i8 11, i8* %xp
	; %yp = getelementptr [2 x i8]* @ints, i64 0, i64 1
	; %res2p = call fastcc i8* @add_ptr(i8* %xp, i8* %yp)
	; %res2 = load i8* %res2p



	%ap = getelementptr i64* @inta, i64 0
	%ap8 = bitcast i64* %ap to i8*
	%bp = getelementptr i64* @intb, i64 0
	%bp8 = bitcast i64* %bp to i8*
	%res2p = call fastcc i8* @add_ptr(i8* %ap8, i8* %bp8)
	%res28p = bitcast i8* %res2p to i64*
	%res2 = load i64* %res28p

	call i32 @printf(i8* %formatstr, i64 %res2)



	%res3p = call fastcc { i8, i8* } @add_ptr_dyn({ i8, i8* } { i8 64, i8* bitcast(i64* getelementptr(i64* @inta, i64 0) to i8*) }, { i8, i8* } { i8 64, i8* bitcast(i64* getelementptr(i64* @intb, i64 0) to i8*) })
	%res38p = extractvalue { i8, i8* } %res3p, 1
	%res364p = bitcast i8* %res38p to i64*
	%res364 = load i64* %res364p

	call i32 @printf(i8* %formatstr, i64 %res364)

	ret i64 %res2
}

