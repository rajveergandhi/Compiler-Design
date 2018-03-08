/* Incorrect number of arguments in function call */

package main

func foo(x int, y string, z float64, w rune){
	print("Hi")
}

func main(){
	foo(1,"A",2.3)
}

