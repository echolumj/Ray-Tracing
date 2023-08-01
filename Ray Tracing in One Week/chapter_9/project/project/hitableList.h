#ifndef HITABLELISTH
#define HITABLELISTH

#include "hitable.h"

class hitableList : public hitable
{
public:
	hitable **list;
	int listSize;

	hitableList(){}
	hitableList(hitable **l, int n) { list = l; listSize = n;}
	virtual bool hit(const ray& r, float tmin, float tmax, hit_record& record) const;
};

bool hitableList::hit(const ray& r, float tmin, float tmax, hit_record& record) const
{
	hit_record midRec;
	bool hitFlag = false;
	double t_min = tmax;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->hit(r, tmin, t_min, midRec))
		{
			hitFlag = true;
			t_min = midRec.t;
			record = midRec;
		}
	}
	return hitFlag;
}

#endif