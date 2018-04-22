# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__a = 0
def _GOLITE__foo():
    global _GOLITE__a
    _GOLITE__a+= 1
    return _GOLITE__a

def main():
    global _GOLITE__a
    _GOLITE__b, _GOLITE__c, _GOLITE__d =     _GOLITE__foo()
, _GOLITE__a,     _GOLITE__foo()

    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b, str(_GOLITE__c).lower() if type(_GOLITE__c) is bool else _GOLITE__c, str(_GOLITE__d).lower() if type(_GOLITE__d) is bool else _GOLITE__d,  sep=' ', end='\n')

if __name__ == "__main__":
    main()