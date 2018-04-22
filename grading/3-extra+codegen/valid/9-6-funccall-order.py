# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__glob = 0
_GOLITE__a = [0] * 5
def _GOLITE__foo(_GOLITE__a, _GOLITE__b):
    global _GOLITE__a
    global _GOLITE__glob
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b,  sep=' ', end='\n')

def _GOLITE__bar():
    global _GOLITE__a
    global _GOLITE__glob
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__baz(_GOLITE__b):
    global _GOLITE__a
    global _GOLITE__glob
    _GOLITE__a[0] = 10
    _GOLITE__a[1] = 11
    _GOLITE__a[2] = 12
    _GOLITE__a[3] = 13
    _GOLITE__a[4] = 14
    return _GOLITE__b

def main():
    global _GOLITE__a
    global _GOLITE__glob
    _GOLITE__glob = 0
    _GOLITE__a[0] = 0
    _GOLITE__a[1] = 1
    _GOLITE__a[2] = 2
    _GOLITE__a[3] = 3
    _GOLITE__a[4] = 4
    _GOLITE__foo(_GOLITE__a[    _GOLITE__bar()
],     _GOLITE__baz(    _GOLITE__bar()
)
)

if __name__ == "__main__":
    main()