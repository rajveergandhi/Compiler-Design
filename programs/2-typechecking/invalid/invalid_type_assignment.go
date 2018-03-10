/* Invalid type assignment */
package main

type a struct{
	x int
}

type b struct{
	y a
}

type c struct{
	z int
}

func main(){
	var p b
	var q c
	p.y = q
}