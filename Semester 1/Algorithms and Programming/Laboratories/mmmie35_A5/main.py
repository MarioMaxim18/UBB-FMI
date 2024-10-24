from domain.patient import Patient
from domain.department import Department
from infrastructure.hospital import Hospital

hospital = Hospital()

department1 = Department(1, "Department 1", 20, [])
department2 = Department(2, "Department 2", 3, [])

hospital.add_department(department1)
patient1 = Patient("John", "Smith", 123, "flu")
patient2 = Patient("George", "Gavriliu", 556, "cold")
patient3 = Patient("Mihai", "Popa", 498, "cancer")
patient4 = Patient("Andrei", "Ardeleanu", 321, "headaches")
patient5 = Patient("Ion", "Popa", 432, "flu")
patient6 = Patient("Ana", "Dumitrescu", 431, "cold")
patient7 = Patient("Mihai", "Florea", 454, "fever")
patient8 = Patient("Elena", "Neagu", 819, "infection")
department1.add_patient(patient1)
department1.add_patient(patient2)
department1.add_patient(patient3)
department1.add_patient(patient4)
department1.add_patient(patient5)
department1.add_patient(patient6)
department1.add_patient(patient7)
department1.add_patient(patient8)


hospital.add_department(department2)
patient9 = Patient("Marcel", "Nustiucum", 563, "flu")
patient10 = Patient("Nume", "Sugestiv", 324, "cold")
department2.add_patient(patient9)
department2.add_patient(patient10)

def menu():
    print("\nSelect an option: ")
    print("1.Display the departments from the hospital")
    print("2.Display the patients from a given department")
    print("3.Add department")
    print("4.Remove department")
    print("5.Add patient")
    print("6.Remove patient")
    print("7.Sort patients by personal numerical code")
    print("8.Sort departments by number of patient")
    print("9.Sort patients having the age above given age")
    print("10.Sort departments by the number of patients and the patients in a department alphabetically")
    print("11.Find department where are patients under a given age")
    print("12.Find patients from a given department for which the first name or last name contain a given string")
    print("13.Find departments where there are patients with a given first name")
    print("0.Quit")

def read_option():
    option = int(input("Option: "))
    return option

def start_program():
    while True:
        menu()
        option = read_option()
        if option == 1:
            for department in hospital.get_departments():
                print(f"{department.get_name()}")
        elif option == 2:
            try:
                dep_id = int(input("Choose a department ID: "))
                selected_department = None
                for department in hospital.get_departments():
                    if department.get_id() == dep_id:
                        selected_department = department
                        break
                if selected_department:
                    for patient in selected_department.get_patients():
                        print(f"{patient.get_first_name()} {patient.get_last_name()}")
                else:
                    print("Department not found.")
            except ValueError:
                print("Please enter a valid department ID (an integer).")
        elif option == 3:
            id = int(input("Enter the ID: "))
            name = input("Enter the name: ")
            number_of_beds = int(input("Enter the number of beds: "))
            patients = []
            department = Department(id, name, number_of_beds, patients)
            hospital.add_department(department)
            print("Department added successfully.")
        elif option == 4:
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                hospital.remove_department(selected_department)
                print("Department removed successfully.")
            else:
                print("Department not found.")
        elif option == 5:
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                try:
                    first_name = input("Enter the first name: ")
                    last_name = input("Enter the last name: ")
                    numerical_code = input("Enter the numerical code: ")
                    disease = input("Enter the disease: ")
                    if not numerical_code.isdigit():
                        print("Numerical code should be a number.")
                    else:
                        numerical_code = int(numerical_code)
                        if len(selected_department.get_patients()) >= selected_department.get_number_of_beds():
                            print("No available beds in the department.")
                        else:
                            patient = Patient(first_name, last_name, numerical_code, disease)
                            selected_department.add_patient(patient)
                            selected_department.decrease_number_of_beds()
                            print("Patient added successfully. Bed count updated.")
                except ValueError:
                    print("Please enter valid input.")
            else:
                print("Department not found.")
        elif option == 6:
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                patient_id = int(input("Enter the patient ID: "))
                selected_patient = None
                for patient in selected_department.get_patients():
                    if patient.get_numerical_code() == patient_id:
                        selected_patient = patient
                        break
                if selected_patient:
                    selected_department.remove_patient(selected_patient)
                    selected_department.increase_number_of_beds()
                    print("Patient removed successfully. Bed count updated.")
                else:
                    print("Patient not found.")
            else:
                print("Department not found.")
        elif option == 7:
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                selected_department.sort_patients_by_personal_numerical_code()
                for patient in selected_department.get_patients():
                    print(f"{patient.get_first_name()} {patient.get_last_name()}")
            else:
                print("Department not found.")
        elif option == 8:
            hospital.sort_department_by_number_of_patients()
            for department in hospital.get_departments():
                print(f"{department.get_name()}")
        elif option == 9:
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                age = int(input("Enter the age: "))
                selected_department.sort_patients_having_the_age_above_given_age(age)
                for patient in selected_department.get_patients():
                    print(f"{patient.get_first_name()} {patient.get_last_name()}")
            else:
                print("Department not found.")
        elif option == 10:
            hospital.sort_department_by_number_of_patients()
            for department in hospital.get_departments():
                print(f"{department.get_name()}")
            dep_id = int(input("Choose a department ID: "))
            selected_department = None
            for department in hospital.get_departments():
                if department.get_id() == dep_id:
                    selected_department = department
                    break
            if selected_department:
                selected_department.sort_patients_alphabetically()
                for patient in selected_department.get_patients():
                    print(f"{patient.get_first_name()} {patient.get_last_name()}")
            else:
                print("Department not found.")
        elif option == 11:
            try:
                given_age = int(input("Enter the age: "))
                departments_found = False
                for department in hospital.get_departments():
                    if department.check_patients_having_the_age_under_given_age(given_age):
                        print(f"{department.get_name()}")
                        departments_found = True
                if not departments_found:
                    print("No departments found with patients under the given age.")
            except ValueError:
                print("Please enter a valid age (an integer).")
        elif option == 12:
            try:
                dep_id = int(input("Choose a department ID: "))
                given_string = input("Enter the given string: ")
                selected_department = None
                for department in hospital.get_departments():
                    if department.get_id() == dep_id:
                        selected_department = department
                        break
                if selected_department:
                    patients_found = False
                    for patient in selected_department.get_patients():
                        if (given_string.lower() in patient.get_first_name().lower() or given_string.lower()
                                in patient.get_last_name().lower()):
                            print(
                                f"{patient.get_first_name()} {patient.get_last_name()} is found in the department.")
                            patients_found = True
                    if not patients_found:
                        print("No patients found with the given string in their first or last name.")
                else:
                    print("Department not found.")
            except ValueError:
                print("Please enter a valid department ID (an integer).")
        elif option == 13:
            given_fname = input("Enter the given first name: ")
            patient_exists = False
            if given_fname.isdigit():
                print("Invalid input. Please enter a valid first name.")
            else:
                for department in hospital.get_departments():
                    for patient in department.get_patients():
                        if patient.get_first_name().lower() == given_fname.lower():
                            patient_exists = True
                            print(f"Patient found with the given first name in {department.get_name()}")
                            break
                    if patient_exists:
                        break
            if not patient_exists:
                print("No patient found with the given first name in any department.")
        elif option == 0:
            break
        else:
            print("Invalid option")

if __name__ == "__main__":
    start_program()
