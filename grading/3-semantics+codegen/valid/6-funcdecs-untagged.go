//~1
//~1

package main

func f(a struct { a int; }) {
	println(a.a)
}

func main() {
	var a struct { a int; }
	var b struct { a int; }
	a.a = 1
	b = a
	f(a)
	f(b)
}
