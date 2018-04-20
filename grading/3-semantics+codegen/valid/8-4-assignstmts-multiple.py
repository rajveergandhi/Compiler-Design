# import all necessary Python libraries
from __future__ import print_function
def main():
    _GOLITE__a = 1
    _GOLITE__b = 2
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__a, _GOLITE__b = 3, 4, 5
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__b = _GOLITE__b, (_GOLITE__a + 1)
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__b, _GOLITE__c = 6, 7, 8
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    print(_GOLITE__c,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__b, _GOLITE__d = _GOLITE__b, _GOLITE__a, (_GOLITE__a + 1)
    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    print(_GOLITE__d,  sep=' ', end='\n')

if __name__ == "__main__":
    main()