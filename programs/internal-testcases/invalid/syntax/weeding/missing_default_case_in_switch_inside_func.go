/* Function with a switch statement with no default case, but for which all case
 * blocks return. */

package main;

func foo(x int) int {
	if (x % 2 == 0) {
		return x;
	} else {
		switch ; x {
			case 3:
				return x;
			case 5:
				return x;
			case 7:
				return x;
		}
 	}
}

func main() {
	// Do nothing.
}
