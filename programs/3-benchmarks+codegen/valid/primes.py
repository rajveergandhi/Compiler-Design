# import all necessary Python libraries
from __future__ import print_function
import copy

def main():
    _GOLITE__iTHprimeNumber = 1000000
    _GOLITE__primeNumbers = []
    _GOLITE__primeNumbers.append(2)
    _GOLITE__sqrt = 2
    _GOLITE__square = 4
    _GOLITE__counter = 1
    _GOLITE__number = 2
    _GOLITE__lastPrime = 2
    _GOLITE__i = 0
    _GOLITE__temp = 0
    _GOLITE__isPrime = 1
    _GOLITE__numPrimes = 1
    while (_GOLITE__counter < _GOLITE__iTHprimeNumber):
        _GOLITE__number+= 1
        if (_GOLITE__number > _GOLITE__square):
            _GOLITE__sqrt+= 1
            _GOLITE__square = (_GOLITE__sqrt * _GOLITE__sqrt)

        _GOLITE__isPrime = 1
        _GOLITE__i = 0
        while (_GOLITE__i < _GOLITE__numPrimes):
            _GOLITE__temp = _GOLITE__primeNumbers[_GOLITE__i]
            if (_GOLITE__temp > _GOLITE__sqrt):
                break

            if ((_GOLITE__number % _GOLITE__temp) == 0):
                _GOLITE__isPrime = 0
                break

            _GOLITE__i+= 1
        if (_GOLITE__isPrime == 1):
            _GOLITE__primeNumbers.append(_GOLITE__number)
            _GOLITE__numPrimes+= 1
            _GOLITE__lastPrime = _GOLITE__number
            _GOLITE__counter+= 1


    print("Last prime:", _GOLITE__lastPrime,  sep=' ', end='\n')

if __name__ == "__main__":
    main()