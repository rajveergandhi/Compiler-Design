# import all necessary Python libraries
from __future__ import print_function
<<<<<<< HEAD
import copy
=======
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790

class _GOLITE__my:
    _GOLITE__a = 0

def _GOLITE__f(_GOLITE__m):
    _GOLITE__m._GOLITE__a = 2

def main():
    _GOLITE__m1 = _GOLITE__my()
    _GOLITE__m1._GOLITE__a = 1
    print(str(_GOLITE__m1._GOLITE__a).lower() if type(_GOLITE__m1._GOLITE__a) is bool else _GOLITE__m1._GOLITE__a,  sep=' ', end='\n')
    _GOLITE__f(_GOLITE__m1)
    print(str(_GOLITE__m1._GOLITE__a).lower() if type(_GOLITE__m1._GOLITE__a) is bool else _GOLITE__m1._GOLITE__a,  sep=' ', end='\n')

if __name__ == "__main__":
    main()