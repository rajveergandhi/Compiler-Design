# import all necessary Python libraries
from __future__ import print_function

def main():
    _GOLITE__a = 3
    _GOLITE__b = 1
    print(str((_GOLITE__a & ~_GOLITE__b)).lower() if type((_GOLITE__a & ~_GOLITE__b)) is bool else (_GOLITE__a & ~_GOLITE__b),  sep=' ', end='\n')

if __name__ == "__main__":
    main()