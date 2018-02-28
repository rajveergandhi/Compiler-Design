package main

func bubble(a []int) {
	var i,j int
	l := len(a)
	for i = 0; i<l; i++ {
		for j=i; j<l; j++ {
			if a[i] > a[j] {
				a[i], a[j] = a[j], a[i]
			}
		}
		
	}
	print(a)	
}
