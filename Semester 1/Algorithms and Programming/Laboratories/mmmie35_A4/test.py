import unittest
from VectorRepo import VectorRepository

class TestVectorRepository(unittest.TestCase):
    def setUp(self):
        self.repository = VectorRepository()
        self.repository.add_vector("vector1", "red", "1", [1, 2, 3])
        self.repository.add_vector("vector2", "blue", "2", [4, 5, 6])
        self.repository.add_vector("vector3", "green", "3", [7, 8, 9])

    def test_add_vector(self):
        initial_count = len(self.repository.get_all_vectors())
        self.repository.add_vector("new_vector", "yellow", "4", [10, 11, 12])
        new_count = len(self.repository.get_all_vectors())
        self.assertEqual(new_count, initial_count + 1, "Adding a new vector increases the count by one")
        new_vector = self.repository.get_vector_at_given_index(3)
        self.assertEqual(new_vector.get_name_id(), "new_vector", "New vector has correct name_id")
        self.assertEqual(new_vector.get_colour(), "yellow", "New vector has correct colour")

    def test_get_all_vectors(self):
        all_vectors = self.repository.get_all_vectors()
        self.assertIsInstance(all_vectors, list, "Returned value is a list")
        self.assertEqual(len(all_vectors), 3, "Expected count of vectors")
        self.assertEqual(all_vectors[0].get_name_id(), "vector1", "Check name_id of first vector")

    def test_get_vector_at_given_index_valid_index(self):
        vector = self.repository.get_vector_at_given_index(1)
        self.assertEqual(vector.get_name_id(), "vector2", "Valid index returns correct vector name_id")

    def test_update_vector_at_given_index(self):
        self.repository.update_vector_at_given_index(1, "vector_updated", "orange", "2", [13, 14, 15])
        updated_vector = self.repository.get_vector_at_given_index(1)
        self.assertEqual(updated_vector.get_name_id(), "vector_updated", "Updated vector has correct name_id")
        self.assertEqual(updated_vector.get_colour(), "orange", "Updated vector has correct colour")
        self.assertEqual(updated_vector.get_values(), [13, 14, 15], "Updated vector has correct values")

    def test_update_vector_by_name_id(self):
        self.repository.update_vector_by_name_id("vector3", "purple", "4", [16, 17, 18])
        updated_vector = self.repository.get_vector_at_given_index(2)
        self.assertEqual(updated_vector.get_colour(), "purple", "Updated vector has correct colour")
        self.assertEqual(updated_vector.get_type(), "4", "Updated vector has correct type")
        self.assertEqual(updated_vector.get_values(), [16, 17, 18], "Updated vector has correct values")

    def test_delete_vector_by_index(self):
        initial_count = len(self.repository.get_all_vectors())
        self.repository.delete_vector_by_index(0)
        new_count = len(self.repository.get_all_vectors())
        self.assertEqual(new_count, initial_count - 1, "Deleting vector decreases count by one")

    def test_delete_vector_by_name_id(self):
        initial_count = len(self.repository.get_all_vectors())
        self.repository.delete_vector_by_name_id("vector2")
        new_count = len(self.repository.get_all_vectors())
        self.assertEqual(new_count, initial_count - 1, "Deleting vector by name_id decreases count by one")

    def test_get_vectors_having_the_minimum_less_than_a_given_value(self):
        filtered_vectors = self.repository.get_vectors_having_the_minimum_less_than_a_given_value(8)
        self.assertIsInstance(filtered_vectors, list, "Returned value is a list")
        self.assertTrue(all(min(vec.get_values()) < 8 for vec in filtered_vectors), "All vectors meet condition")
        self.assertTrue(len(filtered_vectors) > 0, "At least one vector meets the condition")

    def test_delete_vectors_having_max_value_equal_to_a_given_value(self):
        self.repository.delete_vectors_having_max_value_equal_to_a_given_value(8)
        self.repository.delete_vectors_having_max_value_equal_to_a_given_value(3)
        self.repository.delete_vectors_having_max_value_equal_to_a_given_value(12)

    def test_update_vectors_having_a_given_type_by_setting_their_color_to_the_same_given_value(self):
        self.repository.update_vectors_having_a_given_type_by_setting_their_color_to_the_same_given_value("2", "yellow")
        updated_vectors = [vec for vec in self.repository.get_all_vectors() if vec.get_type() == "2"]
        self.assertTrue(all(vec.get_colour() == "yellow" for vec in updated_vectors), "All updated vectors have correct colour")
        self.assertEqual(len(updated_vectors), 1, "Only one vector of type '2' was updated")
        self.assertTrue(all(vec.get_type() == "2" for vec in updated_vectors), "Updated vectors retain correct type")

if __name__ == '__main__':
    unittest.main()
