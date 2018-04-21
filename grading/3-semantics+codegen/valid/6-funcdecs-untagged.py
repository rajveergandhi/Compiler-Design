# import all necessary Python libraries
from __future__ import print_function

def _GOLITE__f(_GOLITE__a):
    print(str(_GOLITE__a._GOLITE__a).lower() if type(_GOLITE__a._GOLITE__a) is bool else _GOLITE__a._GOLITE__a,  sep=' ', end='\n')

def main():
    class _GOLITE__a__:
        _GOLITE__a = 0
    _GOLITE__a = _GOLITE__a__()

    class _GOLITE__b__:
        _GOLITE__a = 0
    _GOLITE__b = _GOLITE__b__()

    _GOLITE__a._GOLITE__a = 1
    _GOLITE__b = _GOLITE__a
    _GOLITE__f(_GOLITE__a)
    _GOLITE__f(_GOLITE__b)

if __name__ == "__main__":
    main()