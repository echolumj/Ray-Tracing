#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitableList : public hitable
{
public:
	hitableList(){}

	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& record) const;
	void add(std::shared_ptr<hitable> object) { _list.emplace_back(object);}

private:
	std::vector<std::shared_ptr<hitable>> _list;
};

bool hitableList::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{
	hit_record midRec;
	bool hitFlag = false;
	double t_min = tmax;
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->hit(r, tmin, t_min, midRec))
		{
			hitFlag = true;
			t_min = midRec.t;
			record = midRec;
		}
	}
	return hitFlag;
}

#endif