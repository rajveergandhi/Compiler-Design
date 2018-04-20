# import all necessary Python libraries
from __future__ import print_function
_GOLITE__glob = 0
_GOLITE__a = [0] * 5
def _GOLITE__foo(_GOLITE__a, _GOLITE__b):
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')

def _GOLITE__bar():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__baz(_GOLITE__b):
    _GOLITE__a[0] = 10
    _GOLITE__a[1] = 11
    _GOLITE__a[2] = 12
    _GOLITE__a[3] = 13
    _GOLITE__a[4] = 14
    return _GOLITE__b

def main():
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