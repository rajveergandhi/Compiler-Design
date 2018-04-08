/*
One
Five
True
True 2
True Inside
*/

package main

var x int

func foo() bool{
	return true
}

func bar() bool{
	return false
}

func main(){
	var a int = 1
	switch a {
		case 1:
			println("One");
			break;
		case 2:
			println("Two");
			break;
		default:
			println("None");
			break;
	}

	var b float64 = 5.6
	switch b {
		case 1.3:
			println("One");
			break;
		case 2.4:
			println("Two");
			break;
		case 5.60:
			println("Five");
			break;
		default:
			println("None");
			break;
	}

	switch {
		case true:
			println("True");
			break;
		case false:
			println("False");
			break;
		default:
			println("None");
			break;
	}

	switch {
		case foo():
			println("True 2");
			break;
		case bar():
			println("False 2");
			break;
		default:
			println("None");
			break;
	}

	switch a {
		case 1:
			switch {
				case true:
					println("True Inside");
					break;
				case false:
					println("False Inside");
					break;
				default:
					println("None");
					break;
			}
			break;
		case 2:
			println("Two");
			break;
		default:
			println("None");
			break;
	}

}
