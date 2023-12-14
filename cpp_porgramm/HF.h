#pragma once
#include <iostream>
#include <cmath>
#include "array.h"
#include "particle.h"
#include "functions.h"
#include "gto.h"

class Hartree_Fock {
private:
	//System* sys;
	Array<Nucleus*>* nuc_ptr;
	Array<Vector*>* nuc_pos;

	Array<Electron*>* electrons;

	Matrix* overlap_matrix;
	Matrix* potetntial_energy_matrix;
	Matrix* fock_matrix;
	Matrix* coef_matrix;
	Matrix* eigv_matirx;

	void set_nuc() {
		for (int i = 0; i < this->nuc_ptr->get_len(); i++) {
			this->nuc_pos->add(this->nuc_ptr->get_element(i)->get_pos());
		}
	}

	void set_electrons() {
		for (int i = 0; i < this->nuc_ptr->get_len(); i++) {
			for (int j = 0; j < this->nuc_ptr->get_element(i)->get_final_charge(); j++) {
				this->electrons->add(this->nuc_ptr->get_element(i)->get_electron_ptr(j));
			}
		}
	}

	double overlap_integral(int i, int j) {
		double summe = 0; 

		Electron* e1 = this->electrons->get_element(i);
		Electron* e2 = this->electrons->get_element(j);

		double d = std::abs(e1->pos->get_sub_vec_len(e2->pos));
		
		double x1 = -40 -(d/2);
		//double x2 = 20 + (d/2);
		double x2 = -(d / 2) + 40;
		double dx = 0.01;

		//std::cout << x1 << " " << x2 << std::endl;
		//std::cout << d << std::endl;

		while (x1 < x2) {
			summe += (e1->get_wave_walue(x1+(d/2)) *
				e2->get_wave_walue(x1-(d/2))) * dx;
			//summe += e1->get_wave_walue(x1 + (d / 2)) * e1->get_wave_walue(x1 + (d / 2)) * dx;
			//antrysymetric principal
			x1 += dx;
		}

		return summe;

	}

	double get_attraction(int q1, int q2, double r) {
		return culomb_const * (elementarladung * q1 * elementarladung * q2) / (r * r);
	}

	double get_attraction2(int q1, int q2, double r) {
		return (q1 * q2) / (r * r);
	}

	double kinetic_integral(int i, int j) {
		double sum = 0;

		Electron* e1 = this->electrons->get_element(i);
		Electron* e2 = this->electrons->get_element(j);

		double d = std::abs(e1->pos->get_sub_vec_len(e2->pos));

		double x1 = -20 - (d / 2);
		//double x2 = 20 + (d / 2);
		double x2 = -(d / 2) + 20;
		double dx = 0.01;

		while (x1 < x2) {
			sum += e1->get_wave_walue(x1 + (d / 2)) *
				e2->get_wave_walue(x1 - (d / 2)) * dx;
			x1 += dx;
		}

		return sum;
	}

	double potential_energy_integral(int i, int j) {
		double sum = 0;

		Electron* e1 = this->electrons->get_element(i);
		Electron* e2 = this->electrons->get_element(j);

		Nucleus* nuc;

		std::cout << j << " " << this->electrons->get_len() << std::endl;

		double d = std::abs(e1->pos->get_sub_vec_len(e2->pos));

		double x1 = -20 - (d / 2);
		//double x2 = 20 + (d / 2);
		double x2 = -(d / 2) + 20;
		double dx = 0.01;

		for (int k = 0; k < this->nuc_ptr->get_len(); k++) {
			nuc = this->nuc_ptr->get_element(k);

			while (x1 < x2) {
				sum += e1->get_wave_walue(x1 + (d / 2)) *
					e2->get_wave_walue(x1 - (d / 2)) *
					get_attraction2(nuc->get_number(), 1, x1 + (d / 2)) * dx * std::pow(x1 + (d / 2), 2); //integrate over every potential nucleus
				x1 += dx;
			}

			x1 = -20 - (d / 2);
		}

		return sum;
	}

	void set_overlap_matrix() {
		for (int i = 0; i < this->electrons->get_len(); i++) {
			for (int j = i; j < this->electrons->get_len(); j++) {
				double overlap = overlap_integral(i, j);
				this->overlap_matrix->insert_element(i,j,overlap);
				this->overlap_matrix->insert_element(j, i, overlap);
			}
		}
	}

	void set_potential_energy_matrix(){
		for (int i = 0; i < this->electrons->get_len(); i++) {
			for (int j = 0; j < this->electrons->get_len(); j++) {
				double potential = potential_energy_integral(i, j);
				this->potetntial_energy_matrix->insert_element(i, j, potential);
			}
		}
	}

public:
	Hartree_Fock(Array<Nucleus*>* nuc_ptr) {
		//this->sys = sys;
		this->nuc_ptr = nuc_ptr;
		nuc_pos = new Array<Vector*>;
		electrons = new Array<Electron*>;

		set_nuc();
		set_electrons();

		overlap_matrix = new Matrix(this->electrons->get_len(), this->electrons->get_len());
		potetntial_energy_matrix = new Matrix(this->electrons->get_len(), this->electrons->get_len());
	}

	void test_run() {
		set_overlap_matrix();
		this->overlap_matrix->print();
		set_potential_energy_matrix();
		this->potetntial_energy_matrix->print();
	}
};