extends Node2D
class_name Complex

var _z: Vector2 = Vector2()

static func new(re: float, im: float) -> Complex:
	var complex = Complex.new()
	complex._z.x = re
	complex._z.y = im
	return complex

func add(z: Complex) -> Complex:
	self._z.x = self._z.x + z._z.x
	self._z.y = self._z.y + z._z.y
	return self

func sub(z: Complex) -> Complex:
	self._z.x = self._z.x - z._z.x
	self._z.y = self._z.y - z._z.y
	return self
