# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__glob = 0
def _GOLITE__foo(_GOLITE__a, _GOLITE__b):
    global _GOLITE__glob
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b,  sep=' ', end='\n')
    return (_GOLITE__a + _GOLITE__b)

def _GOLITE__bar():
    global _GOLITE__glob
    _GOLITE__glob+= 1
    return _GOLITE__glob

def main():
    global _GOLITE__glob
    _GOLITE__a =     _GOLITE__foo(    _GOLITE__bar()
,     _GOLITE__bar()
)

    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')

if __name__ == "__main__":
    main()