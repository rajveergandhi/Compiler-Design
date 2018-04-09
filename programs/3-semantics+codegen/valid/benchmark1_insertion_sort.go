//~1
//~2
//~3
//~4
//~5
//~6
//~7
//~8
//~9
//~10
//~11
//~12
//~13
//~14
//~15
//~16
//~17
//~18
//~19
//~20

/* Insertion sort of an array of size 50000 to ascending order */

package main

func insertion_sort(arr []int, size int){
  var j int
  var tmp int
  i := 1
  for i < size {
    j = i
    for (j>0 && arr[j-1]>arr[j]) {
      tmp = arr[j]
      arr[j] = arr[j-1]
      arr[j-1] = tmp
      j = j - 1
    }
    i = i + 1
  }
  i = 0
  for i<20 {
    println(arr[i])
    i = i + 1
  }
  
}

func main() {
  var length int = 50000
  var items []int
  i := 0
  var x int = length
  for i<length {
    items = append(items, x)
    x = x - 1
    i = i + 1
  }
  
  insertion_sort(items, length)
}