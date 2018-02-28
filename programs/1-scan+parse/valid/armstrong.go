package main

var a int = 371

func main(){
	var rem int
	sum := 0
	copy := a
	for copy > 0 {
		rem = copy % 10
		sum += (rem*rem*rem)
		copy /= 10
	}
	if sum == a {
		print("Armstrong")
	} else {
		print("Not Armstrong")
	}
}