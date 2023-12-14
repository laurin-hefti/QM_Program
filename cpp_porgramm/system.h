#pragma once
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include "array.h"
#include "particle.h"
#include "functions.h"
#include "bond.h"
#include "HF.h"

class System {
private:
	Array<Nucleus*>* nucleus;
	Array<Bond*>* bonds;
	int charge;

	void calculate_charge() {
		for (int i = 0; this->nucleus->get_len(); i++) {
			this->charge += this->nucleus->get_element(i)->get_charge();
		}
	}


public:
	System(){
		this->nucleus = new Array<Nucleus*>;
		this->bonds = new Array<Bond*>;

		calculate_charge();
	}

	void add_nuc(std::string nn, double x, double y, double z, int charge) {
		int n = get_atom_number(nn)+1;
		Nucleus* nuc = new Nucleus(n, charge);
		nuc->set_pos(x, y, z);
		this->nucleus->add(nuc);
	}

	Array<Nucleus*>* get_nuc_ptr() {
		return this->nucleus;
	}

	Array<Bond*>* get_bond_ptr() {
		return this->bonds;
	}

	Nucleus* get_nuc(int i) {
		return this->nucleus->get_element(i);
	}

	void add_bond(int nuc1, int nuc2, int order) {
		Bond* bond = new Bond(this->nucleus->get_element(nuc1), this->nucleus->get_element(nuc2), order);
		this->bonds->add(bond);
	}

	void s_opt() {
		//simple_opt();
	}

	void H2O_test() {
		add_nuc("O", 0.0, 0.0, 0.0, 0);
		add_nuc("H", 1.0, 0.0, 0.0, 0);
		add_nuc("H", -1.0, 0.0, 0.0, 0);
		add_bond(0, 1, 1);
		add_bond(0, 2, 1);
	}

	void test_run() {
		
		add_nuc("H",0,0,0,0);
		add_nuc("H", 10, 0, 0, 0);
		add_bond(0, 1, 1);
		GTO* gto2 = new GTO(1, 0, 0, 0);
		CGTO* gto = new CGTO();
		gto->init_cgto(0,0,0);
		gto->add_new_gto(1);
		gto->add_new_gto(0.5);
		gto->add_new_gto(0.1);
		//std::cout << gto->self_overlap_one_d(-20, 20, 0.01, 1) << std::endl;
		

		//H2O_test();
		//add_nuc("He", 0, 0, 0, 0);

		Hartree_Fock* hf = new Hartree_Fock(this->nucleus);
		hf->test_run();
	}
};