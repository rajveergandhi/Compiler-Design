/* Use of variable before declaration */

package main

var a int = 5
var b int = a+c //Use of variable before declaration
var c int = 6

func main(){
	print(a+b)
}