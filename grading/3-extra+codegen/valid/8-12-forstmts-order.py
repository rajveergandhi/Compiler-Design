# import all necessary Python libraries
from __future__ import print_function
_GOLITE__glob = 0
def _GOLITE__foo():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__bar(_GOLITE__a, _GOLITE__b):
    return (_GOLITE__a > _GOLITE__b)

def main():
    while     _GOLITE__bar(    _GOLITE__foo()
,     _GOLITE__foo()
)
:
        print("Loop",  sep=' ', end='\n')
        break

    print("End",  sep=' ', end='\n')

if __name__ == "__main__":
    main()