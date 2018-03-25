//~01234
//~AAA
//~345678
//~Only semicolons; Only semicolons; Only semicolons; 
//~No init stmt; No init stmt; No init stmt; 
//~No post op; No post op; No post op; 
//~Only init; Only init; Only init; Only init; Only init; 
//~Only post op; Only post op; Only post op; Only post op; Only post op; Only post op;

package main

func main(){
	for a:=0;a<5;a++ {
		print(a)
	}
	println()

	var b int = 0
	for b<3 {
		print("A");
		b++
	}
	println()

	var c int = 3
	for {
		print(c)
		c++
		if c>8{
			break
		}
	}
	println()

	for ;; {
		print("Only semicolons; ")
		if c>10 {
			break
		}
		c++
	}
	println()

	var x int = 4
	for ;x<7;x++ {
		print("No init stmt; ")
	}
	println()	

	for x=0;x<3; {
		print("No post op; ")
		x++
	}
	println()

	for x=0;; {
		print("Only init; ")
		if x>3 {
			break
		}
		x++
	}
	println()

	x=0
	for ;;x++ {
		print("Only post op; ")
		if x>4 {
			break
		}
	}
}