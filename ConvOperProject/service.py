from domain import Number
import math

class Operations:
    def __init__(self):
        '''
        we keep 2 dictionaries to convert the digits from type 'str' to type 'int'
        - more useful for operations and conversions in base 16
        '''
        self._hexaChar = {"0": 0, "1": 1,"2": 2,"3": 3,"4": 4, "5": 5,"6": 6, "7": 7, "8": 8,"9": 9, "A": 10, "B": 11, "C":12, "D":13, "E":14, "F":15}
        self._hexaDig = {0:"0", 1: "1",2: "2",3: "3",4: "4",5: "5",6: "6",7: "7",8: "8",9: "9" ,10: "A", 11:"B", 12: "C", 13: "D", 14: "E", 15: "F"}

    def validate_base(self, number):
        base = number.Base
        value = number.Value
        if base != 16:
            i = 0
            while i < len(value) :
                if int(value[i]) >= int(base):
                    raise  ValueError("Invalid number in base " + str(base))
                i +=1
        else:
            i = 0
            while i < len(value):
                if value[i] >= "F":
                    raise ValueError("Invalid number in base 16")

    def convert_same_lenght(self, number1, number2):
        '''
        we place '0' on the left of the number with less digits
        :param number1: object number 1
        :param number2: object number 2
        :return: a tuple with the values of the numbers with the same lenght
        '''
        num1 = number1.Value
        num2 = number2.Value
        if len(num1) < len(num2):
            for i in range(len(num2) - len(num1)):
                num1 = '0' + num1

        if len(num1) > len(num2):
            for i in range(len(num1) - len(num2)):
                num2 = '0' + num2
        return (num1, num2)

    def new_convert(self, number1, number2):
        '''
        we add insignificant zeros on the left part of the integer part and on the right side of the fractional part
        so that the two numbers have the same number of digits
        :param number1: object number 1
        :param number2: object number 2
        :return: a tuple consisting of the converted integer parts and fractional parts
        '''
        num1 = number1.Value
        '''
        we search for ',' in the string representation of the number
        '''
        idx = num1.find(",")
        '''
        if there is no ',', the number is integer
        if there is ',' , we separate the integer part and the fractional part
        '''
        if idx == -1:
            fp1 = ""
            ip1 = num1
        else:
            fp1 = num1[idx + 1:]
            ip1 = num1[:idx]

        num2 = number2.Value
        idx = num2.find(",")
        if idx == -1:
            fp2 = ""
            ip2 = num2
        else:
            fp2 = num2[idx + 1:]
            ip2 = num2[:idx]

        '''
        we add insignificant zeros to the left of the integer part
        '''
        if len(ip1) < len(ip2):
            for i in range(len(ip2) - len(ip1)):
                ip1 = '0' + ip1

        if len(ip1) > len(ip2):
            for i in range(len(ip1) - len(ip2)):
                ip2 = '0' + ip2
        '''
        we add insignificant zeros to the right of the fractional part
        '''
        if len(fp1) < len(fp2):
            for i in range(len(fp2) - len(fp1)):
                fp1 = fp1 + '0'

        if len(fp1) > len(fp2):
            for i in range(len(fp1) - len(fp2)):
                fp2 = '0' + fp2

        return (ip1, fp1, ip2, fp2)


    def addition(self, number1, number2):
        '''
        we add to numbers in the same base b
        :param number1: object number 1
        :param number2: object number 2
        :return: the result of the sum in base b
            error -> we cannot add two numbers in different bases
        '''
        if number1.Base != number2.Base:
            raise ValueError("Incompatible bases")
        '''
        we call the function convert
        '''
        base = int(number1.Base)
        conv = self.new_convert(number1, number2)
        '''
        we reconstruct the numbers that will have the same number of digits
        '''
        if conv[1] != '' :
            num1 = conv[0] + ',' + conv[1]
        else:
            num1 = conv[0]
        if conv[3] != '':
            num2 = conv[2] + ',' + conv[3]
        else:
            num2 = conv[2]
        '''
        we initialise the carry, the result 
        the parsing of the number will be done from right to left
        '''
        carry = 0
        result = ""
        i = len(num1)-1
        while i >=0:
            '''
            if we reached the ',' in the string parsing, we add it to the result
            '''
            if num1[i] == ',':
                result = ',' + result
                i -= 1
            else:
                '''
                we convert the digits from type 'str' to type 'int' using the dictionaries from above
                '''
                dig1 = self._hexaChar[num1[i]]
                dig2 = self._hexaChar[num2[i]]
                '''
                we calculate the sum of the digits, add the carry and apply modulo
                '''
                digit_sum = (int(dig1) + int(dig2) + carry) % base
                '''
                we convert the resulted digit from type 'int' to type 'str' using the dictionaries from above
                '''
                if digit_sum in self._hexaDig:
                    digit_sum = self._hexaDig[digit_sum]
                '''
                we compute the new carry
                '''
                carry = (int(dig1) + int(dig2) + carry) // base
                '''
                we add the resulted digit to the result
                '''
                result = str(digit_sum) + result
                i -= 1
            '''
            we consider the carry at the end of the sum
            '''
        if carry == 1:
            result = "1" + result
        return result


    def subtraction(self, number1, number2):
        '''
        we compute the subtraction of 2 numbers is base b
        :param number1: object number 1
        :param number2: object number 2
        :return: he result of the subtraction in base b
            error -> we cannot subtract two numbers in different bases
        '''
        if number1.Base != number2.Base:
            raise ValueError("Incompatible bases")
        '''
        we call the function convert
        '''
        base = int(number1.Base)
        conv = self.new_convert(number1, number2)

        '''
        we reconstruct the numbers that will have the same number of digits
        '''

        if conv[1] != '':
            num1 = conv[0] + ',' + conv[1]
        else:
            num1 = conv[0]
        if conv[3] != '':
            num2 = conv[2] + ',' + conv[3]
        else:
            num2 = conv[2]
        '''
        if the numbers are identical, the subtraction is 0
        '''
        if num1 == num2:
            return 0
        '''
        we initialise the carry, the result 
        he parsing of the number will be done from right to left
        '''
        carry = 0
        result = ""
        i = len(num1) - 1
        while i >= 0:
            '''
            if we reached the ',' in the string parsing, we add it to the result
            '''
            if num1[i] == ',':
                result = ',' + result
                i -= 1
            else:
                '''
                we convert the digits from type 'str' to type 'int' using the dictionaries from above
                '''
                dig1 = self._hexaChar[num1[i]]
                dig2 = self._hexaChar[num2[i]]
                '''
                we compute the subtraction and add the carry
                '''
                digit_sum = int(dig1) - int(dig2) + carry
                '''
                if the result is negative, we have a carry and to the resulted digit we add the value of the base
                '''
                if digit_sum < 0:
                    carry = -1
                    digit_sum = digit_sum + base
                else:
                    carry = 0
                '''
                we convert the resulted digit from type 'int' to type 'str' using the dictionaries from above
                '''
                if digit_sum in self._hexaDig:
                    digit_sum = self._hexaDig[digit_sum]
                '''
                we concatenate the new digit to the result
                '''
                result = str(digit_sum) + result
                i -= 1
        if carry == -1:
            raise ValueError("Wrong")

        '''
        retutn the result without the zeros from the front
        '''
        return result.lstrip("0")

    def multiplication(self, number, multDigit):
        '''
        we multiply by one digit a number in a base b
        :param number: the object number
        :param multDigit: the multiplication digit
        :return: the result of the multiplication in base b
            error -> we cannot multiply if the based differ
        '''
        if number.Base != multDigit.Base:
            raise ValueError("Incompatible bases")
        base = int(number.Base)
        number = number.Value
        multDigit = multDigit.Value
        '''
        we convert the multiplication digit from type 'str' to type 'int' using the dictionaries from above
        '''
        multDigit = self._hexaChar[multDigit]
        '''
        we initialise the carry, the result 
        the parsing of the number will be done from right to left
        '''
        carry = 0
        result = ""
        i = len(number) - 1
        while i >= 0:
            '''
            if we reached the ',' in the string parsing, we add it to the result
            '''
            if number[i] == ",":
                result = ',' + result
                i -= 1
            else:
                '''
                we convert the digit from type 'str' to type 'int' using the dictionaries from above
                '''
                digit = self._hexaChar[number[i]]
                '''
                we compute an intermediate result  
                '''
                result_base10 = int(digit) * int(multDigit) + carry
                '''
                we compute the resulted digit and convert it from type 'int' to type 'str' using the dictionaries from above
                '''
                result_digit = result_base10 % base
                if result_digit in self._hexaDig:
                    result_digit = self._hexaDig[result_digit]
                '''
                we compute the new carry
                '''
                carry = result_base10 // base
                '''
                we concatenate the resulted digit to the result
                '''
                result = str(result_digit) + result
                i -= 1
        '''
        we take into consideration the carry digit at the end 
        '''
        if carry > 0:
            result = str(carry) + result
        return result

    def division(self, number, divDigit):
        '''
        we compute the division by one digit of a number in a base b
        :param number: the object number
        :param divDigit: the division digit
        :return: a tuple containing the quotient and the remainder
        ERROR - > we cannot devide if the bases differ
        '''
        if number.Base != divDigit.Base:
            raise ValueError("Incompatible bases")
        base = int(number.Base)
        number = number.Value
        divDigit = divDigit.Value
        try:
            if int(number) < int(divDigit):
                number = number + ",000"
        except Exception:
            pass
        '''
        we convert the division digit from type 'str' to type 'int' using the dictionaries from above
        '''
        divDigit = self._hexaChar[divDigit]
        '''
        we initialise the carry and the quotient
        the parsing of the string will be done from left to right
        '''
        carry = 0
        quotient = ""
        i = 0
        while i < len(number):
            '''
            if we reached the ',' in the string parsing, we add it to the result
            '''
            if number[i] == ",":
                quotient = quotient + ','
                i += 1
            else:
                #intermediate_value = str(carry) + str(number[0])
                '''
                we convert the digit from type 'str' to type 'int' using the dictionaries from above
                '''
                digit = self._hexaChar[number[i]]
                converted_intermediate_value = int(carry) * base + digit
                '''
                we compute the digits of the quotient
                '''
                q1 = converted_intermediate_value // divDigit
                '''
                we convert the resulted digit from type 'str' to type 'int' using the dictionaries from above
                '''
                q1 = self._hexaDig[q1]
                '''
                we compute the new carry
                '''
                carry = converted_intermediate_value % divDigit
                '''
                we concatenate the resulted digit to the quotient 
                '''
                quotient = quotient + str(q1)
                i += 1
        '''
        we compute the remainder 
        '''
        remainder = self._hexaDig[carry]
        return (quotient.lstrip("0"), remainder)

    def division_version2(self, number, divDigit):
        '''
        we compute the division by one digit of a number in a base b
        :param number: the object number
        :param divDigit: the division digit
        :return: a tuple containing the quotient and the remainder
        ERROR - > we cannot devide if the bases differ
        '''
        if number.Base != divDigit.Base:
            raise ValueError("Incompatible bases")
        base = int(number.Base)
        number = number.Value
        divDigit = divDigit.Value
        '''
        we convert the division digit from type 'str' to type 'int' using the dictionaries from above
        '''
        divDigit = self._hexaChar[divDigit]
        '''
        we initialise the carry and the quotient
        the parsing of the string will be done from left to right
        '''
        carry = 0
        quotient = ""
        i = 0
        while i < len(number):
            '''
            if we reached the ',' in the string parsing, we add it to the result
            '''
            if number[i] == ",":
                quotient = quotient + ','
                i += 1
            else:
                #intermediate_value = str(carry) + str(number[0])
                '''
                we convert the digit from type 'str' to type 'int' using the dictionaries from above
                '''
                digit = self._hexaChar[number[i]]
                converted_intermediate_value = int(carry) * base + digit
                '''
                we compute the digits of the quotient
                '''
                q1 = converted_intermediate_value // divDigit
                '''
                we convert the resulted digit from type 'str' to type 'int' using the dictionaries from above
                '''
                q1 = self._hexaDig[q1]
                '''
                we compute the new carry
                '''
                carry = converted_intermediate_value % divDigit
                '''
                we concatenate the resulted digit to the quotient 
                '''
                quotient = quotient + str(q1)
                i += 1
        '''
        we compute the remainder 
        '''
        remainder = self._hexaDig[carry]
        return (quotient.lstrip("0"), remainder)

