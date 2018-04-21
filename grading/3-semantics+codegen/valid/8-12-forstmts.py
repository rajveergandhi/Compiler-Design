# import all necessary Python libraries
from __future__ import print_function

def main():
    while True:
        print(str("infinite").lower() if type("infinite") is bool else "infinite",  sep=' ', end='\n')
        break

    _GOLITE__x = 0
    while (_GOLITE__x < 3):
        print(str(_GOLITE__x).lower() if type(_GOLITE__x) is bool else _GOLITE__x,  sep=' ', end='\n')
        _GOLITE__x+= 1

    _GOLITE__i = 0
    while (_GOLITE__i < 3):
        print(str(_GOLITE__i).lower() if type(_GOLITE__i) is bool else _GOLITE__i,  sep=' ', end='\n')
        _GOLITE__i+= 1
    _GOLITE__a, _GOLITE__b = 0, 0
    while (_GOLITE__a < 3):
        print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
        _GOLITE__a+= 1
        _GOLITE__b, _GOLITE__a = _GOLITE__a, _GOLITE__b
    _GOLITE__a = 0
    while (_GOLITE__a < 3):
        _GOLITE__a = 0
        print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
        _GOLITE__a+= 1
    _GOLITE__i = 0
    while (_GOLITE__i < 3):
        _GOLITE__i+= 1
        continue
        print(str(_GOLITE__i).lower() if type(_GOLITE__i) is bool else _GOLITE__i,  sep=' ', end='\n')
    print(str("Success").lower() if type("Success") is bool else "Success",  sep=' ', end='\n')

if __name__ == "__main__":
    main()