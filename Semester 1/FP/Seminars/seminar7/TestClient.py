import unittest
from domain import Client

class TestClientAgain(unittest.TestCase):
    def testClient(self):
        c = Client(2, 'Edi POp', 19)
        assert c.Id == 2
        assert c.Name == 'Edi POp'
        assert c.Age == 19

    def testClient_again(self):
        c = Client(2, 'Pop MIhnea', 20)
        with self.assertRaises(ValueError):
            c.Age = 17
        try:
            c.Age = 17
            assert False  # should have raised an error
        except ValueError:
            assert True  # we are ei okay
        except Exception:
            assert False  # a different exception was raised
