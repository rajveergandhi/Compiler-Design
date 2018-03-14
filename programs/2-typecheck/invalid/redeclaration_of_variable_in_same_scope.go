/* Redeclaration of variable in same scope */

package main

var a int = 5

func main(){
	a := 6 //Valid
	a := 7 //Invalid
}