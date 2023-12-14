#pragma once
#include <iostream>
#include <cmath>
#include "array.h"
#include "gto.h"

class Electron {
private:
	CGTO* wavefunction;

public:
	Vector* pos;
	int pot;

	Electron(Vector* pos, int pot) {
		this->wavefunction = new CGTO();
		wavefunction->init_cgto(0, 0, 0);
		wavefunction->add_new_gto(1);
		wavefunction->add_new_gto(0.5);
		wavefunction->add_new_gto(0.1);

		this->pos = pos;
		this->pot = pot;
	}

	double get_wave_walue(double x) {
		return this->wavefunction->get_value_one_d(x, 1);
	}

};

class Nucleus {
private:
	int n; 
	int charge;
	int final_charge;
	Electron* e[128];

	void init_electrons() {
		for (int i = 0; i < std::round((final_charge+0.5)/2); i++) {
			this->e[i] = new Electron(this->pos,this->n);
			//std::cout << "test" << std::endl;
		}
	}

public:
	Vector* pos;

	Nucleus(int i, int charge) {
		this->pos = new Vector();
		this->n = i; 
		this->charge = charge;
		this->final_charge = this->n - this->charge;

		init_electrons();
	}

	int get_charge() {
		return this->charge;
	}

	int get_final_charge() {
		return this->final_charge;
	}

	int get_number() {
		return this->n;
	}

	Vector* get_pos() {
		return this->pos;
	}
	
	void set_pos(double x, double y, double z) {
		this->pos->set_vec(x, y, z);
	}

	Electron* get_electron_ptr(int n) {
		return this->e[n];
	}

};
