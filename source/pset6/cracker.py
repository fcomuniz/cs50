import crypt
import itertools

MIN_ASCII_CHAR_VALUE = 32
MAX_ASCII_CHAR_VALUE = 127
printable_ascii=[]
for i in range(MIN_ASCII_CHAR_VALUE, MAX_ASCII_CHAR_VALUE):
    printable_ascii.append(chr(i))

def generate_ascii_permutations(size):
    return itertools.permutations(printable_ascii,r=size)


class CrackDES:

    def __init__(self):
        self.encryptedPassword = None
        self.decryptedPassword = None
        self.dictionary = None
        self.saltValue = None
        self.MAX_PASSWORD_SIZE = 4

    def use_dictionary(self, dictionary):
        self.dictionary = set()
        dictionary_file = open(dictionary, "r")
        for line in dictionary_file:
            self.dictionary.add(line.rstrip('\n'))
        dictionary_file.close()

    def crack_password(self, encryptedPassword):
        # getting salt value
        self.encryptedPassword = encryptedPassword
        self.saltValue = self.encryptedPassword[:2]
        if self.dictionary is not None:
            #Try to break using the given dictionary
            self.__crack_password_dictionary_attack()
        if self.decryptedPassword is None:
            self.__crack_generic_password()

    def get_cracked_password(self):
        return self.decryptedPassword

    def __is_correct_password(self,word):
        encrypted_word = crypt.crypt(word, self.saltValue)
        ret_value = (encrypted_word == self.encryptedPassword)
        return ret_value

    def __crack_generic_password(self):
        #Trying to crack a generic password, generating all possible words
        for i in range(self.MAX_PASSWORD_SIZE + 1):
            permutations = generate_ascii_permutations(i)
            for word_tuple in permutations:
                word = ''.join(word_tuple)
                if self.__is_correct_password(''.join(word)):
                    self.decryptedPassword = word
                    break
            if self.decryptedPassword is not None:
                break

    def __crack_password_dictionary_attack(self):
        for word in self.dictionary:
            if self.__is_correct_password(word):
                self.decryptedPassword = word
                break

