/* Function call with trailing comma */

package main

var a int = 5

func foo(a int){
	print(a)
}

func main(){
	foo(5,)
}