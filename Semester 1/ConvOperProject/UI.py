from service import *

class UI:
    def __init__(self, service):
        self._service = service

    def addition(self):
        '''
        we ask the user for input and we compute the addition
        :return:
        '''
        base = int(input("Give base: "))
        number1 = input("Give first number: ")
        number2 = input("Give second number: ")
        numberObj1 = Number(base, number1)
        numberObj2 = Number(base, number2)
        try:
            self._service.validate_base(numberObj1)
            self._service.validate_base(numberObj2)
        except ValueError as ve:
            print(ve)
            return
        result = self._service.addition(numberObj1, numberObj2)
        print("The result is: " + result)

    def subtraction(self):
        '''
        we ask the user for input and compute the subtraction
        :return:
        '''
        base = int(input("Give base: "))
        number1 = input("Give first number: ")
        number2 = input("Give second number: ")
        numberObj1 = Number(base, number1)
        numberObj2 = Number(base, number2)
        try:
            self._service.validate_base(numberObj1)
            self._service.validate_base(numberObj2)
        except ValueError as ve:
            print(ve)
            return
        result = self._service.subtraction(numberObj1, numberObj2)
        if result[0] == ",":
            result = "0" + result
        print("The result is: " + result)

    def multiplication(self):
        '''
        we ask the user for input and compute the multiplication
        :return:
        '''
        base = int(input("Give base: "))
        number1 = input("Give number: ")
        number2 = input("Give digit: ")
        numberObj1 = Number(base, number1)
        numberObj2 = Number(base, number2)
        try:
            self._service.validate_base(numberObj1)
            self._service.validate_base(numberObj2)
        except ValueError as ve:
            print(ve)
            return
        result = self._service.multiplication(numberObj1, numberObj2)
        if result[0] == ",":
            result = "0" + result
        print("The result is: " + result)

    def division(self):
        '''
        we ask the user for input and compute the division
        :return:
        '''
        base = int(input("Give base: "))
        number1 = input("Give number: ")
        number2 = input("Give digit: ")
        numberObj1 = Number(base, number1)
        numberObj2 = Number(base, number2)
        try:
            self._service.validate_base(numberObj1)
            self._service.validate_base(numberObj2)
        except ValueError as ve:
            print(ve)
            return
        result = self._service.division(numberObj1, numberObj2)
        if result[1] == "0":
            if result[0][0] == ",":
                print("Quotient: " + "0" + result[0])
            else:
                print("Quotient: " + result[0])
        else:
            if result[0][0] == ",":
                print("Quotient: " + "0" + result[0] + " Remainder:" + result[1])
            else:
                print("Quotient: " +  result[0] + " Remainder:" + result[1])

    def substitution_method(self):
        '''
        we ask the user for input, we validate it and compute the conversion using the substritution method
        '''
        source_base = int(input("Give source base: "))
        destination_base = int(input("Give destination base: "))
        number = input("Give number to convert: " )
        if destination_base < source_base:
            print("Invalid method for chosen bases!")
            return
        try:
            self._service.validate_base(Number(source_base, number))
        except ValueError as ve:
            print(ve)
            return
        result = self._service.substitution_method(source_base, destination_base ,number)
        print(result)

    def succesive_divisions_multiplications_method(self):
        '''
        we ask the user for input, we validate it and compute the conversion using the succesive divisions and
        multiplications method
        :return:
        '''
        source_base = int(input("Give source base: "))
        destination_base = int(input("Give destination base: "))
        number = input("Give number to convert: ")
        no_of_digits = int(input("Give number of digits at the fractional part: "))
        if destination_base > source_base:
            print("Invalid method for chosen bases!")
            return
        try:
            self._service.validate_base(Number(source_base, number))
        except ValueError as ve:
            print(ve)
            return
        result = self._service.succesive_multiplication_division(source_base, destination_base, number, no_of_digits)
        print(result)

    def base10_intermediat(self):
        '''
        we ask the user for input, we validate it and compute the conversion using base 10 as an intermediate base
        :return:
        '''
        source_base = int(input("Give source base: "))
        destination_base = int(input("Give destination base: "))
        number = input("Give number to convert: ")
        no_of_digits = int(input("Give number of digits at the fractional part: "))
        try:
            self._service.validate_base(Number(source_base, number))
        except ValueError as ve:
            print(ve)
            return
        result = self._service.covert_10_intermediate_base(source_base, destination_base, number, no_of_digits)
        print(result)

    def rapid_conversions(self):
        '''
        we ask the user for input, we validate it and compute the conversion using rapid conversions
        :return:
        '''
        source_base = int(input("Give source base: "))
        destination_base = int(input("Give destination base: "))
        number = input("Give number to convert: ")
        try:
            self._service.validate_base(Number(source_base, number))
        except ValueError as ve:
            print(ve)
            return
        try:
            result = self._service.rapidConversion(source_base, destination_base, number)
            print(result)
        except ValueError as ve:
            print(ve)


    def print_menu(self):
        print("1. Addition")
        print("2. Subtraction")
        print("3. Multiplication by one digit")
        print("4. Division by one digit")
        print("5. Convert using the substitution method")
        print("6. Convert using the successive divisions and multiplications method")
        print("7. Convert using base 10 as the intermediate base")
        print("8. Convert using rapid conversions")
        print('0. Exit')

    def start(self):
        while True:
            self.print_menu()
            choice = input(">")
            if choice == '1':
                self.addition()
            elif choice == '2':
                self.subtraction()
            elif choice == '3':
                self.multiplication()
            elif choice == '4':
                self.division()
            elif choice == '5':
                self.substitution_method()
            elif choice == '6':
                self.succesive_divisions_multiplications_method()
            elif choice == '7':
                self.base10_intermediat()
            elif choice == '8':
                self.rapid_conversions()
            elif choice == "0":
                break
            else:
                print("Bad command")

