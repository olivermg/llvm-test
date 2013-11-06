define i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
	%tmp = mul i32 %x, %y
	%tmp2 = add i32 %tmp, %z
	ret i32 %tmp2
}

define i32 @main() {
myshit:
	%res = call i32 @mul_add(i32 1, i32 2, i32 3)
	ret i32 %res
}

