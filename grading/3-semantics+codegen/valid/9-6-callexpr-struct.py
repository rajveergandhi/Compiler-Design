# import all necessary Python libraries
from __future__ import print_function
class _GOLITE__my:
    _GOLITE__a = 0

def _GOLITE__f(_GOLITE__m):
    _GOLITE__m._GOLITE__a = 2

def main():
    _GOLITE__m1 = _GOLITE__my()
    _GOLITE__m1._GOLITE__a = 1
    print(_GOLITE__m1._GOLITE__a,  sep=' ', end='\n')
    _GOLITE__f(_GOLITE__m1)
    print(_GOLITE__m1._GOLITE__a,  sep=' ', end='\n')

if __name__ == "__main__":
    main()