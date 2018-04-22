# import all necessary Python libraries
from __future__ import print_function
<<<<<<< HEAD
import copy
=======
>>>>>>> 69ce9bdc99e6a59688611a0184b0ff459fa28790

def _GOLITE__selection_sort(_GOLITE__array, _GOLITE__length):
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__length):
        _GOLITE__min = _GOLITE__array[_GOLITE__i]
        _GOLITE__min_index = _GOLITE__i
        _GOLITE__j = (_GOLITE__i + 1)
        while (_GOLITE__j < _GOLITE__length):
            if (_GOLITE__array[_GOLITE__j] < _GOLITE__min):
                _GOLITE__min = _GOLITE__array[_GOLITE__j]
                _GOLITE__min_index = _GOLITE__j

            _GOLITE__j+= 1
        if (_GOLITE__min_index != _GOLITE__i):
            _GOLITE__array[_GOLITE__min_index] = _GOLITE__array[_GOLITE__i]
            _GOLITE__array[_GOLITE__i] = _GOLITE__min

        _GOLITE__i+= 1

def main():
    _GOLITE__array = []
    _GOLITE__length = 50000
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__length):
        _GOLITE__array.append(((_GOLITE__length - _GOLITE__i) - 1))
        _GOLITE__i+= 1
    _GOLITE__selection_sort(_GOLITE__array, _GOLITE__length)
    _GOLITE__i = 0
    while (_GOLITE__i < 10):
        print(str(_GOLITE__array[_GOLITE__i]).lower() if type(_GOLITE__array[_GOLITE__i]) is bool else _GOLITE__array[_GOLITE__i],  sep=' ', end='\n')
        _GOLITE__i+= 1

if __name__ == "__main__":
    main()