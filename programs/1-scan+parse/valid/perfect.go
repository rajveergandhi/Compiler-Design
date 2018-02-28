package main

var number int = 6

func main() {
	sum := 0
	temp := number - 1
	quotient := 0
	remainder := 0
	for temp != 0 {
		quotient = number / temp
		remainder = number - (temp * quotient)
		if remainder == 0 {
			sum += temp
		}
		temp -= 1
	}
	if sum == number {
		print("Perfect")
	} else {
		print("Not perfect")
	}
}
