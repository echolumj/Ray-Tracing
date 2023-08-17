#ifndef BVHH
#define BVHH

#include "hitableList.h"

class bvh : public hitable
{
public:
	bvh(const hitableList& list) : bvh(list.get_objects(), 0, list.get_objects().size() - 1) {}
	bvh(const std::vector<std::shared_ptr<hitable>>& src_objects, size_t start, size_t end);

	virtual	bool hit(const ray& r, float tmin, float tmax, hit_record& record) const override;
	virtual aabb bounding_box(void) const override {return _aabb;}

	inline double random_double(double min, double max) {
		double range = (max - min);
		double div = RAND_MAX / range;
		return min + (rand() / div);
	} 

	inline int random_int(int min, int max) {
		// Returns a random integer in [min,max].
		return static_cast<int>(random_double(min, max + 1));
	}
private:
	static bool box_compare(const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b, int axis_index);

private:
	std::shared_ptr<hitable> _left;
	std::shared_ptr<hitable> _right;

	aabb _aabb;
	//bool _is_leaf = false;
};


static bool box_compare(
	const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b, int axis_index
) {
	return a->bounding_box()[axis_index]._left < b->bounding_box()[axis_index]._left;
}

static bool box_x_compare(const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b) {
	return box_compare(a, b, 0);
}

static bool box_y_compare(const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b) {
	return box_compare(a, b, 1);
}

static bool box_z_compare(const std::shared_ptr<hitable> a, const std::shared_ptr<hitable> b) {
	return box_compare(a, b, 2);
}

#endif
