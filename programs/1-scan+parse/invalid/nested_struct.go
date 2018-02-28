/* Nested struct declaration */

package main

type num struct{
	x int
	type new_num struct{
		a int
		b int
	}
	y new_num
}
var p num

func main(){
	print("Test")
}