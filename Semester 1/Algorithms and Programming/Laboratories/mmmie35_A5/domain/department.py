class Department:
    def __init__(self, id, name, number_of_beds, patients):
        self.__id = id
        self.__name = name
        self.__number_of_beds = number_of_beds
        self.__patients = patients

    def add_patient(self, patient):
        self.__patients.append(patient)

    def remove_patient(self, patient):
        self.__patients.remove(patient)
        self.__number_of_beds -= 1

    def get_patients(self):
        return self.__patients

    def get_name(self):
        return self.__name

    def get_id(self):
        return self.__id

    def get_number_of_beds(self):
        return self.__number_of_beds

    def sort_patients_alphabetically(self):
        return self.__patients.sort(key=lambda patients: (patients.get_last_name(), patients.get_first_name()))

    def sort_patients_by_personal_numerical_code(self):
        return self.__patients.sort(key=lambda patients: patients.get_numerical_code())

    def sort_patients_having_the_age_above_given_age(self, age):
        filtered_patients = [patient for patient in self.__patients if patient.get_age() > age]
        sorted_patients = sorted(filtered_patients, key=lambda patients: patients.get_age())
        self.__patients = sorted_patients
        return self.__patients

    def check_patients_having_the_age_under_given_age(self, age):
        filtered_patients = [patient for patient in self.__patients if patient.get_age() < age]
        if len(filtered_patients) > 0:
            return True

    def identify_patients_contain_a_given_string(self, string):
        for patient in self.__patients:
            if patient.get_first_name() == string or patient.get_last_name() == string:
                print(f"{patient.get_first_name()} {patient.get_last_name()}")

    def patients_contain_a_given_fname(self, fname):
        for patient in self.__patients:
            if patient.get_first_name() == fname:
                return True

    def decrease_number_of_beds(self):
        self.__number_of_beds -= 1

    def increase_number_of_beds(self):
        self.__number_of_beds += 1
