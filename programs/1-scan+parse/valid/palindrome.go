package main

var a int = 1331
var pal int = 0

func main() {
	var rem int
	var copy int = a
	for copy > 0 {
		rem = copy % 10
		pal = pal * 10 + rem
		copy /= 10
	}
	if (pal == a){
		print("Palindrome")
	} else {
		print("Not a palindrome")
	}
	
}
