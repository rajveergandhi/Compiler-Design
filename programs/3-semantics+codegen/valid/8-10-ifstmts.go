//~true
//~false
//~true
//~false
//~false

package main

func main() {
	var a bool = false

	if a := true; a {
		println(a)
	}
	println(a)

	if a {

	} else if a := true; a {
		println(a)
	}
	println(a)

	if a {

	} else {
		println(a)
	}
}
