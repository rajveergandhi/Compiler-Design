# import all necessary Python libraries
from __future__ import print_function
def _GOLITE__f(_GOLITE__a):
    _GOLITE__a.append(2)

def main():
    _GOLITE__a = []
    _GOLITE__a.append(1)
    _GOLITE__f(_GOLITE__a)
    print(_GOLITE__a[1],  sep=' ', end='\n')

if __name__ == "__main__":
    main()