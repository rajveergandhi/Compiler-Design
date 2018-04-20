# import all necessary Python libraries
from __future__ import print_function
_GOLITE__glob = 0
def _GOLITE__foo(_GOLITE__a, _GOLITE__b):
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    return (_GOLITE__a + _GOLITE__b)

def _GOLITE__bar():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def main():
    _GOLITE__a =     _GOLITE__foo(    _GOLITE__bar()
,     _GOLITE__bar()
)

    print(_GOLITE__a,  sep=' ', end='\n')

if __name__ == "__main__":
    main()