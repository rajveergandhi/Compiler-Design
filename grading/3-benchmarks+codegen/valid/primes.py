# import all necessary Python libraries
from __future__ import print_function

def main():
    _GOLITE__iTHprimeNumber = 1000000
    _GOLITE__primeNumbers = []
    if '_GOLITE__primeNumbers' not in locals() and '_GOLITE__primeNumbers' in globals():
        global _GOLITE__primeNumbers
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
        if '_GOLITE__number' not in locals() and '_GOLITE__number' in globals():
            global _GOLITE__number
        _GOLITE__number+= 1
        if (_GOLITE__number > _GOLITE__square):
            if '_GOLITE__sqrt' not in locals() and '_GOLITE__sqrt' in globals():
                global _GOLITE__sqrt
            _GOLITE__sqrt+= 1
            if '_GOLITE__square' not in locals() and '_GOLITE__square' in globals():
                global _GOLITE__square
            _GOLITE__square = (_GOLITE__sqrt * _GOLITE__sqrt)

        if '_GOLITE__isPrime' not in locals() and '_GOLITE__isPrime' in globals():
            global _GOLITE__isPrime
        _GOLITE__isPrime = 1
        if '_GOLITE__i' not in locals() and '_GOLITE__i' in globals():
            global _GOLITE__i
        _GOLITE__i = 0
        while (_GOLITE__i < _GOLITE__numPrimes):
            if '_GOLITE__temp' not in locals() and '_GOLITE__temp' in globals():
                global _GOLITE__temp
            _GOLITE__temp = _GOLITE__primeNumbers[_GOLITE__i]
            if (_GOLITE__temp > _GOLITE__sqrt):
                break

            if ((_GOLITE__number % _GOLITE__temp) == 0):
                if '_GOLITE__isPrime' not in locals() and '_GOLITE__isPrime' in globals():
                    global _GOLITE__isPrime
                _GOLITE__isPrime = 0
                break

            if '_GOLITE__i' not in locals() and '_GOLITE__i' in globals():
                global _GOLITE__i
            _GOLITE__i+= 1
        if (_GOLITE__isPrime == 1):
            if '_GOLITE__primeNumbers' not in locals() and '_GOLITE__primeNumbers' in globals():
                global _GOLITE__primeNumbers
            _GOLITE__primeNumbers.append(_GOLITE__number)
            if '_GOLITE__numPrimes' not in locals() and '_GOLITE__numPrimes' in globals():
                global _GOLITE__numPrimes
            _GOLITE__numPrimes+= 1
            if '_GOLITE__lastPrime' not in locals() and '_GOLITE__lastPrime' in globals():
                global _GOLITE__lastPrime
            _GOLITE__lastPrime = _GOLITE__number
            if '_GOLITE__counter' not in locals() and '_GOLITE__counter' in globals():
                global _GOLITE__counter
            _GOLITE__counter+= 1


    print(str("Last prime:").lower() if type("Last prime:") is bool else "Last prime:", str(_GOLITE__lastPrime).lower() if type(_GOLITE__lastPrime) is bool else _GOLITE__lastPrime,  sep=' ', end='\n')

if __name__ == "__main__":
    main()