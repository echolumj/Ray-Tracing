#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"
#include "aabb.h"

class hitableList : public hitable
{
public:
	hitableList() {}
	hitableList(std::shared_ptr<hitable> object) { add(object); }

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& record) const;
	void add(std::shared_ptr<hitable> object);

	aabb bounding_box(void) const override { return _aabb;}
	std::vector<std::shared_ptr<hitable>> get_objects() const { return _list; }

private:
	std::vector<std::shared_ptr<hitable>> _list;
	aabb _aabb;
};

#endif