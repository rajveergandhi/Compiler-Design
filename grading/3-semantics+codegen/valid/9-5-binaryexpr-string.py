# import all necessary Python libraries
from __future__ import print_function
def main():
    _GOLITE__s1 = "apple"
    _GOLITE__s2 = "pear"
    _GOLITE__s3 = (_GOLITE__s1 + _GOLITE__s2)
    print(_GOLITE__s3,  sep=' ', end='\n')
    _GOLITE__s4 = "apple"
    print((_GOLITE__s1 == _GOLITE__s4), (_GOLITE__s1 == _GOLITE__s2),  sep=' ', end='\n')
    print((_GOLITE__s1 != _GOLITE__s4), (_GOLITE__s1 != _GOLITE__s2),  sep=' ', end='\n')
    print((_GOLITE__s1 > _GOLITE__s4), (_GOLITE__s1 > _GOLITE__s2),  sep=' ', end='\n')
    print((_GOLITE__s1 < _GOLITE__s4), (_GOLITE__s1 < _GOLITE__s2),  sep=' ', end='\n')
    print(("apple" == "Apple"),  sep=' ', end='\n')
    print(("apple" != "Apple"),  sep=' ', end='\n')
    print(("apple" > "Apple"),  sep=' ', end='\n')
    print(("apple" < "Apple"),  sep=' ', end='\n')

if __name__ == "__main__":
    main()