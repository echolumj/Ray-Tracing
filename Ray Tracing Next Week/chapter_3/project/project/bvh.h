#ifndef BVHH
#define BVHH

#include "hitable.h"
class bvh : public hitable
{
public:

	virtual	bool hit(const ray& r, float tmin, float tmax, hit_record& record) const override;
	virtual aabb bounding_box(void) const override {return _aabb;}

private:
	std::shared_ptr<hitable> _left;
	std::shared_ptr<hitable> _right;

	aabb _aabb;
};


#endif
