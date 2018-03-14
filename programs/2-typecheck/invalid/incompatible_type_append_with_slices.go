/* Incompatible type append with slices */
package main

type a int
type b int

var x []a

func main(){
	var y b
	x = append(x, y)
}