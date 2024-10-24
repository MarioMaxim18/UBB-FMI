from PointRepo import PointRepository

def print_menu():
    print("Select an option")
    print("1.Add point to repository")
    print("2.Get all points")
    print("3.Get a point at a given index")
    print("4.Get all points of a given color")
    print("5.Get all points inside a given square(up-left corner and length)")
    print("6.Get the minimum distance between 2 points")
    print("7.Update point at a given index")
    print("8.Delete point by index")
    print("9.Delete all points that are inside a given square")
    print("10.Plot all points")
    print("11.Get points inside rectangle")
    print("12.Shift all points on the x axis")
    print("13.Delete all points inside circle")
    print("14.Quit")

def print_point_repo(repo):
    point_list = []
    for point in repo:
        point_list.append(str(point))
    print(point_list)

def read_ok():
    ok = int(input("Option:"))
    while ok not in [i for i in range(1, 15)]:
        print("Invalid ok.")
        ok = int(input("Please type in a valid ok:"))
    return ok

def get_input_1():
    [x, y] = input("Please type in the coordinates:").split()
    color = input("Please type in the color:")
    return float(x), float(y), color

def get_input_index():
    index = int(input("Please type in the index:"))
    return index

def get_input_color():
    color = input("Please type in the color:")
    return color

def get_input_square():
    [x, y, length] = input("Please type in the coordinates of the up-left corner and the length:").split()
    return float(x), float(y), float(length)

def get_input_rectangle():
    [x, y, length, width] = input("Please type in the coordinates of the up-left corner, the length and the width:").split()
    return float(x), float(y), float(length), float(width)

def get_input_7():
    index = get_input_index()
    [x, y] = input("Please type in the new coordinates:").split()
    color = input("Please type in the new color:")
    return index, float(x), float(y), color

def get_input_circle():
    [x, y, radius] = input("Please type in the coordinates of the center and the radius:").split()
    return float(x), float(y), float(radius)


def get_input_coordinates():
    [x, y] = input("Please type in the coordinates:").split()
    return float(x), float(y)

def data_examples(point_repo):
    data_examples = [
        ((3.5, 2.0), "red"),
        ((1.0, 4.5), "blue"),
        ((0.0, 0.0), "green"),
        ((-2.5, 1.8), "yellow"),
        ((6.0, 6.0), "blue"),
        ((-3.0, -3.0), "magenta"),
        ((2.5, -4.0), "blue"),
        ((7.2, 9.5), "magenta"),
        ((-1.0, -1.0), "green"),
        ((4.5, -2.5), "red")
    ]

    for coords, color in data_examples:
        x, y = coords
        point_repo.add_point(x, y, color)
def start_program():
    ok = 0
    point_repo = PointRepository()
    data_examples(point_repo)
    while ok != 14:
        print_menu()
        ok = read_ok()
        if ok == 1:
            [x, y, color] = get_input_1()
            point_repo.add_point(x, y, color)
        if ok == 2:
            print_point_repo(point_repo.get_all_points())
        if ok == 3:
            index = get_input_index()
            point = point_repo.get_point_at_given_index(index)
            print(str(point))
        if ok == 4:
            color = get_input_color()
            point = point_repo.get_points_of_given_color(color)
            print_point_repo(point)
        if ok == 5:
            [x, y, length] = get_input_square()
            point = point_repo.get_points_inside_square(x, y, length)
            print_point_repo(point)
        if ok == 6:
            min_distance = point_repo.get_minimum_distance_between_points()
            print(f"The minimum distance between all points is: {min_distance}")
        if ok == 7:
            index, x, y, color = get_input_7()
            point_repo.update_point_at_given_index(index, x, y, color)
            print_point_repo(point_repo.get_all_points())
        if ok == 8:
            index = get_input_index()
            point_repo.delete_point_by_index(index)
            print_point_repo(point_repo.get_all_points())
        if ok == 9:
            [x, y, length] = get_input_square()
            point_repo.delete_points_inside_square(x, y, length)
            print_point_repo(point_repo.get_all_points())
        if ok == 10:
            point_repo.plot_points()
        if ok == 11:
            [x, y, length, width] = get_input_rectangle()
            point = point_repo.get_points_inside_rectangle(x, y, length, width)
            print_point_repo(point)
        if ok == 12:
            x = int(input("Please type in the value:"))
            point_repo.shift_points_on_x(x)
            print_point_repo(point_repo.get_all_points())
        if ok == 13:
            [x, y, radius] = get_input_circle()
            point_repo.delete_points_inside_circle(x, y, radius)
            print_point_repo(point_repo.get_all_points())
        if ok == 14:
            break