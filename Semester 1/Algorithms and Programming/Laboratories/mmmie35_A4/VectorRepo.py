import math
import matplotlib.pyplot as plt
from my_vector import MyVector

class VectorRepository:
    def __init__(self):
        self.__repository = []

    """
    Description: THE FUNCTION ADD A VECTOR TO THE REPOSITORY
    Input: THE NAME, THE COLOR, THE TYPE AND THE VALUES OF THE VECTOR
    Output: THE VECTOR IS ADDED TO THE REPOSITORY
    """
    def add_vector(self, name_id, colour, type, values):
            if colour not in ["r", "g", "b", "y", "m"]:
                print("Invalid color")
            else:
                vector = MyVector(name_id, colour, type, values)
                self.__repository.append(vector)

    """
   Description: THE FUNCTION RETURN THE LIST OF VECTORS
   Input: -
   Output: THE LIST OF VECTORS
   """
    def get_all_vectors(self):
        try:
            return self.__repository
        except Exception as e:
            print("Invalid input")
            return None

    """
    Description: THE FUNCTION RETURN THE VECTOR AT A SPECIFIC INDEX
    Input: THE INDEX
    Output: THE VECTOR AT THE SPECIFIC INDEX
     """
    def get_vector_at_given_index(self, index):
        try:
            return self.__repository[index]
        except IndexError as ie:
            print("IndexError")
            return None
        except Exception as e:
            print("Invalid input")
            return None

    """
    Description: THE FUNCTION UPDATE THE VECTOR AT A SPECIFIC INDEX
    Input: THE INDEX, THE NAME, THE COLOR, THE TYPE AND THE VALUES OF THE VECTOR
    Output: THE VECTOR IS UPDATED
    """
    def update_vector_at_given_index(self, index, name_id, colour, type, values):
        try:
            vector = self.get_vector_at_given_index(index)
            vector.set_name_id(name_id)
            if colour not in ["r", "g", "b", "y", "m"]:
                print("Invalid color")
            vector.set_colour(colour)
            vector.set_type(type)
            vector.set_values(values)
        except ValueError as ve:
            print("Invalid value")
        except Exception as e:
            print("Invalid input")

    """
    Description: THE FUNCTION UPDATE THE VECTOR BY NAME_ID
    Input: THE NAME, THE COLOR, THE TYPE AND THE VALUES OF THE VECTOR
    Output: THE VECTOR IS UPDATED
    """
    def update_vector_by_name_id(self, name_id, new_name_id, colour, type, values):
        try:
            vector_found = False
            for vector in self.__repository:
                if vector.get_name_id() == name_id:
                    vector.set_name_id(new_name_id)
                    if colour not in ["r", "g", "b", "y", "m"]:
                        print("Invalid color")
                    vector.set_colour(colour)
                    vector.set_type(type)
                    vector.set_values(values)
                    vector_found = True

            if not vector_found:
                print("name_id not found")
        except Exception as e:
            print("Invalid input")

    """
    Description: THE FUNCTION DELETE THE VECTOR AT A SPECIFIC INDEX
  Input: THE INDEX
  Output: THE VECTOR IS DELETED
  """
    def delete_vector_by_index(self, index):
        try:
            self.__repository.pop(index)
        except IndexError as ie:
            print("IndexError")
        except Exception as e:
            print("Invalid input")

    """
    Description: THE FUNCTION DELETE THE VECTOR BY NAME_ID
    Input: THE NAME_ID
    Output: THE VECTOR IS DELETED
    """
    def delete_vector_by_name_id(self, name_id):
        try:
            vector_found = False
            for index, vector in enumerate(self.__repository):
                if vector.get_name_id() == name_id:
                    self.delete_vector_by_index(index)
                    vector_found = True

            if not vector_found:
                print("name_id not found")
        except Exception as e:
            print("Invalid input")

    """
    Description: THE FUNCTION PLOT ALL THE VECTORS
    Input: -
    Output: THE VECTORS ARE PLOTTED
    """
    def plot_all_vectors(self):
        def type_to_marker(type):
            if type == "1":
                return "o"
            elif type == "2":
                return "s"
            elif type == "3":
                return "^"
            else:
                return "D"

        for vector in self.__repository:
            plt.plot(vector.get_values(), marker=type_to_marker(vector.get_type()), color=vector.get_colour())
        plt.show()

    """
    Description: THE FUNCTION RETURN THE LIST OF VECTORS HAVING THE MINIMUM LESS THAN A GIVEN VALUE
    Input: THE VALUE
    Output: THE LIST OF VECTORS HAVING THE MINIMUM LESS THAN A GIVEN VALUE
    """
    def get_vectors_having_the_minimum_less_than_a_given_value(self, value):
        try:
            filtered_vectors = []
            for vector in self.__repository:
                if min(vector.get_values()) < value:
                    filtered_vectors.append(vector)
            return filtered_vectors
        except Exception as e:
            print("Invalid input")
            return None

    """
    Description: THE FUNCTION REMOVE VECTORS HAVING THE MAXIMUM EQUAL TO A GIVEN VALUE
    Input: THE VALUE
    Output: THE VECTORS ARE REMOVED
    """
    def delete_vectors_having_max_value_equal_to_a_given_value(self, value):
        try:
            for index, vector in enumerate(self.__repository):
                if max(vector.get_values()) == value:
                    self.delete_vector_by_index(index)
        except Exception as e:
            print("Invalid input")

    """
    Description: THE FUNCTION UPDATE VECTORS HAVING A GIVEN TYPE BY SETTING THEIR COLOR TO THE SAME GIVEN VALUE
    Input: THE TYPE AND THE VALUE
    Output: THE VECTORS ARE UPDATED
    """
    def update_vectors_having_a_given_type_by_setting_their_color_to_the_same_given_value(self, type, value):
        try:
            for vector in self.__repository:
                if vector.get_type() == type:
                    if value not in ["r", "g", "b", "y", "m"]:
                        print("Invalid color")
                    vector.set_colour(value)
        except ValueError as ve:
            print("Invalid value")
        except Exception as e:
            print("Invalid input")