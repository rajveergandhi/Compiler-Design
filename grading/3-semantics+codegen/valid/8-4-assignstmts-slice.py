# import all necessary Python libraries
from __future__ import print_function
def main():
    _GOLITE__m1 = []
    _GOLITE__m2 = []
    _GOLITE__m1.append(1)
    _GOLITE__m2 = _GOLITE__m1
    print(_GOLITE__m1[0],  sep=' ', end='\n')
    print(_GOLITE__m2[0],  sep=' ', end='\n')
    _GOLITE__m2[0] = 2
    print(_GOLITE__m1[0],  sep=' ', end='\n')
    print(_GOLITE__m2[0],  sep=' ', end='\n')

if __name__ == "__main__":
    main()