#pragma once
#include <iostream>
#include <cmath>
#include "array.h"
#include "functions.h"

class gto_family {
public:
	double get_value_one_d(double x, int axis) {};

	double num_integrate_one_d(double x1, double x2, double dx, int axis) {};
};

class GTO : gto_family{
private:
	//zeta, i, j, k
	Array<double>* components;
	Array<double>* normalize;




public:

	GTO(double zeta, int i, int j, int k) {
		this->components = new Array<double>;
		this->normalize = new Array<double>;
		this->components->add(zeta);
		this->components->add(i);
		this->components->add(j);
		this->components->add(k);
		double v = 0;
		for (int i = 0; i < 3; i++) {
			this->normalize->add(1);
			//this->normalize->insert(i,this->num_integrate_one_d(-20, 20, 0.01, i+1));
			v = this->self_overlap_one_d(-40, 40, 0.01, i + 1);
			//std::cout << v << std::endl;
			this->normalize->insert(i, std::sqrt(v));
			//std::cout << v / this->normalize->get_element(i);
			//std::cout << this->normalize->get_element(i) << std::endl;
		}
	}

	double self_overlap_one_d(double x1, double x2, double dx, int angle) {
		double summe = 0;

		while (x1 < x2) {
			summe += std::abs(std::pow(get_value_one_d(x1, angle), 2)) * dx;
			x1 += dx;
		}

		return summe;
	}

	double get_self_overlap_value(double x, int axis) {
		return std::pow(x, this->components->get_element(axis)*2) *
			std::pow(e, -this->components->get_element(0) * (x * x));
	}


	double get_value_one_d(double x, int axis) {
		return std::pow(x, this->components->get_element(axis)) *
			std::pow(e, -this->components->get_element(0) * (x * x)) /
			this->normalize->get_element(axis-1);
	}

	double get_valu_one_d_no_norm(double x, int axis) {
		return std::pow(x, this->components->get_element(axis)) *
			std::pow(e, -this->components->get_element(0) * (x * x));
	}


	double num_integrate_one_d(double x1, double x2, double dx, int axis) {
		/*
		double normalisation = std::pow(2 * this->components->get_element(0) / pi, 0.25) *
			std::sqrt(std::pow(4 * this->components->get_element(0), this->components->get_element(axis)) /
				double_fac(2 * this->components->get_element(axis) - 1));
		*/

		double summe = 0;

		while (x1 < x2) {
			summe += std::abs(get_value_one_d(x1, axis)) * dx;
			x1 += dx;
		}
		return summe;
	}
};

class CGTO : gto_family{
private:
	Array<GTO*>* gtos;
	Array<double>* coef;
	Array<int>* axis;
	Array<double>* normalize;
	bool initialised;

public:
	CGTO() {
		this->gtos = new Array<GTO*>;
		this->coef = new Array<double>;
		this->axis = new Array<int>;
		this->normalize = new Array<double>;
		this->initialised = false;
	}

	void addGTO(GTO* gto) {
		this->gtos->add(gto);
		this->coef->add(1);
	}

	void init_cgto(int i, int j, int k) {
		this->axis->add(i);
		this->axis->add(j);
		this->axis->add(k);
	}

	void add_new_gto(double zeta) {
		GTO* gto = new GTO(zeta, this->axis->get_element(0), this->axis->get_element(1), this->axis->get_element(2));
		this->gtos->add(gto);
		this->coef->add(1);
	}

	void set_normalize() {
		double v = 0;
		for (int i = 0; i < 3; i++) {
			v = this->self_overlap_one_d(-40, 40, 0.01, i + 1);
			v = std::sqrt(v);
			this->normalize->insert(i,v);
		}
	}

	double get_value_one_d(double x, int axis) {

		if (this->initialised != true) {
			this->initialised = true;
			for (int i = 0; i < this->gtos->get_len(); i++) {
				this->normalize->add(1);
			}
			this->set_normalize();
		}

		double summ = 0;
		for (int i = 0; i < this->gtos->get_len(); i++) {
			summ += this->coef->get_element(i) * this->gtos->get_element(i)->get_value_one_d(x, axis);
		}
		//maybe without normalisation
		return summ/this->normalize->get_element(axis-1);
	}

	double self_overlap_one_d(double x1, double x2, double dx, int angle) {
		double summe = 0;

		while (x1 < x2) {
			summe += std::abs(std::pow(get_value_one_d(x1, angle), 2)) * dx;
			x1 += dx;
		}

		return summe;
	}

	double num_integrate_one_d(double x1, double x2, double dx, int axis) {
		double summ = 0;

		while (x1 < x2) {
			//with normalisation
			summ += abs(get_value_one_d(x1, axis))* dx;
			x1 += dx;
		}

		return summ;
	}
};