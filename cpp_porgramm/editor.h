#pragma once
#include<iostream>
#include "system.h"
#include "functions.h"

class Handelprog {
private:
	System* sys;
	std::string input_str;

	void line() {
		for (int i = 0; i < 30; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void help() {
		std::cout << "pinf = prints all Atoms in the system" << std::endl;
		std::cout << "inuc = insert a atom parameters: name, pos, charge" << std::endl;
		std::cout << "exit = exit the programm" << std::endl;
		std::cout << "sopt = simple optimisation" << std::endl;
		std::cout << "ab = add bond parameters: nuc1, nuc2, order" << std::endl;
		std::cout << "iH2O = add H2O to system" << std::endl;
		std::cout << "testrun = run test" << std::endl;
		line();
	}

	Array<std::string> split_input(std::string str) {
		Array<std::string> frag;
		std::string word;
		char w;
		//char space = (char)" ";
		for (int i = 0; i < str.length(); i++) {
			w = str[i];
			if ((int)w != 32) {
				word += w;
			}
			else {
				frag.add(word);
				word = "";
			}
		}
		frag.add(word);
		return frag;
	}

	void executable() {
		Array<std::string> frag = split_input(this->input_str);
		if (this->input_str == "pinf") {
			print_nuc();
		}
		else if (this->input_str == "help") {
			help();
		}
		else if (frag.get_element(0) == "inuc") {
			frag.delet(0);
			this->sys->add_nuc(frag.get_element(0), std::stod(frag.get_element(1)),std::stod(frag.get_element(2)), std::stod(frag.get_element(3)), std::stoi(frag.get_element(4)));
		}
		else if (this->input_str == "sopt") {
			this->sys->s_opt();
		}
		else if (frag.get_element(0) == "ab") {
			frag.delet(0);
			//std::cout << frag.get_element(0) << frag.get_element(1) << frag.get_element(2);
			this->sys->add_bond(std::stoi(frag.get_element(0)), std::stoi(frag.get_element(1)), std::stoi(frag.get_element(2)));
		}
		else if (this->input_str == "iH2O") {
			this->sys->H2O_test();
		}
		else if (this->input_str == "exit") {
			std::cout << "program exit";
		}
		else if (this->input_str == "testrun") {
			this->sys->test_run();
		}
		else {
			std::cout << "unbekannter befehl" << std::endl;
		}
	}

	System* get_sys() {
		return new System();
	}

	void dolphin() {
		std::cout << "              ## " << std::endl;
		std::cout << "         ##########" << std::endl;
		std::cout << "      ####      #######" << std::endl;
		std::cout << "     ###    ####    ### #" << std::endl;
		std::cout << "  ###     ##   #########" << std::endl;
	}

public:
	Handelprog() {
		this->sys = get_sys();
	}

	void input() {
		std::getline(std::cin, this->input_str);
	}

	void print_nuc() {
		std::cout << "All Atoms in the system : " << std::endl;
		int len = this->sys->get_nuc_ptr()->get_len();
		std::cout << "number of atoms : " << len << std::endl;
		for (int i = 0; i < len; i++) {
			std::string n = get_atom_name(this->sys->get_nuc(i)->get_number());
			std::cout << n;
			for (int j = n.length(); j < 2; j++) { std::cout << " "; }
			for (int j = 0; j < 3; j++) {
				std::cout << this->sys->get_nuc(i)->get_pos()->get_element(j) << " ";
			}
			std::cout << std::endl;
		}
		line();
	}

	void run() {
		std::cout << "            DOLPHIN" << std::endl;
		std::cout << std::endl;
		dolphin();
		std::cout << std::endl;
		line();
		std::cout << "enter input: " << std::endl;
		while (this->input_str != "exit") {
			input();
			executable();
		}
	}
};
