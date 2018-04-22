# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__g = 0
def _GOLITE__bar(_GOLITE__a):
    global _GOLITE__g
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    _GOLITE__g+= 1
    return _GOLITE__g

def main():
    global _GOLITE__g
    _GOLITE__a = False
    _GOLITE__b = 0
    _GOLITE__c = 0
    _GOLITE__a, _GOLITE__b, _GOLITE__c = ((    _GOLITE__bar("lhs1")
 == 2) or (    _GOLITE__bar("rhs1")
 == 3)), _GOLITE__g,     _GOLITE__bar("call3")

    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b,  sep=' ', end='\n')
    print(str(_GOLITE__c).lower() if type(_GOLITE__c) is bool else _GOLITE__c,  sep=' ', end='\n')
    _GOLITE__a, _GOLITE__b, _GOLITE__c = ((    _GOLITE__bar("lhs1")
 == 4) and (    _GOLITE__bar("rhs1")
 == 6)), _GOLITE__g,     _GOLITE__bar("call3")

    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b,  sep=' ', end='\n')
    print(str(_GOLITE__c).lower() if type(_GOLITE__c) is bool else _GOLITE__c,  sep=' ', end='\n')

if __name__ == "__main__":
    main()