/* Invalid function return value (different type alias) */
package main

type num1 int
type num2 int

func main() {
	var a num1
	var b num2
	c := foocat(a, b)
}

func foocat(a num1, b num2) num2 {
	return a
}

