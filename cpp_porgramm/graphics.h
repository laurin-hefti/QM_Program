#pragma once
#include "array.h"
#include "HF.h"

bool is_inside(Vector2D* vec, Vector2D* center, double r) {
	if (vec->get_sub_vec_len(center) <= r) {
		return true;
	}
	else {
		return false;
	}
}

bool graph(int x, int y, int x1, int x2, int dx, int dy, GTO* gto, int axis) {
	double rx = x - (int)(dx / 2);
	double value = gto->get_self_overlap_value(rx/20, axis);
	Vector2D* vec1 = new Vector2D();
	Vector2D* vec2 = new Vector2D();
	vec1->set_vec((double)x, value*100);
	vec2->set_vec((double)x, (double)y);
	bool result = is_inside(vec1, vec2, 1);
	delete vec1;
	delete vec2;
	return result;
}

bool graph2(int x, int y, int x1, int x2, int dx, int dy, GTO* gto, int axis) {
	double rx = x - (int)(dx / 2);
	double value = gto->get_value_one_d(rx / 20, axis);
	Vector2D* vec1 = new Vector2D();
	Vector2D* vec2 = new Vector2D();
	vec1->set_vec((double)x, value * 100);
	vec2->set_vec((double)x, (double)y);
	bool result = is_inside(vec1, vec2, 1);
	delete vec1;
	delete vec2;
	return result;
}