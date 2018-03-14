/* Invalid type comparisons 2*/
package main

type num1 int
type num2 num1
func main () {
	var a num1
	var b num2
	print(a==b)
}