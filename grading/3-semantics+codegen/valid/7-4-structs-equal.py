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
    print(str((_GOLITE__m1 == _GOLITE__m2)).lower() if type((_GOLITE__m1 == _GOLITE__m2)) is bool else (_GOLITE__m1 == _GOLITE__m2),  sep=' ', end='\n')
    print(str((_GOLITE__m1 != _GOLITE__m2)).lower() if type((_GOLITE__m1 != _GOLITE__m2)) is bool else (_GOLITE__m1 != _GOLITE__m2),  sep=' ', end='\n')
    _GOLITE__m2._GOLITE__a = 2
    print(str((_GOLITE__m1 == _GOLITE__m2)).lower() if type((_GOLITE__m1 == _GOLITE__m2)) is bool else (_GOLITE__m1 == _GOLITE__m2),  sep=' ', end='\n')
    print(str((_GOLITE__m1 != _GOLITE__m2)).lower() if type((_GOLITE__m1 != _GOLITE__m2)) is bool else (_GOLITE__m1 != _GOLITE__m2),  sep=' ', end='\n')
    _GOLITE__m3 = _GOLITE__empty()
    _GOLITE__m4 = _GOLITE__empty()
    print(str((_GOLITE__m3 == _GOLITE__m4)).lower() if type((_GOLITE__m3 == _GOLITE__m4)) is bool else (_GOLITE__m3 == _GOLITE__m4),  sep=' ', end='\n')
    print(str((_GOLITE__m3 != _GOLITE__m4)).lower() if type((_GOLITE__m3 != _GOLITE__m4)) is bool else (_GOLITE__m3 != _GOLITE__m4),  sep=' ', end='\n')
    _GOLITE__b1 = _GOLITE__blank()
    _GOLITE__b2 = _GOLITE__blank()
    print(str((_GOLITE__b1 == _GOLITE__b2)).lower() if type((_GOLITE__b1 == _GOLITE__b2)) is bool else (_GOLITE__b1 == _GOLITE__b2),  sep=' ', end='\n')
    print(str((_GOLITE__b1 != _GOLITE__b2)).lower() if type((_GOLITE__b1 != _GOLITE__b2)) is bool else (_GOLITE__b1 != _GOLITE__b2),  sep=' ', end='\n')

if __name__ == "__main__":
    main()