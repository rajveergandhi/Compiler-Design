# import all necessary Python libraries
from __future__ import print_function
import copy

def main():
    _GOLITE__s1 = "apple"
    _GOLITE__s2 = "pear"
    _GOLITE__s3 = (_GOLITE__s1 + _GOLITE__s2)
    print(str(_GOLITE__s3).lower() if type(_GOLITE__s3) is bool else _GOLITE__s3,  sep=' ', end='\n')
    _GOLITE__s4 = "apple"
    print(str((_GOLITE__s1 == _GOLITE__s4)).lower() if type((_GOLITE__s1 == _GOLITE__s4)) is bool else (_GOLITE__s1 == _GOLITE__s4), str((_GOLITE__s1 == _GOLITE__s2)).lower() if type((_GOLITE__s1 == _GOLITE__s2)) is bool else (_GOLITE__s1 == _GOLITE__s2),  sep=' ', end='\n')
    print(str((_GOLITE__s1 != _GOLITE__s4)).lower() if type((_GOLITE__s1 != _GOLITE__s4)) is bool else (_GOLITE__s1 != _GOLITE__s4), str((_GOLITE__s1 != _GOLITE__s2)).lower() if type((_GOLITE__s1 != _GOLITE__s2)) is bool else (_GOLITE__s1 != _GOLITE__s2),  sep=' ', end='\n')
    print(str((_GOLITE__s1 > _GOLITE__s4)).lower() if type((_GOLITE__s1 > _GOLITE__s4)) is bool else (_GOLITE__s1 > _GOLITE__s4), str((_GOLITE__s1 > _GOLITE__s2)).lower() if type((_GOLITE__s1 > _GOLITE__s2)) is bool else (_GOLITE__s1 > _GOLITE__s2),  sep=' ', end='\n')
    print(str((_GOLITE__s1 < _GOLITE__s4)).lower() if type((_GOLITE__s1 < _GOLITE__s4)) is bool else (_GOLITE__s1 < _GOLITE__s4), str((_GOLITE__s1 < _GOLITE__s2)).lower() if type((_GOLITE__s1 < _GOLITE__s2)) is bool else (_GOLITE__s1 < _GOLITE__s2),  sep=' ', end='\n')
    print(str(("apple" == "Apple")).lower() if type(("apple" == "Apple")) is bool else ("apple" == "Apple"),  sep=' ', end='\n')
    print(str(("apple" != "Apple")).lower() if type(("apple" != "Apple")) is bool else ("apple" != "Apple"),  sep=' ', end='\n')
    print(str(("apple" > "Apple")).lower() if type(("apple" > "Apple")) is bool else ("apple" > "Apple"),  sep=' ', end='\n')
    print(str(("apple" < "Apple")).lower() if type(("apple" < "Apple")) is bool else ("apple" < "Apple"),  sep=' ', end='\n')

if __name__ == "__main__":
    main()