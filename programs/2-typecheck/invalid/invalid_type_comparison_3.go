/* Invalid type comparisons 2*/
package main

type a struct{
	x int
}

type b struct{
	y int
}

func main(){
	var p a
	var q b
	print(p==q)
}