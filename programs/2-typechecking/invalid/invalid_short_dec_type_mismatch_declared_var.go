/* Invalid short declaration saving incompatible type in declared variable */

package main

func main(){
	a := 5
	a, b := "a",5.5
	print(a)
	print(b)
}