# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__size = copy.deepcopy(25000)
_GOLITE__arr = [0] * 25000
def _GOLITE__insertionSort():
    _GOLITE__j = copy.deepcopy(0)
    while (_GOLITE__j < _GOLITE__size):
        _GOLITE__key = copy.deepcopy(_GOLITE__arr[_GOLITE__j])
        _GOLITE__i = copy.deepcopy((_GOLITE__j - 1))
        while ((_GOLITE__i >= 0) and (_GOLITE__arr[_GOLITE__i] > _GOLITE__key)):
            _GOLITE__arr[(_GOLITE__i + 1)] = copy.deepcopy(_GOLITE__arr[_GOLITE__i])
            _GOLITE__i = copy.deepcopy((_GOLITE__i - 1))

        _GOLITE__arr[(_GOLITE__i + 1)] = copy.deepcopy(_GOLITE__key)
        _GOLITE__j+= 1

def main():
    _GOLITE__j = copy.deepcopy((_GOLITE__size - 1))
    while (_GOLITE__j >= 0):
        _GOLITE__arr[((_GOLITE__size - _GOLITE__j) - 1)] = copy.deepcopy(_GOLITE__j)
        _GOLITE__j-= 1
    _GOLITE__insertionSort()
    _GOLITE__i = copy.deepcopy(0)
    while (_GOLITE__i < 10):
        print(_GOLITE__arr[_GOLITE__i],  sep=' ', end='\n')
        _GOLITE__i+= 1

if __name__ == "__main__":
    main()