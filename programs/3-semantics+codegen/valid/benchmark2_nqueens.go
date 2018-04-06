/* Solving the N-Queens problem in a 40x40 board 
The N Queen is the problem of placing N chess queens on an N×N chessboard so that no two queens attack each other. */

package main

var size int = 30;

func correctPos(board [][]int, row int, column int) bool{
  var i,j int;
  for i = 0; i < column; i++ {
    if board[row][i] == 1{
      return false
    }
  }
  for i,j = row,column; i >= 0 && j >= 0; i,j = i-1, j-1 {
    if board[i][j] == 1 {
      return false
    }
  } 
  for i,j = row,column; i < size && j >= 0; i,j = i+1, j-1 {
    if board[i][j] == 1 {
      return false
    }
  } 
  return true
}

func nqueens(board [][]int, column int) bool {
  if column >= size{
    return true
  }
  for i := 0; i < size; i++{
    if correctPos(board, i, column) == true {
      
      
      board[i][column] = 1
      
      
      if nqueens(board, column + 1) == true {
        return true
      }
      
      
      board[i][column] = 0
    }
  }
  return false
}

func main(){
  var board [][]int

  for i := 0; i < size; i++ {
    var row []int
    for j := 0; j < size; j++ {
      row = append(row, 0)
    }
    board = append(board, row)
  }
  var status bool = nqueens(board, 0)
  
  if status == true {
    for i := 0; i < size; i++ {
      for j := 0; j < size; j++ {
        print(" ", board[i][j], " ")
      }
      println()
    }
  } else {
    println("No solution")
  }
}