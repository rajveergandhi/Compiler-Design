/* Define struct Time which has two fields: Hour and Minute */

package main

/* Time struct */
type Time struct {
  Hour, Minute int
}

func main() {
  var time Time
  time.Hour = 6
  time.Minute = 30

  println(time.Hour)
  println(time.Minute)
}
