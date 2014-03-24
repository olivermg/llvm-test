; declare i32 @printf(i8* nocapture noalias, i64 nocapture noalias)
declare i32 @printf(i8*, ...)

@decimalstr = private unnamed_addr constant [6 x i8] c": %d\0a\00"
@pointerstr = private unnamed_addr constant [6 x i8] c": %p\0a\00"

define i64 @0(i64 %a, i64 %b) {
entry:
	%res = add i64 %a, %b
	ret i64 %res
}

define i64 @main() {
myshit:
	%dformatstr = getelementptr [6 x i8]* @decimalstr, i64 0, i64 0
	%pformatstr = getelementptr [6 x i8]* @pointerstr, i64 0, i64 0

	; %res = call fastcc i32 @mul_add(i32 1, i32 2, i32 3)

	; ; %xp = getelementptr [2 x i8]* @ints, i8 0, i8 0
	; %xp = alloca i8
	; store i8 11, i8* %xp
	; %yp = getelementptr [2 x i8]* @ints, i64 0, i64 1
	; %res2p = call fastcc i8* @add_ptr(i8* %xp, i8* %yp)
	; %res2 = load i8* %res2p



	; %ap = getelementptr i64* @inta, i64 0
	; %ap8 = bitcast i64* %ap to i8*
	; %bp = getelementptr i64* @intb, i64 0
	; %bp8 = bitcast i64* %bp to i8*
	; %res2p = call fastcc i8* @add_ptr(i8* %ap8, i8* %bp8)
	; %res28p = bitcast i8* %res2p to i64*
	; %res2 = load i64* %res28p

	; call i32 @printf(i8* %formatstr, i64 %res2)



	; %res3p = call fastcc { i8, i8* } @add_ptr_dyn({ i8, i8* } { i8 64, i8* bitcast(i64* getelementptr(i64* @inta, i64 0) to i8*) }, { i8, i8* } { i8 64, i8* bitcast(i64* getelementptr(i64* @intb, i64 0) to i8*) })
	; %res38p = extractvalue { i8, i8* } %res3p, 1
	; %res364p = bitcast i8* %res38p to i64*
	; %res364 = load i64* %res364p

	; call i32 @printf(i8* %formatstr, i64 %res364)

	; ret i64 %res2

	call i32 (i8*, ...)* @printf(i8* %pformatstr, i64 (i64, i64)* @0)

	%sum = call i64 @0(i64 23, i64 34)
	call i32 (i8*, ...)* @printf(i8* %dformatstr, i64 %sum)
	ret i64 %sum
}

