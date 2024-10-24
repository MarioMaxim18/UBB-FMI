from VectorRepo import VectorRepository

def print_menu():
    print("Select an option")
    print("1.Add a vector to repository")
    print("2.Get all vectors")
    print("3.Get a vector at a given index")
    print("4.Update a vector at a given index")
    print("5.Update a vector identified by name_id")
    print("6.Delete a vector by index")
    print("7.Delete a vector by name_id")
    print("8.Plot all vectors")
    print("12.Get the list of vectors having the minimum less than a given value")
    print("20.Delete all vectors for which the max value is equal to a given value")
    print("23.Update all vectors having a given type by setting their color to the same given value")
    print("0.Quit")

def print_vector_repo(repo):
    vector_list = []
    for vector in repo:
        vector_list.append(str(vector))
    print(vector_list)

def read_ok():
    ok = int(input("Option:"))
    return ok

def data_examples(repo):
    repo.add_vector("v1", "r", "4", [1, 2, 3])
    repo.add_vector("v2", "b", "3", [4, 5, 6])
    repo.add_vector("v3", "g", "2", [7, 8])
    repo.add_vector("v4", "y", "1", [9, 10])
    repo.add_vector("v5", "r", "6", [11, 12])
    repo.add_vector("v6", "m", "5", [13, 14, 18, 20])
    repo.add_vector("v7", "r", "4", [21, 22])
    repo.add_vector("v8", "b", "3", [23, 24])
    repo.add_vector("v9", "y", "2", [26, 30])
    repo.add_vector("v10", "b", "1", [27, 28])

def start_program():
    repo = VectorRepository()
    data_examples(repo)
    while True:
        print_menu()
        ok = read_ok()
        if ok == 1:
            name_id = input("Please type in the name_id:")
            colour = input("Please type in the colour:")
            type = input("Please type in the type:")
            values = input("Please type in the values:")
            repo.add_vector(name_id, colour, type, values)
        elif ok == 2:
            print_vector_repo(repo.get_all_vectors())
        elif ok == 3:
            index = int(input("Please type in the index:"))
            print(repo.get_vector_at_given_index(index))
        elif ok == 4:
            index = int(input("Please type in the index:"))
            name_id = input("Please type in the new name_id:")
            colour = input("Please type in the new colour:")
            type = input("Please type in the new type:")
            values = input("Please type in the new values:")
            repo.update_vector_at_given_index(index, name_id, colour, type, values)
        elif ok == 5:
            name_id = input("Please type in the name_id:")
            new_name_id = input("Please type in the new name_id:")
            colour = input("Please type in the new colour:")
            type = input("Please type in the new type:")
            values = input("Please type in the new values:")
            repo.update_vector_by_name_id(name_id, new_name_id, colour, type, values)
        elif ok == 6:
            index = int(input("Please type in the index:"))
            repo.delete_vector_by_index(index)
        elif ok == 7:
            name_id = input("Please type in the name_id:")
            repo.delete_vector_by_name_id(name_id)
        elif ok == 8:
            repo.plot_all_vectors()
        elif ok == 12:
            value = int(input("Please enter the value:"))
            vectors_min_value = repo.get_vectors_having_the_minimum_less_than_a_given_value(value)
            print_vector_repo(vectors_min_value)
        elif ok == 20:
            value = int(input("Please enter the value:"))
            repo.delete_vectors_having_max_value_equal_to_a_given_value(value)
        elif ok == 23:
            type = input("Please enter the type:")
            color_value = input("Please enter the color value:")
            repo.update_vectors_having_a_given_type_by_setting_their_color_to_the_same_given_value(type,color_value)
        elif ok == 0:
            break