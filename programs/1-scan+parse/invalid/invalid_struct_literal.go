/* Invalid struct literal */

package main

type x struct{
	a int;
}

var b x = x{1}

func main(){
	print("Test")
}