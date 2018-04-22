# import all necessary Python libraries
from __future__ import print_function
<<<<<<< HEAD
import copy
=======
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790

def main():
    _GOLITE__m1 = []
    _GOLITE__m2 = []
    _GOLITE__m1.append(1)
<<<<<<< HEAD
    _GOLITE__m2 = copy.deepcopy(_GOLITE__m1)
=======
    _GOLITE__m2 = _GOLITE__m1
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790
    print(str(_GOLITE__m1[0]).lower() if type(_GOLITE__m1[0]) is bool else _GOLITE__m1[0],  sep=' ', end='\n')
    print(str(_GOLITE__m2[0]).lower() if type(_GOLITE__m2[0]) is bool else _GOLITE__m2[0],  sep=' ', end='\n')
    _GOLITE__m2[0] = 2
    print(str(_GOLITE__m1[0]).lower() if type(_GOLITE__m1[0]) is bool else _GOLITE__m1[0],  sep=' ', end='\n')
    print(str(_GOLITE__m2[0]).lower() if type(_GOLITE__m2[0]) is bool else _GOLITE__m2[0],  sep=' ', end='\n')

if __name__ == "__main__":
    main()