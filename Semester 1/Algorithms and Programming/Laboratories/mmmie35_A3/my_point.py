class MyPoint:
    def __init__(self, x, y, color):
        self.__coord_x = x
        self.__coord_y = y
        self.__color = color

    def get_coord_x(self):
        return self.__coord_x

    def get_coord_y(self):
        return self.__coord_y

    def get_color(self):
        return self.__color

    def set_coord_x(self, x):
        self.__coord_x = x

    def set_coord_y(self, y):
        self.__coord_y = y

    def set_color(self, color):
        self.__color = color

    def __str__(self):
        return f"Point({self.__coord_x}, {self.__coord_y}) of color {self.__color}"
