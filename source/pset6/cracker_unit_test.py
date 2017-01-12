import unittest
import crypt
import itertools
from cracker import generate_ascii_permutations
from cracker import CrackDES


class TestCrackMethods(unittest.TestCase):

    def test_crypt(self):

        password_to_encrypt = "12345"
        encrypted_password = crypt.crypt(password_to_encrypt, "50")

    def test_crack_with_dictionary(self):
        unencrypted_password = "Ada"
        password = crypt.crypt(unencrypted_password, "50")
        dictionary_path="wordsfile"
        crack = CrackDES()
        crack.use_dictionary(dictionary_path)
        crack.crack_password(password)
        cracked_password = crack.get_cracked_password()

        self.assertTrue(cracked_password == unencrypted_password)

    def test_crack_without_dictionary(self):
        unencrypted_password = "A3{~"
        password = crypt.crypt(unencrypted_password, "50")
        crack = CrackDES()
        crack.crack_password(password)
        cracked_password = crack.get_cracked_password()
        self.assertTrue(cracked_password == unencrypted_password)
        print(cracked_password)

    def test_generating_strings(self):
        val = generate_ascii_permutations(2)

if __name__=="__main__":
    unittest.main()