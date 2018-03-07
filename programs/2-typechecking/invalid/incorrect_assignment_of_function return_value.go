/* Incorrect assignment of return value of function */

package main

var a int = 5

func foo(x int, y string, z float64) float64{
	print("Hi")
	return 5.9
}

func main(){
	a = foo(1,"A",2.3) //Return type float64 cannot be assigned to type int
}

