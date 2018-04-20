# import all necessary Python libraries
from __future__ import print_function
class _GOLITE__point:
    _GOLITE__x = 0
    _GOLITE__y = 0

_GOLITE__chessGridSize = 27
_GOLITE__queens = []
def _GOLITE__queenRecursion(_GOLITE__index):
    if (_GOLITE__index >= _GOLITE__chessGridSize):
        return 1

    _GOLITE__i = 0
    _GOLITE__j = 0
    _GOLITE__p = _GOLITE__point()
    _GOLITE__allgood = 0
    _GOLITE__p2 = _GOLITE__point()
    _GOLITE__solutionFound = 0
    _GOLITE__p = _GOLITE__queens[_GOLITE__index]
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__chessGridSize):
        _GOLITE__p._GOLITE__x = _GOLITE__i
        _GOLITE__allgood = 1
        _GOLITE__j = 0
        while (_GOLITE__j < _GOLITE__index):
            _GOLITE__p2 = _GOLITE__queens[_GOLITE__j]
            if (((_GOLITE__p._GOLITE__x == _GOLITE__p2._GOLITE__x) or ((_GOLITE__p2._GOLITE__y - _GOLITE__p._GOLITE__y) == (_GOLITE__p2._GOLITE__x - _GOLITE__p._GOLITE__x))) or ((_GOLITE__p2._GOLITE__y - _GOLITE__p._GOLITE__y) == (_GOLITE__p._GOLITE__x - _GOLITE__p2._GOLITE__x))):
                _GOLITE__allgood = 0
                break

            _GOLITE__j+= 1
        if (_GOLITE__allgood == 1):
            _GOLITE__queens[_GOLITE__index] = _GOLITE__p
            if (            _GOLITE__queenRecursion((_GOLITE__index + 1))
 == 1):
                print("[",  sep='', end='')
                print(_GOLITE__p._GOLITE__x,  sep='', end='')
                print(", ",  sep='', end='')
                print(_GOLITE__p._GOLITE__y,  sep='', end='')
                print("]",  sep=' ', end='\n')
                _GOLITE__solutionFound = 1
                break


        _GOLITE__i+= 1
    return _GOLITE__solutionFound

def main():
    _GOLITE__i = 0
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__chessGridSize):
        _GOLITE__p = _GOLITE__point()
        _GOLITE__p._GOLITE__x = 0
        _GOLITE__p._GOLITE__y = _GOLITE__i
        _GOLITE__queens.append(_GOLITE__p)
        _GOLITE__i+= 1
    _GOLITE__queenRecursion(0)

if __name__ == "__main__":
    main()