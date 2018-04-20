# import all necessary Python libraries
from __future__ import print_function
_GOLITE__glob = 0
_GOLITE__array = [0] * 6
def _GOLITE__foo():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__bar(_GOLITE__a):
    print(_GOLITE__a,  sep=' ', end='\n')
    return _GOLITE__a

def _GOLITE__baz():
    _GOLITE__glob+= 1
    return _GOLITE__array

def main():
    _GOLITE__array[0] = 0
    _GOLITE__array[1] = 1
    _GOLITE__array[2] = 2
    _GOLITE__array[3] = 3
    _GOLITE__array[4] = 4
    _GOLITE__array[5] = 5
    print(_GOLITE__glob,     _GOLITE__foo()
, _GOLITE__glob,  sep=' ', end='\n')
    print(    _GOLITE__foo()
, _GOLITE__array[    _GOLITE__foo()
], _GOLITE__array[    _GOLITE__foo()
],     _GOLITE__foo()
,  sep=' ', end='\n')
    print(    _GOLITE__bar(    _GOLITE__bar(0)
)
,     _GOLITE__bar(1)
,  sep=' ', end='\n')
    _GOLITE__glob = 0
    print(    _GOLITE__baz()
[_GOLITE__glob],  sep=' ', end='\n')
    print(    _GOLITE__bar(    _GOLITE__baz()
[_GOLITE__glob])
,  sep=' ', end='\n')

if __name__ == "__main__":
    main()