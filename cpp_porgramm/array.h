#pragma once
#include <iostream>
#include <cmath>
#include <typeinfo>

template<typename T>
class Array {
protected:
	T* values;
	int len;
	int i;

	bool chek_if_full() {
		if (this->len == this->i) {
			return true;
		}
		else {
			return false;
		}
	}

	T* create_new_array() {
		return new T[len * 2];
	}

	void handel_array() {
		T* new_list = create_new_array();
		for (int i = 0; i < this->i; i++) {
			new_list[i] = this->values[i];
		}
		delete[] this->values;
		this->values = new_list;
		this->len *= 2;
	}

public:
	Array() {
		this->values = new T[10];
		this->len = 10;
		this->i = 0;
	}

	void add(T value) {
		this->values[this->i] = value;
		this->i += 1;
		if (chek_if_full()) {
			handel_array();
		}
	}

	void pop() {
		this->i -= 1;
	}

	int get_index(T element) {
		int index = -1; 
		for (int i = 0; i < this->i; i++) {
			if (this->values[i] = element) {
				index = i; 
			}
		}
		return index;
	}

	void remove(T element) {
		int pos = get_index(element);
		if (pos == -1) { throw("error the element is not in the list"); }
		for (int i = pos; i < this->i; i++) {
			this->values[i] = this->values[i + 1];
		}
		this->i -= 1;
	}

	void insert(int i, T element) {
		this->values[i] = element;
	}

	int get_len() {
		return this->i;
	}

	T get_element(int i) {
		if (i <= this->i && i >= 0) {
			return this->values[i];
		}
		else {
			throw "error index out of range";
		}
	}

	void reset() {
		for (int i = 0; i < this->i; i++) {
			//delete[] this->values[i];
		}
		//delete[] this->values;
		this->i = 0;
		//Array();
	}

	void delet_self() {
		if (std::is_pointer<T>::value) {
			for (int i = 0; i < this->i; i++) {
				//delete[] this->values[i];
			}
		}
		else {
			for (int i = 0; i < this->i; i++) {
				//delete this->values[i];
			}
		}
		//delete[] this->values;
		//delete this;
	}

	void delet(int pos) {
		for (int i = pos; i < this->i; i++) {
			this->values[i] = this->values[i + 1];
		}
		this->i -= 1;
	}

	double max() {
		double max = 0;
		for (int i = 0; i < this->i; i++) {
			if (max > this->values[i]) {
				max = this->values[i];
			}
		}
		return max;
	}
};

class Vector : public Array<double> {
public:
	Vector() {
		this->values = new double[3];
		this->len = 3;
		this->i = 3; 
	}

	void set_vec(double x, double y, double z) {
		this->values[0] = x;
		this->values[1] = y;
		this->values[2] = z;
	}

	void sub_vec(Vector* vec) {
		for (int i = 0; i < 3; i++) {
			this->values[i] -= vec->get_element(i);
		}
	}

	void add_vec(Vector* vec) {
		for (int i = 0; i < 3; i++) {
			this->values[i] += vec->get_element(i);
		}
	}

	Vector* get_sub_vec(Vector* vec) {
		Vector* new_vec = new Vector();
		new_vec->set_vec(this->values[0] - vec->get_element(0), this->values[1] - vec->get_element(1), this->values[2] - vec->get_element(2));
		return new_vec;
	}

	double get_sub_vec_len(Vector* vec) {
		double new_vec[3] = { 0.0,0.0,0.0 };
		for (int i = 0; i < 3; i++) {
			//std::cout << "c " << this->values[i] << " + " << vec->get_element(i) << std::endl;
			new_vec[i] = this->values[i] - vec->get_element(i);
		}
		
		//std::cout << "vel " << std::sqrt(std::pow(new_vec[0], 2) + std::pow(new_vec[1], 2) + std::pow(new_vec[2], 2)) << std::endl;
		return std::sqrt(std::pow(new_vec[0],2) + std::pow(new_vec[1],2) + std::pow(new_vec[2],2));
	}

	double get_length() {
		return std::sqrt(std::abs(std::pow(this->values[0],2) + std::pow(this->values[1],2) + std::pow(this->values[2],2)));
	}

	double get_dot(Vector* vec) {
		return this->values[0] * vec->get_element(0) + this->values[1] * vec->get_element(1) + this->values[2] * vec->get_element(2);
	}

	double get_angle(Vector* vec) {
		return std::acos(get_dot(vec) / (get_length() * vec->get_length()));
	}

	void mult_vec_fac(double factor) {
		this->values[0] *= factor;
		this->values[1] *= factor;
		this->values[2] *= factor;
	}

	void normalize() {
		mult_vec_fac(1 / get_length());
	}
};

class Vector2D : public Array<double> {
public:
	Vector2D() {
		this->values = new double[2];
		this->len = 2;
		this->i = 2;
	}

	void set_vec(double x, double y) {
		this->values[0] = x;
		this->values[1] = y;
	}

	void sub_vec(Vector2D* vec) {
		for (int i = 0; i < 2; i++) {
			this->values[i] -= vec->get_element(i);
		}
	}

	void add_vec(Vector2D* vec) {
		for (int i = 0; i < 2; i++) {
			this->values[i] += vec->get_element(i);
		}
	}

	Vector2D* get_sub_vec(Vector2D* vec) {
		Vector2D* new_vec = new Vector2D();
		new_vec->set_vec(this->values[0] - vec->get_element(0), this->values[1] - vec->get_element(1));
		return new_vec;
	}

	double get_sub_vec_len(Vector2D* vec) {
		double new_vec[2] = { 0.0,0.0};
		for (int i = 0; i < 2; i++) {
			//std::cout << "c " << this->values[i] << " + " << vec->get_element(i) << std::endl;
			new_vec[i] = this->values[i] - vec->get_element(i);
		}

		//std::cout << "vel " << std::sqrt(std::pow(new_vec[0], 2) + std::pow(new_vec[1], 2) + std::pow(new_vec[2], 2)) << std::endl;
		return std::sqrt(std::pow(new_vec[0], 2) + std::pow(new_vec[1], 2));
	}

	double get_length() {
		return std::sqrt(std::abs(std::pow(this->values[0], 2) + std::pow(this->values[1], 2)));
	}

	double get_dot(Vector2D* vec) {
		return this->values[0] * vec->get_element(0) + this->values[1] * vec->get_element(1);
	}

	double get_angle(Vector2D* vec) {
		return std::acos(get_dot(vec) / (get_length() * vec->get_length()));
	}

	void mult_vec_fac(double factor) {
		this->values[0] *= factor;
		this->values[1] *= factor;
	}

	void normalize() {
		mult_vec_fac(1 / get_length());
	}

	~Vector2D() {
		delete[] this->values;
	}
};

class Matrix {
private:
	Array<Array<double>*>* m;
	int x;
	int y;

public:
	Matrix(int x, int y) {
		this->x = x;
		this->y = y;
		this->m = new Array<Array<double>*>;

		for (int i = 0; i < x; i++) {
			this->m->add(new Array<double>);
			for (int j = 0; j < y; j++) {
				this->m->get_element(i)->add(0);
			}
		}
	}

	void insert_element(int x, int y, double value) {
		this->m->get_element(x)->insert(y, value);
	}

	void print() {
		for (int i = 0; i < this->x; i++) {
			std::cout << std::endl;
			for (int j = 0; j < this->y; j++) {
				std::cout << this->m->get_element(i)->get_element(j) << " ";
			}
		}
		std::cout << std::endl;
	}
};
