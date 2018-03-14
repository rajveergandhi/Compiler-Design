/* Invalid assignment of function return value (array size mismatch) */
package main

var a [5]int
var b [6]int

func foo(x [5]int) [5]int{
	return x
}

func main(){
	b = foo(a)
}