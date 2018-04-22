# import all necessary Python libraries
from __future__ import print_function
<<<<<<< HEAD
import copy
=======
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790

_GOLITE__size = 25000
_GOLITE__arr = [0] * 25000
def _GOLITE__insertionSort():
    global _GOLITE__arr
    global _GOLITE__size
    _GOLITE__j = 0
    while (_GOLITE__j < _GOLITE__size):
        _GOLITE__key = _GOLITE__arr[_GOLITE__j]
        _GOLITE__i = (_GOLITE__j - 1)
        while ((_GOLITE__i >= 0) and (_GOLITE__arr[_GOLITE__i] > _GOLITE__key)):
            _GOLITE__arr[(_GOLITE__i + 1)] = _GOLITE__arr[_GOLITE__i]
            _GOLITE__i = (_GOLITE__i - 1)

        _GOLITE__arr[(_GOLITE__i + 1)] = _GOLITE__key
        _GOLITE__j+= 1

def main():
    global _GOLITE__arr
    global _GOLITE__size
    _GOLITE__j = (_GOLITE__size - 1)
    while (_GOLITE__j >= 0):
        _GOLITE__arr[((_GOLITE__size - _GOLITE__j) - 1)] = _GOLITE__j
        _GOLITE__j-= 1
    _GOLITE__insertionSort()
    _GOLITE__i = 0
    while (_GOLITE__i < 10):
        print(str(_GOLITE__arr[_GOLITE__i]).lower() if type(_GOLITE__arr[_GOLITE__i]) is bool else _GOLITE__arr[_GOLITE__i],  sep=' ', end='\n')
        _GOLITE__i+= 1

if __name__ == "__main__":
    main()