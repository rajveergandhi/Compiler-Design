# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__a = []
def _GOLITE__foo():
    global _GOLITE__a
    return copy.deepcopy(_GOLITE__a)

def main():
    global _GOLITE__a
    _GOLITE__a.append(1)
    _GOLITE__b =     _GOLITE__foo()

    _GOLITE__a[0] = 2
    print(str(_GOLITE__a[0]).lower() if type(_GOLITE__a[0]) is bool else _GOLITE__a[0],  sep=' ', end='\n')
    print(str(_GOLITE__b[0]).lower() if type(_GOLITE__b[0]) is bool else _GOLITE__b[0],  sep=' ', end='\n')

if __name__ == "__main__":
    main()