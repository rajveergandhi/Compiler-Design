package main

var x int

func foo() int{
	x++
	return x
}

func main(){
	var a int =5
	var b string = "abc"
	var b1 string = "a\nc"
	var c string = `a\nc`
	var d float64 = 5.6
	var e rune = 'm'
	var e1 rune = '\n'
	println(a)
	println(b)
	println(b1)
	println(c)
	println(d)
	println(e)
	println(e1)
	
	println(x,foo(),foo())
	println(x," ",foo()," ",foo())
}