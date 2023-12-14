#pragma once
#include "array.h"
#include "particle.h"


class Bond {
private:
	Nucleus* nucleus1;
	Nucleus* nucleus2;
	int order;

public:
	Bond(Nucleus* n1, Nucleus* n2, int order) {
		this->nucleus1 = n1;
		this->nucleus2 = n2;
		this->order = order;
	}

	double get_distance() {
		return this->nucleus1->pos->get_sub_vec_len(this->nucleus2->pos);
	}

	Vector* get_vec() {
		return this->nucleus1->pos->get_sub_vec(this->nucleus2->pos);
	}
};