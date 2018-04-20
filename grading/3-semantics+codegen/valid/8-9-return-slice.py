# import all necessary Python libraries
from __future__ import print_function
_GOLITE__a = []
def _GOLITE__foo():
    return _GOLITE__a

def main():
    _GOLITE__a.append(1)
    _GOLITE__b =     _GOLITE__foo()

    _GOLITE__a[0] = 2
    print(_GOLITE__a[0],  sep=' ', end='\n')
    print(_GOLITE__b[0],  sep=' ', end='\n')

if __name__ == "__main__":
    main()