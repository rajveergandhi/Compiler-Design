package alias

var _ int = 2;
var _ bool = 2;
var c = 5;
var e = 3.2;
var f,g,h float64 = 2.1, 3.2, 4.5;
var y1, y2 = 42, 43
var q10 [][]string
var a10 [23]int

var (
    c1, c2 int;
    d1, d2 float64;
)
var q1,q2,q3 rune = 2, 2.2, false

type a int
type b float64

type point struct {
    x, y float64
}

type (
    num int
    point2 struct {
        x4, y4 float64
    }
)


func f2(a5 int, b5 int, c5 string, d5 int, c int) {
    a5, b0 := 2, 4
    for qqqq := 4;true; qqqq++ {
        var mmmm int = 10;
        qqqq = 10
    }

    nn:=2;
    var newfuncvar1 int = 10;
    var newfuncvar2 = 10;
    if (a5) {
        var k3 = 8;
    } else {
        var k4 = 8;
    }
    var myint int = 10
    a5 = 10
    print (a5, b5, c5)
    println (b5, a5)
    
    switch short := 11; b5 {
        case c5:
            print ("foo")
            var myint2 = 100
        case d5:
            print ("foo")
            var myint5 = 100
    }

    return a5
}
