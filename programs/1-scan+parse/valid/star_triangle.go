package main

var a int = 10

func main() {
	var i int
	var j int
	for i = 0; i<a; i++{
		for j = 0; j<=i; j++{
			print("*")
		}
		println()
	}
}
