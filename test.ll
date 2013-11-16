declare i32 @printf(i8* nocapture noalias)

define fastcc i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
	%tmp = mul i32 %x, %y
	%tmp2 = add i32 %tmp, %z
	ret i32 %tmp2
}

define fastcc i8* @add_ptr(i8* %xp, i8* %yp) {
entry:
	%x = load i8* %xp
	%y = load i8* %yp
	%sum = add i8 %x, %y
	%sump = alloca i8
	store i8 %sum, i8* %sump
	ret i8* %sump
}

@str = private unnamed_addr constant [6 x i8] c"abcd\0a\00"
@ints = private unnamed_addr constant [2 x i8] [ i8 22, i8 33 ]

define i8 @main() {
myshit:
	%res = call fastcc i32 @mul_add(i32 1, i32 2, i32 3)

	%ptr = getelementptr [6 x i8]* @str, i32 0, i32 0
	call i32 @printf(i8* %ptr)

	; %xp = getelementptr [2 x i8]* @ints, i8 0, i8 0
	%xp = alloca i8
	store i8 11, i8* %xp
	%yp = getelementptr [2 x i8]* @ints, i8 0, i8 1
	%res2p = call fastcc i8* @add_ptr(i8* %xp, i8* %yp)
	%res2 = load i8* %res2p

	ret i8 %res2
}

