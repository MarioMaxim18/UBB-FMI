import unittest
from domain.patient import Patient
from domain.department import Department
from infrastructure.hospital import Hospital


class TestHospital(unittest.TestCase):

    def setUp(self):
        self.hospital = Hospital()

    def test_sort_department_by_number_of_patients(self):
        department1 = Department(1, "Department 1", 20, [Patient("John", "Smith", 123, "flu")])
        department2 = Department(2, "Department 2", 3, [Patient("Jane", "Doe", 556, "cold")])
        self.hospital.add_department(department1)
        self.hospital.add_department(department2)

        self.hospital.sort_department_by_number_of_patients()
        self.assertEqual(self.hospital.get_departments(), [department2, department1])

        department3 = Department(3, "Department 3", 10, [Patient("Mark", "Johnson", 789, "fever")])
        self.hospital.add_department(department3)

        self.hospital.sort_department_by_number_of_patients()
        self.assertEqual(self.hospital.get_departments(), [department2, department3, department1])

        empty_hospital = Hospital()
        empty_hospital.sort_department_by_number_of_patients()
        self.assertEqual(empty_hospital.get_departments(), [])


if __name__ == '__main__':
    unittest.main()
