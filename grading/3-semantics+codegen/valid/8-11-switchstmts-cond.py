# import all necessary Python libraries
from __future__ import print_function
_GOLITE__glob = 0
def _GOLITE__inc():
    _GOLITE__glob+= 1
    return _GOLITE__glob

def main():
    _GOLITE__a = True
    _GOLITE__b = True
    print(_GOLITE__a,  sep=' ', end='\n')
    _GOLITE__a = False
    if True == _GOLITE__a:
        print("a",  sep=' ', end='\n')
    elif True == _GOLITE__b:
        print("b",  sep=' ', end='\n')
    else:
        print("default",  sep=' ', end='\n')
    if _GOLITE__a == True:
            print("default",  sep=' ', end='\n')
    _GOLITE__switchFuncCall = _GOLITE__inc()
    if _GOLITE__switchFuncCall == 0:
        print("0",  sep=' ', end='\n')
    elif _GOLITE__switchFuncCall == 1:
        print("1",  sep=' ', end='\n')

if __name__ == "__main__":
    main()