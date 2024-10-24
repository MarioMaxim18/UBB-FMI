class Patient:
    def __init__(self, first_name, last_name, numerical_code, disease):
        self.__first_name = first_name
        self.__last_name = last_name
        self.__numerical_code = numerical_code
        self.__disease = disease
        self.__age = None

    def get_first_name(self):
        return self.__first_name

    def get_last_name(self):
        return self.__last_name

    def get_numerical_code(self):
        return self.__numerical_code

    def get_disease(self):
        return self.__disease

    def get_age(self):
        if self.__age is None:
            self.__age = int(input(f"Enter age for {self.__first_name} {self.__last_name}: "))
        return self.__age

    def set_first_name(self, first_name):
        self.__first_name = first_name

    def set_last_name(self, last_name):
        self.__last_name = last_name

    def set_numerical_code(self, numerical_code):
        self.__numerical_code = numerical_code

    def set_disease(self, disease):
        self.__disease = disease

    def set_age(self, age):
        self.__age = age
