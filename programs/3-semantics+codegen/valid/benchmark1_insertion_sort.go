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
  for i<size {
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