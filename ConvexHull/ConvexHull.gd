extends Node2D

const color := Color(1.0, 1.0, 0.0)

const random_constant = 100

var points: PoolVector2Array
var convex_hull: PoolVector2Array
var ch_colors: PoolColorArray
var pts_colors: PoolColorArray

func _ready() -> void:
	var _screen_size: Vector2 = get_viewport_rect().size
	var _half_width: float = _screen_size.x / 2
	var _half_height: float = _screen_size.y / 2
	
	for i in range(0, random_constant):
		var v: Vector2
		if i >= random_constant / 2:
			v = Vector2(_half_width-i, _half_height-i)
		else:
			v = Vector2(_half_width-i, _half_height+i)
		points.append(v)
	
	for i in range(0, random_constant):
		pts_colors.append(Color(1.0, 1.0, 0.0))
		
	convex_hull = Geometry.convex_hull_2d(points)
	
	for i in range(0, convex_hull.size()):
		var c = Color(1.0, 1.0, 1.0)
		ch_colors.append(c)
	
func _physics_process(_delta: float) -> void:
	pass	
	
func _draw() -> void:
	var _distance:float = 100.0
	var _screen_size: Vector2 = get_viewport_rect().size
	var _half_width: float = _screen_size.x / 2
	var _half_height: float = _screen_size.y / 2
	var from := Vector2(0, _half_height / 2)
	var to   := Vector2(_half_width + _distance, _half_height / 2) 
	
	for i in range(0, 10):
		if i % 2 == 0:
			to += Vector2(_distance, 0)
		else:
			to += Vector2(_distance * 2, -_distance)
		
		var current_color := _random_color()			
		draw_line(from, to, current_color)
		from = to

func _random_color() -> Color:
	return Color(randi() % 2, randi() % 2, randi() % 2)