class Convertions(Operations):
    def __init__(self):
        Operations.__init__(self)
        self._hexaChar = {"0": 0, "1": 1,"2": 2,"3": 3,"4": 4, "5": 5,"6": 6, "7": 7, "8": 8,"9": 9, "A": 10, "B": 11, "C":12, "D":13, "E":14, "F":15}
        self._hexaDig = {0: "0", 1: "1", 2: "2", 3: "3", 4: "4", 5: "5", 6: "6", 7: "7", 8: "8", 9: "9", 10: "A",
                         11: "B", 12: "C", 13: "D", 14: "E", 15: "F"}
        self.RapidConversionFrom2to4 = {"00": "0", "01": "1", "10": "2", "11": "3", ",": ","}
        self.RapidConversionFrom4to2 = {"0": "00", "1": "01", "2": "10", "3": "11", ",": ","}
        self.RapidConversionFrom2to8 = {"000": "0", "001": "1", "010": "2", "011": "3", "100": "4", "101": "5",
                                        "110": "6", "111": "7", ",": ","}
        self.RapidConversionFrom8to2 = {"0": "000", "1": "001", "2": "010", "3": "011", "4": "100", "5": "101",
                                        "6": "110", "7": "111", ",": ","}
        self.RapidConversionFrom2to16 = {"0000": "0", "0001": "1", "0010": "2", "0011": "3", "0100": "4", "0101": "5",
                                         "0110": "6", "0111": "7", "1000": "8", "1001": "9", "1010": "A", "1011": "B",
                                         "1100": "C", "1101": "D", "1110": "E", "1111": "F", ",": ","}
        self.RapidConversionFrom16to2 = {"0": "0000", "1": "0001", "2": "0010", "3": "0011", "4": "0100", "5": "0101",
                                         "6": "0110", "7": "0111", "8": "1000", "9": "1001", "A": "1010", "B": "1011",
                                         "C": "1100", "D": "1101", "E": "1110", "F": "1111", ",": ","}
        self.RapidConversionFrom4to16 = {"00": "0", "01": "1", "02": "2", "03": "3", "10": "4", "11": "5", "12": "6",
                                         "13": "7", "20": "8", "21": "9", "22": "A", "23": "B", "30": "C", "31": "D",
                                         "32": "E", "33": "F", ",": ","}
        self.RapidConversionFrom16to4 = {"0": "00", "1": "01", "2": "02", "3": "03", "4": "10", "5": "11", "6": "12",
                                         "7": "13", "8": "20", "9": "21", "A": "22", "B": "23", "C": "30", "D": "31",
                                         "E": "32", "F": "33", ",": ","}

    def substitution_method(self, source_base, destination_base, number):
        '''
        we convert two numbers using the substitution method if the source base
        :param source_base: the source base
        :param destination_base: the destination base
        :param number: the number to be converted
        :return: the converted number
        '''
        '''
        we separate the integer part and the fractional part
        '''
        idx = number.find(",")
        if idx == -1:
            fractional_part = ""
            integer_part = number
        else:
            fractional_part = number[idx + 1:]
            integer_part= number[:idx]
        '''
        we initialize the count and the sum for the integer part
        the string parsing will be done from right to left
        '''
        count = 0
        sum = 0
        i = len(integer_part) - 1
        while i >= 0:
            '''
            variable "power" calculates the source base value to the power of count that will be multiplied
            later with the number's digit
            '''
            if count == 0:
                power = 1
            elif count == 1:
                power = source_base
            else:
                sb = Number(destination_base, str(source_base))
                power = Operations.multiplication(self, sb, sb)
                for j in range(count-2):
                    num = Number(destination_base, str(power))
                    sb = Number(destination_base, str(source_base))
                    power = Operations.multiplication(self, num, sb)
            '''
            we calculate a temporary result by multiplying power with the digit from the number to be converted
            '''
            result_integer = Operations.multiplication(self,Number(destination_base,str(power)),Number(destination_base, integer_part[i]))
            n1 = Number(destination_base, str(sum))
            n2 = Number(destination_base, str(result_integer))
            '''
            we add the temporary result to the previous sum
            '''
            sum = Operations.addition(self, n1,n2)
            count += 1
            i -= 1
        '''
        the variable sum will hold the integer part of the number converted in the destination base
        '''
        '''
        we initialize the count and the sum for the fractional part of the number to be converted
        the string parsing will be done from left to right
        '''
        count = 1
        i = 0
        sum2 = 0
        while i < len(fractional_part):
            '''
            variable "power" calculates the source base value to the power of "-count" that will be multiplied
            later with the number's digit
            '''
            n1 = Number(destination_base, str(fractional_part[i]))
            digit = Number(destination_base, str(source_base))
            power = Operations.division(self, n1, digit)
            for j in range(count-1):
                n1 = Number(destination_base, str(power[0]))
                digit = Number(destination_base, str(source_base))
                power = Operations.division(self, n1, digit)
            '''
            we add "0," to the result
            '''
            if power[0][0] == ",":
                power = "0" + power[0]
            else:
                power = power[0]
            '''
            we compute the sum by adding all the power"s resulted from previous calculations
            '''
            n1 = Number(destination_base, str(sum2))
            n2 = Number(destination_base, str(power))
            sum2 = Operations.addition(self, n1, n2)
            count += 1
            i += 1
        '''
        we compute the final conversion of the integer part and of the fractional part and we concatenate them
        '''
        final_int = Number(destination_base, str(sum))
        final_frac = Number(destination_base, str(sum2))
        result = Operations.addition(self, final_int, final_frac)
        return result

    def convert_integer_10(self, number):
        '''
        we convert an integer number to base 10
        :param number: the given number
        :return: the converted value
        '''
        base = number.Base
        value = number.Value
        '''
        we initialize the count and the sum 
        the string parsing will be done from right to left 
        '''
        count = 0
        sum = 0
        i = len(value) - 1
        while i >= 0:
            '''
            we convert the digit from type 'str' to type 'int' using the dictionaries above
            '''
            digit = self._hexaChar[value[i]]
            '''
            variable "power" calculates the source base value to the power of count that will be multiplied
            later with the number's digit
            '''
            power = pow(base, count)
            '''
            we calculate a temporary result by multiplying the power with the current digit
            '''
            temporary_result = power * int(digit)
            '''
            we add the temporary result to the sum
            '''
            sum += temporary_result
            count += 1
            i -= 1
        return sum

    def convert_fractional_10(self, number):
        '''
        we convert the fractional part of a number into base 10
        :param number: the given number
        :return: the converted value
        '''
        base = number.Base
        value = number.Value
        '''
        we initialize count and sum 
        the string parsing will be done from left to right
        '''
        count = -1
        sum = 0
        i = 0
        while i < len(value):
            '''
             we convert the digit from type 'str' to type 'int' using the dictionaries above
            '''
            digit = self._hexaChar[value[i]]
            '''
            variable "power" calculates the source base value to the power of count that will be multiplied
            later with the number's digit
            '''
            power = pow(base, count)
            '''
            we calculate a temporary result by multiplying the power with the current digit
            '''
            temporary_result = power * int(digit)
            '''
            we add the temporary result to the sum
            '''
            sum += temporary_result
            count -= 1
            i +=1
        return sum

    def convert_integer_10_other_base(self, number):
        '''
        converts an integer number from base 10 into another base
        :param number: the given number
        :return: the converted value
        '''
        base = number.Base
        value = int(number.Value)
        result = ""
        quotient = 1000000
        while quotient > 0:
            '''
            we divide the value to the  base and add the remainder to the result 
            '''
            quotient = value // base
            remainder = value % base
            result = str(self._hexaDig[remainder]) + result
            '''
            we update the value
            '''
            value = value // base
        return result

    def convert_fractional_10_other_base(self, number, no_of_digits): #with , included
        '''
        converts the fractional part of a number into another base
        :param number: the given number
        :param no_of_digits: the number of digits after '.'
        :return: the converted value
        '''
        base = number.Base
        result = "0."
        '''
        we compute a temporary result by multiplying the value with the base
        '''
        temporary_result = float(number.Value) * base
        temporary_result = str(temporary_result)
        idx = temporary_result.find(".")
        '''
        we add to the result the integer part of the obtained result
        '''
        result = result + self._hexaDig[int(temporary_result[:idx])]
        '''
        we continue the multiplication with the fractional part of the obtained result
        '''
        temporary_result = float(temporary_result) - float(temporary_result[:idx])
        no_of_digits -= 1
        '''
        we repeat the same steps untill the variable 'no_of_digits' is 0
        '''
        while no_of_digits > 0:
            temporary_result = temporary_result * base
            temporary_result = str(temporary_result)
            idx = temporary_result.find(".")
            result = result + self._hexaDig[int(temporary_result[:idx])]
            temporary_result = float(temporary_result) - float(temporary_result[:idx])
            no_of_digits -= 1
        return result

    def covert_10_intermediate_base(self, source_base, destination_base, number, no_of_digits):
        '''
        converts a number from a source base into the destination base using base 10 as an intermediate base
        :param source_base: the source base
        :param destination_base: the destination base
        :param number: the given number
        :param no_of_digits: the number of digits at the fractional part
        :return: the converted value
        '''
        '''
        we separate the integer part and the fractional part
        '''
        idx = number.find(",")
        if idx != -1:
            integer_part = number[:idx]
            fractional_part = number[idx + 1:]
        else:
            integer_part = number
            fractional_part = ""
        '''
        we convert the integer part and the fractional part into base 10 using the functions from above
        '''
        integer_part_base10 = self.convert_integer_10(Number(source_base, integer_part))
        fractional_part_base10 = self.convert_fractional_10(Number(source_base, fractional_part))
        fractional_part_base10 = str(fractional_part_base10)
        number_base10 = str(integer_part_base10) + fractional_part_base10.lstrip("0")
        number_base10 = str(number_base10)
        '''
        we separate the new number's integer part and fractional part
        '''
        idx = number_base10.find(".")
        if idx != -1:
            integer_part = number_base10[:idx]
            fractional_part = "0" + number_base10[idx:]
        else:
            integer_part = number_base10
            fractional_part = ""
        '''
        we convert the integer part and the fractional part into the destination base using the functions from above
        '''
        integer_part_dest_base = self.convert_integer_10_other_base(Number(destination_base, integer_part))
        fractional_part_dest_base = self.convert_fractional_10_other_base(Number(destination_base, fractional_part), no_of_digits)
        fractional_part_dest_base = str(fractional_part_dest_base)
        number_dest_base = integer_part_dest_base + fractional_part_dest_base.lstrip("0")
        return number_dest_base

    '''
    smd - successive multiplications and divisions
    '''
    def smd_integer(self, source_base, destination_base, number):
        '''
        we convert the integer part of a number using successive divisions
        :param source_base: the source base
        :param destination_base: the destination base
        :param number: the number to be converted
        :return: the converted value
        '''
        value = number
        result = ""
        quotient = "1000000"
        while quotient != '':
            '''
            we divide the value to the  base and add the remainder to the result 
            '''
            division = Operations.division_version2(self, Number(source_base, value), Number(source_base, str(destination_base)))

            quotient = str(division[0])
            remainder = division[1]
            result = remainder + result
            '''
            we update the value
            '''
            value = division[0]
        return result

    def smd_fractional(self, source_base, destination_base, number, no_of_digits):  #"with" , included
        '''
        we convert the fractional part of a number using successive multiplications
        :param source_base: the source base
        :param destination_base: the destination base
        :param number: the number to be converted
        :param no_of_digits: the number of the digits at the fractional part
        :return: the converted value
        '''
        result = "0,"
        '''
        we compute a temporary result by multiplying the value with the base
        '''
        temporary_result = Operations.multiplication(self, Number(source_base, number), Number(source_base, str(destination_base)))
        temporary_result = str(temporary_result)
        idx = temporary_result.find(",")
        '''
        we add to the result the integer part of the obtained result
        '''
        result = result + self._hexaDig[int(temporary_result[:idx])]
        '''
        we continue the multiplication with the fractional part of the obtained result
        '''
        #temporary_result = float(temporary_result) - float(temporary_result[:idx])
        temporary_result = "0" + temporary_result[idx:]
        no_of_digits -= 1
        '''
        we repeat the same steps untill the variable 'no_of_digits' is 0
        '''
        while no_of_digits > 0:
            temporary_result = Operations.multiplication(self, Number(source_base, temporary_result), Number(source_base, str(destination_base)))
            temporary_result = str(temporary_result)
            idx = temporary_result.find(",")
            result = result + self._hexaDig[int(temporary_result[:idx])]
            temporary_result = "0" + temporary_result[idx:]
            no_of_digits -= 1
        return result

    def succesive_multiplication_division(self, source_base, destination_base, number, no_of_digits):
        '''
        we convert the number into the destination base using the successive multiplication division method
        :param source_base: the source base
        :param destination_base: the destination base
        :param number: the number to be converted
        :param no_of_digits: the number of the digits at the fractional part
        :return: the converted value
        '''
        '''
        we separate the integer part and the fractional part
        '''
        idx = number.find(",")
        if idx != -1:
            integer_part = number[:idx]
            fractional_part = "0" + number[idx:]
            '''
            we convert the integer part and the fractional part using the functions defined above
            '''
            integer_part_converted = self.smd_integer(source_base, destination_base, integer_part)
            fractional_part_converted = self.smd_fractional(source_base, destination_base, fractional_part,
                                                            no_of_digits)
            result = integer_part_converted + fractional_part_converted[1:]
            return result
        else:
            '''
            if we have just integer part, we convert and return it
            '''
            integer_part = number
            fractional_part = ""
            integer_part_converted = self.smd_integer(source_base, destination_base, integer_part)
            return integer_part_converted

    def digitsIntegerPart(self, number):
        '''
        we compute the number of digits before the comma
        :param number: the given number
        :return: the number of digits
        '''
        nr_digits = 0
        for i in range(len(number)):
            character = number[i]
            if character == ",":
                return nr_digits
            nr_digits += 1
        return nr_digits

    def digitsFractionalPart(self, number):
        '''
        we compute the number of digits after the comma
        :param number: the given number
        :return: the number of digits
        '''
        nr_digits = 0
        for i in range(len(number) - 1, -1, -1):
            character = number[i]
            if character == ",":
                return nr_digits
            nr_digits += 1
        return 0

    def createNumberWith0Digits(self, number, sourceBase, destinationBase):
        '''
        used to complete a number with 0s before/after the comma in the case of rapid conversions depending on the bases
        :param number: the number to convert
        :param sourceBase: the source base
        :param destinationBase: the destination base
        :return: the number as a string with the necessary 0s added in the front (before the comma) and in the end (after the comma)
        '''
        digitsBeforeComma = self.digitsIntegerPart(number)
        digitsAfterComma = self.digitsFractionalPart(number)
        '''
        we compute the number of zeros to be added considering the bases given
        '''
        if sourceBase > destinationBase:
            return number
        elif destinationBase > sourceBase:
            numberOfDigitsToGroup = int(math.log(destinationBase, sourceBase))
        numberOf0sToAddBeforeComma = int(numberOfDigitsToGroup - digitsBeforeComma % numberOfDigitsToGroup)
        numberOf0sToAddAfterComma = int(numberOfDigitsToGroup - digitsAfterComma % numberOfDigitsToGroup)
        if numberOf0sToAddBeforeComma == 4:
            numberOf0sToAddBeforeComma = 0
        if numberOf0sToAddAfterComma == 4:
            numberOf0sToAddAfterComma = 0
        '''
        we add the necessary digits: on the left (the integer part) and at the right (the fractional part)
        '''
        if digitsBeforeComma != 0:
            for i in range(numberOf0sToAddBeforeComma):
                number = "0" + number
        if digitsAfterComma != 0:
            for i in range(numberOf0sToAddAfterComma):
                number = number + "0"
        return number

    def chooseDict(self, sourceBase, destinationBase):
        '''
        we choose which rapid conversion dictionary to use for conversion
        :param sourceBase: the source base
        :param destinationBase: the destination base
        :return: the corresponding dictionary for future conversions
        '''
        if sourceBase == 2:
            if destinationBase == 4:
                return self.RapidConversionFrom2to4
            elif destinationBase == 8:
                return self.RapidConversionFrom2to8
            elif destinationBase == 16:
                return self.RapidConversionFrom2to16
        elif sourceBase == 4:
            if destinationBase == 2:
                return self.RapidConversionFrom4to2
            elif destinationBase == 16:
                return self.RapidConversionFrom4to16
        elif sourceBase == 8:
            if destinationBase == 2:
                return self.RapidConversionFrom8to2
        elif sourceBase == 16:
            if destinationBase == 2:
                return self.RapidConversionFrom16to2
            elif destinationBase == 4:
                return self.RapidConversionFrom16to4

    def rapidConversion(self, sourceBase, destinationBase, number):
        '''
        conversion method used when both bases are powers of 2
        :param number: the number to convert
        :param sourceBase: the source base of the conversion
        :param destinationBase: the destination base of the conversion
        :return: the converted number
        '''
        list = [2,4,8,16]
        if sourceBase not in list or destinationBase not in list:
            raise ValueError("Unvalid base for rapid conversion!")
        result = ""
        '''
        we complete the number with zeros according to the bases we work with
        '''
        number = self.createNumberWith0Digits(number, sourceBase, destinationBase)
        digitsBeforeComma = self.digitsIntegerPart(number)
        digitsAfterComma = self.digitsFractionalPart(number)
        '''
        if the source base is not a power of the destination base or the other way around, we use base 2 as the
        intermediate base
        '''
        if sourceBase == 4 and destinationBase == 8:
            number = self.rapidConversion(4, 2, number)
            number = self.rapidConversion(2, 8, number)
            result = number
        elif sourceBase == 8 and destinationBase == 4:
            number = self.rapidConversion(8, 2, number)
            number = self.rapidConversion(2, 4, number)
            result = number
        elif sourceBase == 8 and destinationBase == 16:
            number = self.rapidConversion(8, 2, number)
            number = self.rapidConversion(2, 16, number)
            result = number
        elif sourceBase == 16 and destinationBase == 8:
            number = self.rapidConversion(16, 2, number)
            number = self.rapidConversion(2, 8, number)
            result = number
        else:
            '''
            if the destination base is greater than the source base, we group the digits in groups of 2,3,4 depending on
            the bases we work with
            in the next step, we convert each group formed using the appropriate dictionary 
            if the source base is greater than the destination base, we just replace each digit with 2,3,4 digits 
            depending on the bases we work with using the appropriate dictionary
            '''
            conversionDictionary = self.chooseDict(sourceBase, destinationBase)
            if destinationBase > sourceBase:
                numberOfDigitsInGroup = int(math.log(destinationBase, sourceBase))
                numberOfGroupsBeforeComma = digitsBeforeComma // numberOfDigitsInGroup
                numberOfGroupsAfterComma = digitsAfterComma // numberOfDigitsInGroup
                if numberOfGroupsBeforeComma != 0:
                    for i in range(numberOfGroupsBeforeComma):
                        groupOfDigitsToConvert = number[numberOfDigitsInGroup * i:][:numberOfDigitsInGroup]
                        result = result + conversionDictionary[groupOfDigitsToConvert]
                if numberOfGroupsAfterComma != 0:
                    result = result + ","
                    for i in range(numberOfGroupsAfterComma):
                        groupOfDigitsToConvert = number[(numberOfGroupsBeforeComma * numberOfDigitsInGroup + 1 + i * numberOfDigitsInGroup):][:(numberOfDigitsInGroup)]
                        result = result + conversionDictionary[groupOfDigitsToConvert]
            elif sourceBase > destinationBase:
                for i in range(len(number)):
                    result = result + conversionDictionary[number[i]]
        '''
        we eliminate all the zeros from the left of the integer part and all zeros from the right side of the
        fractional part
        '''
        idx = result.find(",")
        if idx == -1:
            return result.lstrip("0")
        else:
            return result.strip("0")