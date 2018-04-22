# import all necessary Python libraries
from __future__ import print_function
import copy

_GOLITE__glob = 0
_GOLITE__array = [0] * 6
def _GOLITE__foo():
    global _GOLITE__array
    global _GOLITE__glob
    _GOLITE__glob+= 1
    return _GOLITE__glob

def _GOLITE__bar(_GOLITE__a):
    global _GOLITE__array
    global _GOLITE__glob
    print(str(_GOLITE__a).lower() if type(_GOLITE__a) is bool else _GOLITE__a,  sep=' ', end='\n')
    return _GOLITE__a

def _GOLITE__baz():
    global _GOLITE__array
    global _GOLITE__glob
    _GOLITE__glob+= 1
    return copy.deepcopy(_GOLITE__array)

def main():
    global _GOLITE__array
    global _GOLITE__glob
    _GOLITE__array[0] = 0
    _GOLITE__array[1] = 1
    _GOLITE__array[2] = 2
    _GOLITE__array[3] = 3
    _GOLITE__array[4] = 4
    _GOLITE__array[5] = 5
    print(str(_GOLITE__glob).lower() if type(_GOLITE__glob) is bool else _GOLITE__glob, str(    _GOLITE__foo()
).lower() if type(    _GOLITE__foo()
) is bool else     _GOLITE__foo()
, str(_GOLITE__glob).lower() if type(_GOLITE__glob) is bool else _GOLITE__glob,  sep=' ', end='\n')
    print(str(    _GOLITE__foo()
).lower() if type(    _GOLITE__foo()
) is bool else     _GOLITE__foo()
, str(_GOLITE__array[    _GOLITE__foo()
]).lower() if type(_GOLITE__array[    _GOLITE__foo()
]) is bool else _GOLITE__array[    _GOLITE__foo()
], str(_GOLITE__array[    _GOLITE__foo()
]).lower() if type(_GOLITE__array[    _GOLITE__foo()
]) is bool else _GOLITE__array[    _GOLITE__foo()
], str(    _GOLITE__foo()
).lower() if type(    _GOLITE__foo()
) is bool else     _GOLITE__foo()
,  sep=' ', end='\n')
    print(str(    _GOLITE__bar(    _GOLITE__bar(0)
)
).lower() if type(    _GOLITE__bar(    _GOLITE__bar(0)
)
) is bool else     _GOLITE__bar(    _GOLITE__bar(0)
)
, str(    _GOLITE__bar(1)
).lower() if type(    _GOLITE__bar(1)
) is bool else     _GOLITE__bar(1)
,  sep=' ', end='\n')
    _GOLITE__glob = 0
    print(str(    _GOLITE__baz()
[_GOLITE__glob]).lower() if type(    _GOLITE__baz()
[_GOLITE__glob]) is bool else     _GOLITE__baz()
[_GOLITE__glob],  sep=' ', end='\n')
    print(str(    _GOLITE__bar(    _GOLITE__baz()
[_GOLITE__glob])
).lower() if type(    _GOLITE__bar(    _GOLITE__baz()
[_GOLITE__glob])
) is bool else     _GOLITE__bar(    _GOLITE__baz()
[_GOLITE__glob])
,  sep=' ', end='\n')

if __name__ == "__main__":
    main()