//~Even
//~Positive
//~Even positive multi digit

package main

func main(){

	var x int = 6
	if x%2 == 0{
		print("Even")
	} else {
		print("Odd")
	}
	println()

	var b int = 2
	if a:=(5<4); a {
		print("True")
	} else if b<0 {
		print("Negative")
	} else {
		print("Positive")
	}
	println()

	if num := 24; num%2 == 0 {
		if b:=num<0; b {
			if num <= -10 {
				print("Even negative multi digit")
			} else {
				print("Even negative single digit")
			}
		} else if num<10 {
			print("Even positive single digit")
		} else {
			print("Even positive multi digit")
		}
	} else {
		if b:=num<0; b {
			if num <= -10 {
				print("Odd negative multi digit")
			} else {
				print("Odd negative single digit")
			}
		} else if num<10 {
			print("Odd positive single digit")
		} else {
			print("Odd positive multi digit")
		}
	}
}
