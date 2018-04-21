# import all necessary Python libraries
from __future__ import print_function

def main():
    _GOLITE__a = 2
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    if _GOLITE__a == 1 or _GOLITE__a == 2:
        print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    else:
        print(str("default").lower() if type("default") is bool else "default",  sep=' ', end='\n')

if __name__ == "__main__":
    main()