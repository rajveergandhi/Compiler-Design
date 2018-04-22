# import all necessary Python libraries
from __future__ import print_function
<<<<<<< HEAD
import copy
=======
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790

def _GOLITE__f(_GOLITE__a):
    _GOLITE__a[1] = 2

def main():
    _GOLITE__a = [0] * 2
    _GOLITE__a[0] = 1
    _GOLITE__a[1] = 1
    print(str(_GOLITE__a[1]).lower() if type(_GOLITE__a[1]) is bool else _GOLITE__a[1],  sep=' ', end='\n')
<<<<<<< HEAD
    _GOLITE__f(copy.deepcopy(_GOLITE__a))
=======
    _GOLITE__f(_GOLITE__a)
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790
    print(str(_GOLITE__a[1]).lower() if type(_GOLITE__a[1]) is bool else _GOLITE__a[1],  sep=' ', end='\n')

if __name__ == "__main__":
    main()