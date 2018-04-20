# import all necessary Python libraries
from __future__ import print_function
_GOLITE__count = 0
def _GOLITE__towers(_GOLITE__num, _GOLITE__from, _GOLITE__to, _GOLITE__aux):
    if (_GOLITE__num == 1):
        _GOLITE__count+= 1
        return

    _GOLITE__towers((_GOLITE__num - 1), _GOLITE__from, _GOLITE__aux, _GOLITE__to)
    _GOLITE__count+= 1
    _GOLITE__towers((_GOLITE__num - 1), _GOLITE__aux, _GOLITE__to, _GOLITE__from)

def main():
    _GOLITE__towers(28, 65, 67, 66)
    print("Number of moves:", _GOLITE__count,  sep=' ', end='\n')

if __name__ == "__main__":
    main()