# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__s = []
_GOLITE__cost_s = 0
_GOLITE__w = []
_GOLITE__r = 0
def _GOLITE__rand():
    global _GOLITE__r
    global _GOLITE__s
    global _GOLITE__w
    global _GOLITE__cost_s
    _GOLITE__r = (((8121 * _GOLITE__r) + 28411) % 134456)
    return _GOLITE__r

def _GOLITE__compute_cost(_GOLITE__n, _GOLITE__A):
    global _GOLITE__r
    global _GOLITE__s
    global _GOLITE__w
    global _GOLITE__cost_s
    _GOLITE__sum = 0
    _GOLITE__i = 0
    while (_GOLITE__i < (_GOLITE__n - 1)):
        _GOLITE__sum += _GOLITE__w[_GOLITE__A[_GOLITE__i]][_GOLITE__A[(_GOLITE__i + 1)]]
        _GOLITE__i+= 1
    return (_GOLITE__sum + _GOLITE__w[(_GOLITE__n - 1)][0])

def _GOLITE__permute(_GOLITE__n, _GOLITE__A):
    global _GOLITE__r
    global _GOLITE__s
    global _GOLITE__w
    global _GOLITE__cost_s
    _GOLITE__index = []
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__n):
        _GOLITE__index.append(0)
        _GOLITE__i+= 1
    _GOLITE__temp = 0
    _GOLITE__swap = 0
    _GOLITE__cost_i = 0
    _GOLITE__i = 1
    while (_GOLITE__i < _GOLITE__n):
        if (_GOLITE__index[_GOLITE__i] < _GOLITE__i):
            _GOLITE__swap = ((_GOLITE__i % 2) * _GOLITE__index[_GOLITE__i])
            _GOLITE__temp = _GOLITE__A[_GOLITE__swap]
            _GOLITE__A[_GOLITE__swap] = _GOLITE__A[_GOLITE__i]
            _GOLITE__A[_GOLITE__i] = _GOLITE__temp
            _GOLITE__cost_i =             _GOLITE__compute_cost(_GOLITE__n, _GOLITE__A)

            if (_GOLITE__cost_i < _GOLITE__cost_s):
                _GOLITE__cost_s = _GOLITE__cost_i
                _GOLITE__j = 0
                while (_GOLITE__j < (_GOLITE__n - 1)):
                    _GOLITE__s[_GOLITE__j] = _GOLITE__A[_GOLITE__j]
                    _GOLITE__j+= 1

            _GOLITE__index[_GOLITE__i]+= 1
            _GOLITE__i = 1
        else:
            _GOLITE__index[_GOLITE__i] = 0
            _GOLITE__i+= 1


def main():
    global _GOLITE__r
    global _GOLITE__s
    global _GOLITE__w
    global _GOLITE__cost_s
    _GOLITE__n = 11
    _GOLITE__i = 0
    while (_GOLITE__i < _GOLITE__n):
        _GOLITE__s.append(_GOLITE__i)
        _GOLITE__w_i = []
        _GOLITE__j = 0
        while (_GOLITE__j < _GOLITE__n):
            _GOLITE__w_i.append(            _GOLITE__rand()
)
            _GOLITE__j+= 1
        _GOLITE__w.append(_GOLITE__w_i)
        _GOLITE__i+= 1
    _GOLITE__cost_s =     _GOLITE__compute_cost(_GOLITE__n, _GOLITE__s)

    print(str("Ordered path cost:").lower() if type("Ordered path cost:") is bool else "Ordered path cost:", str(_GOLITE__cost_s).lower() if type(_GOLITE__cost_s) is bool else _GOLITE__cost_s,  sep=' ', end='\n')
    _GOLITE__permute(_GOLITE__n, _GOLITE__s)
    print(str("Optimal path cost:").lower() if type("Optimal path cost:") is bool else "Optimal path cost:", str(_GOLITE__cost_s).lower() if type(_GOLITE__cost_s) is bool else _GOLITE__cost_s,  sep=' ', end='\n')

if __name__ == "__main__":
    main()