/* Invalid expression on global scope */

package main

var a int = 5

a++

func main(){
	print(a)
}