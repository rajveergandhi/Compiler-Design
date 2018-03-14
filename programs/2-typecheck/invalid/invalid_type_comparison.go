/* Invalid type comparisons */
package main

type num1 int
type num2 int
func main () {
	var a num1
	var b num2
	print(a==b)
}