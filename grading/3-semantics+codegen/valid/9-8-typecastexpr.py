# import all necessary Python libraries
from __future__ import print_function

def main():
    _GOLITE__a = 64
    _GOLITE__b = (_GOLITE__a + 1)
    _GOLITE__c = chr(_GOLITE__a)
    _GOLITE__d = chr(97)
    _GOLITE__e = "a"
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    print(str(_GOLITE__b).lower() if type(_GOLITE__b) is bool else _GOLITE__b,  sep=' ', end='\n')
    print(str(_GOLITE__c).lower() if type(_GOLITE__c) is bool else _GOLITE__c,  sep=' ', end='\n')
    print(str(_GOLITE__d).lower() if type(_GOLITE__d) is bool else _GOLITE__d,  sep=' ', end='\n')
    print(str(_GOLITE__e).lower() if type(_GOLITE__e) is bool else _GOLITE__e,  sep=' ', end='\n')

if __name__ == "__main__":
    main()