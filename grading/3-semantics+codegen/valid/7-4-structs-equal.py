# import all necessary Python libraries
from __future__ import print_function
class _GOLITE__my:
    _GOLITE__a = 0

class _GOLITE__empty:
    pass

class _GOLITE__uncomparable:
    _GOLITE__a = []

class _GOLITE__blank:
    _GOLITE___ = 0
    _GOLITE__a = 0
    _GOLITE___ = 0

def main():
    _GOLITE__m1 = _GOLITE__my()
    _GOLITE__m2 = _GOLITE__my()
    _GOLITE__m1._GOLITE__a = 1
    _GOLITE__m2._GOLITE__a = 1
    print((_GOLITE__m1 == _GOLITE__m2),  sep=' ', end='\n')
    print((_GOLITE__m1 != _GOLITE__m2),  sep=' ', end='\n')
    _GOLITE__m2._GOLITE__a = 2
    print((_GOLITE__m1 == _GOLITE__m2),  sep=' ', end='\n')
    print((_GOLITE__m1 != _GOLITE__m2),  sep=' ', end='\n')
    _GOLITE__m3 = _GOLITE__empty()
    _GOLITE__m4 = _GOLITE__empty()
    print((_GOLITE__m3 == _GOLITE__m4),  sep=' ', end='\n')
    print((_GOLITE__m3 != _GOLITE__m4),  sep=' ', end='\n')
    _GOLITE__b1 = _GOLITE__blank()
    _GOLITE__b2 = _GOLITE__blank()
    print((_GOLITE__b1 == _GOLITE__b2),  sep=' ', end='\n')
    print((_GOLITE__b1 != _GOLITE__b2),  sep=' ', end='\n')

if __name__ == "__main__":
    main()