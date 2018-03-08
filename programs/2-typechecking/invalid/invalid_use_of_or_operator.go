/* Use of OR operator on invalid types */

package main

var a int = 1

func main() {
	print(a || 0) //not supported for int
}
