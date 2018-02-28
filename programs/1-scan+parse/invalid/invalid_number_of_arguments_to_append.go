/* Invalid number of arguments to append. */

package main

var a []int

func main() {
	append(a, 5, 10)
	print(a)
}
