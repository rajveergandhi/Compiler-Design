/* invalid struct member assignment */
package main

type a struct{
	x int
}

func main(){
	var p a
	p.x = "x"
}