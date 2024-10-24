class Hospital:
    def __init__(self):
        self.__departments = []

    def get_departments(self):
        return self.__departments

    def add_department(self, department):
        self.__departments.append(department)

    def remove_department(self, department):
        self.__departments.remove(department)

    def sort_department_by_number_of_patients(self):
        return self.__departments.sort(key=lambda department: len(department.get_patients()))

    def identify_departments_contain_a_given_first_name(self, fname):
        for department in self.__departments:
            if department.patients_contain_a_given_fname(fname):
                print(f"{department.get_name()}")
