/* Solving the 0-1 knapsack problem. The 0-1 knapsack problem can choose an item only if there is space in the knapsack for the whole item, otherwise rejects it altogether.
It is a dynamic programming problem 
In this program, all the subproblems (items from 1 to N and capacity if 1 to max_cap for ever subset of items) are solved and printed.
*/

package main

type item struct {
  value int
  weight int
}
var itemlist []item

func max(a int, b int) int{
  if a > b {
    return a
  } else {
    return b
  }
}

func knapsack(capacity int, n int) int{
  if n == 0 || capacity == 0 {
    return 0
  }
  if itemlist[n - 1].weight > capacity {
    return knapsack(capacity, n-1)
  } else {
    return max(itemlist[n-1].value + knapsack(capacity - itemlist[n-1].weight, n-1), knapsack(capacity, n - 1))
  }
}

func main(){
  var cap int = 1000
  var itemcount = 20
  var item item 
  item.value = 1
  item.weight = 2
  itemlist = append(itemlist, item)
  item.value = 2
  item.weight = 4
  itemlist = append(itemlist, item)
  item.value = 3
  item.weight = 6
  itemlist = append(itemlist, item)
  item.value = 4
  item.weight = 8
  itemlist = append(itemlist, item)
  item.value = 5
  item.weight = 10
  itemlist = append(itemlist, item)
  item.value = 6
  item.weight = 1
  itemlist = append(itemlist, item)
  item.value = 7
  item.weight = 3
  itemlist = append(itemlist, item)
  item.value = 8
  item.weight = 5
  itemlist = append(itemlist, item)
  item.value = 9
  item.weight = 7
  itemlist = append(itemlist, item)
  item.value = 10
  item.weight = 9
  itemlist = append(itemlist, item)
  item.value = 11
  item.weight = 20
  itemlist = append(itemlist, item)
  item.value = 12
  item.weight = 18
  itemlist = append(itemlist, item)
  item.value = 13
  item.weight = 16
  itemlist = append(itemlist, item)
  item.value = 14
  item.weight = 14
  itemlist = append(itemlist, item)
  item.value = 15
  item.weight = 12
  itemlist = append(itemlist, item)
  item.value = 16
  item.weight = 11
  itemlist = append(itemlist, item)
  item.value = 17
  item.weight = 13
  itemlist = append(itemlist, item)
  item.value = 18
  item.weight = 15
  itemlist = append(itemlist, item)
  item.value = 19
  item.weight = 17
  itemlist = append(itemlist, item)
  item.value = 20
  item.weight = 19
  itemlist = append(itemlist, item)
  for i := 1; i <= itemcount; i++ {
    for j := 1; j <= cap; j++ {
      println("No. of items : ",i ,", Capacity : ",j , "Max Value : ", knapsack(j, i))
    }
  }
}