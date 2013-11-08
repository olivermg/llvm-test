declare i32 @printf(i8* nocapture noalias)

define fastcc i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
	%tmp = mul i32 %x, %y
	%tmp2 = add i32 %tmp, %z
	ret i32 %tmp2
}

@str = private constant [6 x i8] c"abcd\0a\00"

define i32 @main() {
myshit:
	%res = call fastcc i32 @mul_add(i32 1, i32 2, i32 3)
	%ptr = getelementptr [6 x i8]* @str, i32 0, i32 0
	call i32 @printf(i8* %ptr)
	ret i32 %res
}

