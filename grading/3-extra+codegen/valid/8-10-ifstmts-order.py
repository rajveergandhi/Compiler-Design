# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__glob = 0
def _GOLITE__foo():
    global _GOLITE__glob
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__bar(_GOLITE__a, _GOLITE__b):
    global _GOLITE__glob
    return (_GOLITE__a > _GOLITE__b)

def main():
    global _GOLITE__glob
    if (    _GOLITE__bar(    _GOLITE__foo()
,     _GOLITE__foo()
)
 == False):
        print(str("True").lower() if type("True") is bool else "True",  sep=' ', end='\n')
    else:
        print(str("False").lower() if type("False") is bool else "False",  sep=' ', end='\n')


if __name__ == "__main__":
    main()