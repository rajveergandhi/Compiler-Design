# import all necessary Python libraries
from __future__ import print_function
import copy

def _GOLITE__merge(_GOLITE__array, _GOLITE__temp, _GOLITE__lo, _GOLITE__hi):
    _GOLITE__mid = copy.deepcopy(((_GOLITE__lo + _GOLITE__hi) / 2))
    _GOLITE__temp_index = copy.deepcopy(_GOLITE__lo)
    _GOLITE__index_left = copy.deepcopy(_GOLITE__lo)
    _GOLITE__index_right = copy.deepcopy((_GOLITE__mid + 1))
    while ((_GOLITE__index_left <= _GOLITE__mid) and (_GOLITE__index_right <= _GOLITE__hi)):
        if (_GOLITE__array[_GOLITE__index_left] < _GOLITE__array[_GOLITE__index_right]):
            _GOLITE__temp[_GOLITE__temp_index] = copy.deepcopy(_GOLITE__array[_GOLITE__index_left])
            _GOLITE__index_left+= 1
        else:
            _GOLITE__temp[_GOLITE__temp_index] = copy.deepcopy(_GOLITE__array[_GOLITE__index_right])
            _GOLITE__index_right+= 1

        _GOLITE__temp_index+= 1

    while (_GOLITE__index_right <= _GOLITE__hi):
        _GOLITE__temp[_GOLITE__temp_index] = copy.deepcopy(_GOLITE__array[_GOLITE__index_right])
        _GOLITE__index_right+= 1
        _GOLITE__temp_index+= 1

    while (_GOLITE__index_left <= _GOLITE__mid):
        _GOLITE__temp[_GOLITE__temp_index] = copy.deepcopy(_GOLITE__array[_GOLITE__index_left])
        _GOLITE__index_left+= 1
        _GOLITE__temp_index+= 1

    _GOLITE__i = copy.deepcopy(_GOLITE__lo)
    while (_GOLITE__i <= _GOLITE__hi):
        _GOLITE__array[_GOLITE__i] = copy.deepcopy(_GOLITE__temp[_GOLITE__i])
        _GOLITE__i+= 1

def _GOLITE__merge_sort_helper(_GOLITE__array, _GOLITE__temp, _GOLITE__lo, _GOLITE__hi):
    if (_GOLITE__lo >= _GOLITE__hi):
        return

    _GOLITE__mid = copy.deepcopy(((_GOLITE__lo + _GOLITE__hi) / 2))
    _GOLITE__merge_sort_helper(_GOLITE__array, _GOLITE__temp, _GOLITE__lo, _GOLITE__mid)
    _GOLITE__merge_sort_helper(_GOLITE__array, _GOLITE__temp, (_GOLITE__mid + 1), _GOLITE__hi)
    _GOLITE__merge(_GOLITE__array, _GOLITE__temp, _GOLITE__lo, _GOLITE__hi)

def _GOLITE__merge_sort(_GOLITE__array, _GOLITE__length):
    _GOLITE__temp = []
    _GOLITE__i = copy.deepcopy(0)
    while (_GOLITE__i < _GOLITE__length):
        _GOLITE__temp = copy.deepcopy(_GOLITE__temp + [_GOLITE__array[_GOLITE__i]])
        _GOLITE__i+= 1
    _GOLITE__merge_sort_helper(_GOLITE__array, _GOLITE__temp, 0, (_GOLITE__length - 1))

def main():
    _GOLITE__array = []
    _GOLITE__length = copy.deepcopy(10000000)
    _GOLITE__i = copy.deepcopy(0)
    while (_GOLITE__i < _GOLITE__length):
        _GOLITE__array = copy.deepcopy(_GOLITE__array + [((_GOLITE__length - _GOLITE__i) - 1)])
        _GOLITE__i+= 1
    _GOLITE__merge_sort(_GOLITE__array, _GOLITE__length)
    _GOLITE__i = copy.deepcopy(0)
    while (_GOLITE__i < 10):
        print(_GOLITE__array[_GOLITE__i],  sep=' ', end='\n')
        _GOLITE__i+= 1

if __name__ == "__main__":
    main()