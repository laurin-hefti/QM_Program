#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include "particle.h"
#include "gto.h"

double e = 2.7182818284;
double pi = 3.141592653589793;

// units J * Hz-1
double planks_konst = 6.62607015 * 10e-34;
double reduzierte_planks_konst = 1.054571817 * 10e-34;

double mass_electron = 9.1093837015 * 10e-31;

// unit coulomb
double elementarladung = 1.602176634 * 10e-19;

// unit amper * second / volt * meter
double electric_field_const = 8.8541878128 * 10e-12;

double culomb_const = 1 / (4 * pi * electric_field_const);

int fakultät(int i) {
	int summe = 1;
	for (int j = i; j > 0; j--) {
		summe *= j;
	}
	return summe;
}

int double_fac(int i) {
	int summe = 1;
	int j = i;
	while (j - 2 > 0) {
		summe *= j;
		j -= 2;
	}
	return summe;
}

std::string atoms_name[128] = { "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne"};

std::string get_atom_name(int i) {
	return atoms_name[i-1];
}

int get_atom_number(std::string name) {
	int n = -1;
	for (int i = 0; i < 128; i++) {
		if (atoms_name[i] == name) {
			n = i;
			break;
		}
	}
	return n;
}

int step(double x) {
	if (x == 0) {
		return 0;
	}
	else if (x > 0) {
		return 1;
	}
	else {
		return -1; 
	}
}
