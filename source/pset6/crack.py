# -*- coding: utf-8 -*-

import sys
from cracker import CrackDES

def main():
    #Try to crack the password given as a command line argument
    if len(sys.argv) != 2:
        print("Usage {} passwd".format(sys.argv[0]), file = sys.stderr)
        exit(1)
    encryptedPassword = sys.argv[0]
    cracker = CrackDES()
    cracker.use_dictionary("/usr/share/dict/words")
    cracker.crack_password(encryptedPassword)
    print(cracker.get_cracked_password())


if __name__=="__main__":
    main()