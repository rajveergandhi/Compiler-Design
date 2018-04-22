# import all necessary Python libraries
from __future__ import print_function
import copy

def main():
    print(str(255).lower() if type(255) is bool else 255,  sep=' ', end='\n')
    print(str(255).lower() if type(255) is bool else 255,  sep=' ', end='\n')
    print(str(255).lower() if type(255) is bool else 255,  sep=' ', end='\n')
    print(str(0.120000).lower() if type(0.120000) is bool else 0.120000,  sep=' ', end='\n')
    print(str(0.120000).lower() if type(0.120000) is bool else 0.120000,  sep=' ', end='\n')
    print(str(12.000000).lower() if type(12.000000) is bool else 12.000000,  sep=' ', end='\n')
    print(str(True).lower() if type(True) is bool else True,  sep=' ', end='\n')
    print(str(False).lower() if type(False) is bool else False,  sep=' ', end='\n')
    print(str(76).lower() if type(76) is bool else 76,  sep=' ', end='\n')
    print(str(10).lower() if type(10) is bool else 10,  sep=' ', end='\n')
    print(str("hello\n").lower() if type("hello\n") is bool else "hello\n",  sep=' ', end='\n')
    print(str(r"hello\n").lower() if type(r"hello\n") is bool else r"hello\n",  sep=' ', end='\n')

if __name__ == "__main__":
    main()