# import all necessary Python libraries
from __future__ import print_function

_GOLITE__glob = 0
def _GOLITE__inc():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def main():
    _GOLITE__a = True
    _GOLITE__b = True
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    _GOLITE__a = False
    if True == _GOLITE__a:
        print(str("a").lower() if type("a") is bool else "a",  sep=' ', end='\n')
    elif True == _GOLITE__b:
        print(str("b").lower() if type("b") is bool else "b",  sep=' ', end='\n')
    else:
        print(str("default").lower() if type("default") is bool else "default",  sep=' ', end='\n')
    if _GOLITE__a == True:
            print(str("default").lower() if type("default") is bool else "default",  sep=' ', end='\n')
    _GOLITE__switchFuncCall = _GOLITE__inc()
    if _GOLITE__switchFuncCall == 0:
        print(str("0").lower() if type("0") is bool else "0",  sep=' ', end='\n')
    elif _GOLITE__switchFuncCall == 1:
        print(str("1").lower() if type("1") is bool else "1",  sep=' ', end='\n')

if __name__ == "__main__":
    main()