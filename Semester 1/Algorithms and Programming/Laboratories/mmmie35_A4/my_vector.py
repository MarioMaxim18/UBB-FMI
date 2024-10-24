import numpy as np

class MyVector:
    def __init__(self, name_id, colour, type, values):
        self.__name_id = name_id
        self.__colour = colour
        self.__type = type
        self.__values = np.array(values)

    def get_name_id(self):
        return self.__name_id

    def get_colour(self):
        return self.__colour

    def get_type(self):
        return self.__type

    def get_values(self):
        return self.__values

    def set_name_id(self, name_id):
        self.__name_id = name_id

    def set_colour(self, colour):
        self.__colour = colour

    def set_type(self, type):
        self.__type = type

    def set_values(self, values):
        self.__values = values

    def add_scalar(self, scalar):
        return self.__values+scalar

    def add_two_vectors(self, new_vect):
       return self.__values+new_vect

    def subtract(self, new_vect):
        return self.__values-new_vect

    def multiplication(self, new_vect):
        return self.__values*new_vect

    def sum_of_elem(self):
        return np.sum(self.__values)

    def product(self):
        return np.prod(self.__values)

    def average(self):
        return np.mean(self.__values)

    def min(self):
        return np.min(self.__values)

    def max(self):
        return np.max(self.__values)

    def __str__(self):
        return f"Vector {self.__name_id} of type {self.__type} and colour {self.__colour} with values {self.__values}"
    