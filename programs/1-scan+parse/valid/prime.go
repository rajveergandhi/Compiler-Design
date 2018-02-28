package main

var num int = 7

func main() {
	var i int
	flag := 0
	for i = 2; i<num; i++ {
		if num % i == 0 {
			flag = 1
		}
	}
	if flag == 0 {
		print("Prime number")
	} else {
		print("Not a prime number")
	}
}
