/* Invalid return type of function (different type alias arrays) */
package main

type num1 int
type num2 int

func main() {
	var a [5]num1
	var b [5]num2
	c := foocat(a, b)
}

func foocat(a [5]num1, b [5]num2) [5]num2 {
	return a
}

