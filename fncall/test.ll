
define i64 @main() {
	%1 = bitcast i64 33 to i64
	%2 = bitcast i64 44 to i64
	%3 = call i64 @fn(i64 %1, i64 %2)
	ret i64 %3
}

define i64 @fn(i64 %a, i64 %b) {
	%1 = add i64 %a, %b
	ret i64 %1
}

