import math
import matplotlib.pyplot as plt
from my_point import *

class PointRepository:
    def __init__(self):
        self.__repository = []

    """
    Description: THE FUNCTION ADD A POINT TO THE REPOSITORY
    Input: THE COORDINATES AND THE COLOR OF THE POINT
    Output: THE POINT IS ADDED TO THE REPOSITORY
    """
    def add_point(self, x, y, color):
        point = MyPoint(x, y, color)
        self.__repository.append(point)

    """
    Description: THE FUNCTION RETURN THE LIST OF POINTS
    Input: -
    Output: THE LIST OF POINTS
    """
    def get_all_points(self):
        return self.__repository

    """
    Description: THE FUNCTION RETURN THE POINT AT A SPECIFIC INDEX
    Input: THE INDEX
    Output: THE POINT AT THE SPECIFIC INDEX
    """
    def get_point_at_given_index(self, index):
        try:
            return self.__repository[index]
        except IndexError:
            print("Invalid Index")

    """
    Description: THE FUNCTION RETURN THE LIST OF POINTS OF A SPECIFIC COLOR
    Input: THE COLOR
    Output: THE LIST OF POINTS OF A SPECIFIC COLOR
    """
    def get_points_of_given_color(self, color):
        if color not in ["red", "green", "blue", "magenta", "yellow"]:
            raise ValueError("Invalid color")
        else:
            points_list = []
            for point in self.__repository:
                if point.get_color() == color:
                    points_list.append(point)
            return points_list

    """
    Description: THE FUNCTION RETURN THE LIST OF POINTS INSIDE A SQUARE
    Input: THE COORDINATES OF THE UP-LEFT CORNER AND THE LENGTH
    Output: THE LIST OF POINTS INSIDE A SQUARE
    """
    def get_points_inside_square(self, x, y, length):
        inside_points = []
        for point in self.__repository:
            point_x = point.get_coord_x()
            point_y = point.get_coord_y()
            if x <= point_x <= x + length and y - length <= point_y <= y:
                inside_points.append(point)
        return inside_points

    """
    Description: THE FUNCTION RETURN THE MINIMUM DISTANCE BETWEEN 2 POINTS
    Input: -
    Output: THE MINIMUM DISTANCE BETWEEN 2 POINTS
    """
    def get_minimum_distance_between_points(self):
        minimum_distance = 9999999999999999
        for i in range(len(self.__repository)):
            for j in range(i + 1, len(self.__repository)):
                point1 = self.__repository[i]
                point2 = self.__repository[j]
                distance = math.sqrt((point1.get_coord_x() - point2.get_coord_x()) ** 2 + (
                        point1.get_coord_y() - point2.get_coord_y()) ** 2)
                if distance < minimum_distance:
                    minimum_distance = distance
        return minimum_distance

    """
    Description: THE FUNCTION UPDATE THE POINT AT A SPECIFIC INDEX
    Input: THE INDEX, THE NEW COORDINATES AND THE NEW COLOR
    Output: THE POINT AT THE SPECIFIC INDEX IS UPDATED
    """
    def update_point_at_given_index(self, index, x, y, color):
        try:
            point = self.get_point_at_given_index(index)
        except IndexError:
            print("Invalid index.")
        try:
            point.set_coord_x(x)
            point.set_coord_y(y)
            point.set_color(color)
        except ValueError:
            print("Invalid data")

    """
    Description: THE FUNCTION DELETE THE POINT AT A SPECIFIC INDEX
    Input: THE INDEX
    Output: THE POINT AT THE SPECIFIC INDEX IS DELETED
    """
    def delete_point_by_index(self, index):
        try:
            self.__repository.pop(index)
        except IndexError:
            print("Invalid index.")

    """
    Description: THE FUNCTION DELETE THE POINTS INSIDE A SQUARE
    Input: THE COORDINATES OF THE UP-LEFT CORNER AND THE LENGTH
    Output: THE POINTS INSIDE A SQUARE ARE DELETED
    """
    def delete_points_inside_square(self, x, y, length):
        points_to_delete = self.get_points_inside_square(x, y, length)
        for point in points_to_delete:
            self.__repository.remove(point)

    """
    Description: THE FUNCTION PLOT ALL THE POINTS
    Input: -
    Output: THE POINTS ARE PLOTTED
    """
    def plot_points(self):
        x = [point.get_coord_x() for point in self.__repository]
        y = [point.get_coord_y() for point in self.__repository]
        col = [point.get_color() for point in self.__repository]

        plt.scatter(x, y, c=col)
        plt.show()

    """
    Description: THE FUNCTION RETURN THE LIST OF POINTS INSIDE A RECTANGLE
    Input: THE COORDINATES OF THE UP-LEFT CORNER, THE LENGTH AND THE WIDTH
    Output: THE LIST OF POINTS INSIDE A RECTANGLE
    """
    def get_points_inside_rectangle(self, x, y, length, width):
        inside_points = []
        for point in self.__repository:
            point_x = point.get_coord_x()
            point_y = point.get_coord_y()
            if x <= point_x <= x + length and y <= point_y <= y + width:
                inside_points.append(point)
        return inside_points

    """
    Description: THE FUNCTION SHIFT ALL THE POINTS ON THE X AXIS
    Input: THE VALUE WITH WHICH THE POINTS ARE SHIFTED
    Output: THE POINTS ARE SHIFTED ON THE X AXIS
    """
    def shift_points_on_x(self, value):
        for i in range(len(self.__repository)):
            self.__repository[i].set_coord_x(self.__repository[i].get_coord_x()+value)
    """
    Description: THE FUNCTION DELETE THE POINT BY COORDINATES
    Input: THE COORDINATES
    Output: THE POINT IS DELETED
    """
    def delete_by_coordinates(self, x, y):
        found = 0
        for point in self.__repository:
            if point.get_coord_x() == float(x) and point.get_coord_y() == float(y):
                found = 1
                self.__repository.remove(point)
        if found == 0:
            print("Point not found.")

    """
    Description: THE FUNCTION DELETE THE POINTS INSIDE A CIRCLE
    Input: THE COORDINATES OF THE CENTER AND THE RADIUS
    Output: THE POINTS INSIDE A CIRCLE ARE DELETED
    """
    def delete_points_inside_circle(self, x, y, radius):
        for point in self.__repository:
            if (x - point.get_coord_x()) ** 2 + (y - point.get_coord_y()) ** 2 <= radius ** 2:
                self.delete_by_coordinates(point.get_coord_x(),point.get_coord_y())