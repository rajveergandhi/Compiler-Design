# import all necessary Python libraries
from __future__ import print_function
_GOLITE__g = 0
def _GOLITE__bar(_GOLITE__a):
    print(_GOLITE__a,  sep=' ', end='\n')
    _GOLITE__g+= 1
    return _GOLITE__g

def main():
    _GOLITE__a = False
    _GOLITE__b = 0
    _GOLITE__c = 0
    _GOLITE__a, _GOLITE__b, _GOLITE__c = ((    _GOLITE__bar("lhs1")
 == 2) or (    _GOLITE__bar("rhs1")
 == 3)), _GOLITE__g,     _GOLITE__bar("call3")

    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    print(_GOLITE__c,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__b, _GOLITE__c = ((    _GOLITE__bar("lhs1")
 == 4) and (    _GOLITE__bar("rhs1")
 == 6)), _GOLITE__g,     _GOLITE__bar("call3")

    print(_GOLITE__a,  sep=' ', end='\n')
    print(_GOLITE__b,  sep=' ', end='\n')
    print(_GOLITE__c,  sep=' ', end='\n')

if __name__ == "__main__":
    main()