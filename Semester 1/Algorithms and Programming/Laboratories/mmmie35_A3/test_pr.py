from math import sqrt
from PointRepo import PointRepository
from my_point import MyPoint

def should_delete_point_by_index():
    point_repo = PointRepository()
    point_repo.add_point(1, 2, "red")
    point_repo.add_point(2, 3, "blue")
    point_repo.add_point(3, 4, "green")
    point_repo.add_point(4, 5, "magenta")
    point_repo.add_point(5, 6, "yellow")
    point_repo.delete_point_by_index(2)
    assert len(point_repo.get_all_points()) == 4

def shift_points_on_x():
    point_repo = PointRepository()
    point_repo.add_point(1, 2, "red")
    point_repo.add_point(2, 3, "blue")
    point_repo.add_point(3, 4, "green")
    point_repo.add_point(4, 5, "magenta")
    point_repo.add_point(5, 6, "yellow")
    point_repo.shift_points_on_x(2)
    assert point_repo.get_all_points()[0].get_coord_x() == 3
    assert point_repo.get_all_points()[1].get_coord_x() == 4
    assert point_repo.get_all_points()[2].get_coord_x() == 5
    assert point_repo.get_all_points()[3].get_coord_x() == 6
    assert point_repo.get_all_points()[4].get_coord_x() == 7

def should_get_minimum_distance_between_points():
    point_repo = PointRepository()
    point_repo.add_point(1, 2, "red")
    point_repo.add_point(2, 3, "blue")
    point_repo.add_point(3, 4, "green")
    point_repo.add_point(4, 5, "magenta")
    point_repo.add_point(5, 6, "yellow")
    assert point_repo.get_minimum_distance_between_points() == sqrt(2)

should_delete_point_by_index()
shift_points_on_x()
should_get_minimum_distance_between_points()