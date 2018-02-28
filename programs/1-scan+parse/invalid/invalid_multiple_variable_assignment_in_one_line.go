/* Invalid multiple variable assignment types in single line */

package main

var a string, b int = "a", 5

func main(){
	print(a)
	print(b)
}

