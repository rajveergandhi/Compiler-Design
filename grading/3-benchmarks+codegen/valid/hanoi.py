# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__count = 0
def _GOLITE__towers(_GOLITE__num, _GOLITE__from, _GOLITE__to, _GOLITE__aux):
    global _GOLITE__count
    if (_GOLITE__num == 1):
        _GOLITE__count+= 1
        return

    _GOLITE__towers((_GOLITE__num - 1), _GOLITE__from, _GOLITE__aux, _GOLITE__to)
    _GOLITE__count+= 1
    _GOLITE__towers((_GOLITE__num - 1), _GOLITE__aux, _GOLITE__to, _GOLITE__from)

def main():
    global _GOLITE__count
    _GOLITE__towers(28, 65, 67, 66)
    print(str("Number of moves:").lower() if type("Number of moves:") is bool else "Number of moves:", str(_GOLITE__count).lower() if type(_GOLITE__count) is bool else _GOLITE__count,  sep=' ', end='\n')

if __name__ == "__main__":
    main()