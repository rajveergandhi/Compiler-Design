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
    while     _GOLITE__bar(    _GOLITE__foo()
,     _GOLITE__foo()
)
:
        print(str("Loop").lower() if type("Loop") is bool else "Loop",  sep=' ', end='\n')
        break

    print(str("End").lower() if type("End") is bool else "End",  sep=' ', end='\n')

if __name__ == "__main__":
    main()