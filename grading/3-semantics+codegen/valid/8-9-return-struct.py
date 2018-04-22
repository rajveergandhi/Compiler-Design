# import all necessary Python libraries
from __future__ import print_function
import copy

class _GOLITE__my:
    _GOLITE__a = 0

_GOLITE__a = _GOLITE__my()
def _GOLITE__foo():
    global _GOLITE__a
    _GOLITE__a._GOLITE__a = 1
    return _GOLITE__a

def main():
    global _GOLITE__a
    _GOLITE__b =     _GOLITE__foo()

    _GOLITE__a._GOLITE__a = 2
    print(str(_GOLITE__a._GOLITE__a).lower() if type(_GOLITE__a._GOLITE__a) is bool else _GOLITE__a._GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b._GOLITE__a).lower() if type(_GOLITE__b._GOLITE__a) is bool else _GOLITE__b._GOLITE__a,  sep=' ', end='\n')

if __name__ == "__main__":
    main()