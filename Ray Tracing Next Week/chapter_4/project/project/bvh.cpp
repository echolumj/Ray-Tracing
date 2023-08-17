#include "bvh.h"

bvh::bvh(const std::vector<std::shared_ptr<hitable>>& src_objects, size_t start, size_t end)
{
	/*
	auto objects = src_objects;
	_aabb = objects[start]->bounding_box();
	for (int i = start + 1; i <= end; ++i)
		_aabb = aabb(_aabb, objects[i]->bounding_box());

	interval<float> longAxis = _aabb[0];
	float span = longAxis._right - longAxis._left;
	int idx = 0;
	for (int i = 1; i < 3; ++i)
	{
		float midSpan = _aabb[i]._right - _aabb[i]._left;
		if (midSpan > span)
		{
			longAxis = _aabb[i];
			span = midSpan;
			idx = i;
		}
	}

	//2. split objects
	if (start == end)
	{
		_left = objects[start];
		_right = objects[start];
	}
	else if (end - start == 1)
	{
		_left = objects[start];
		_right = objects[end];
	}
	else
	{
		auto comparator = (idx == 0) ? box_x_compare
			: (idx == 1) ? box_y_compare
			: box_z_compare;
		sort(objects.begin() + start, objects.begin() + end + 1, comparator);

		_left = std::make_shared<bvh>(objects, start, (end + start) / 2);
		_right = std::make_shared<bvh>(objects, (end + start) / 2 + 1, end);
	}*/
	auto objects = src_objects; // Create a modifiable array of the source scene objects

	int axis = random_int(0, 2);
	auto comparator = (axis == 0) ? box_x_compare
		: (axis == 1) ? box_y_compare
		: box_z_compare;

	size_t object_span = end - start;

	if (object_span == 0) {
		_left = _right = objects[start];
	}
	else if (object_span == 1) {
		if (comparator(objects[start], objects[start + 1])) {
			_left = objects[start];
			_right = objects[start + 1];
		}
		else {
			_left = objects[start + 1];
			_right = objects[start];
		}
	}
	else {
		std::sort(objects.begin() + start, objects.begin() + end + 1, comparator);

		auto mid = (start + end)/ 2;
		_left = std::make_shared<bvh>(objects, start, mid);
		_right = std::make_shared<bvh>(objects, mid+1, end);
	}

	_aabb = aabb(_left->bounding_box(), _right->bounding_box());
}

bool bvh::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{
	if (!_aabb.hit(r, interval<float>(tmin, tmax)))
		return false;
	bool isLeft = false;
	bool isRight = false;
	isLeft = _left->hit(r, tmin, tmax, record);
	isRight = _right->hit(r, tmin, (isLeft? record.t: tmax), record);

	return isLeft || isRight;
}

bool bvh::box_compare(const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b, int axis_index)
{
	if (a->bounding_box()[axis_index]._left < b->bounding_box()[axis_index]._left)
		return true;
	else if (a->bounding_box()[axis_index]._left == b->bounding_box()[axis_index]._left)
	{
		return a->bounding_box()[axis_index]._right < b->bounding_box()[axis_index]._right;
	}
	return false;
}