/* Using fallthrough in switch statement. */

package main

var a int = 5

func main() {
	if a<10 {
		print("Test")
		fallthrough
	}
}
