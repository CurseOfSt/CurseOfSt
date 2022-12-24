#include<iostream>
#include "Vector_Stack.h"
#include<time.h>

using std::cin;
using std::cout;
using std::endl;

class Run {
public:
	int size;
	int start_index;
}; 
int get_MinRun(int array_size) {
	int add = 0;
	while (array_size >= 64) {
		add = add | (array_size & 1);
		array_size = array_size >> 1;
	}
	return (array_size + add);
}

void fill_array(my_vector<int>& a, int size) {
	//for (int i = 0; i < (size / 2) + 1; i++) {
	//	a[i] = size - i;//= rand() % 1000;
	//}
	//for (int i = size-1; i> (size / 2); i--) {
	//	a[i] = i + size;//= rand() % 1000;
	//}
	for (int i = 0; i < size ; i++) {
		a[i] = rand() % 1000;

	}
	/*for (int i = size-1; i > size / 3 ; i--) {
		a[i] = i;

	}
	for (int i = size - 1; i > size / 3; i--) {
		a[i] = i;

	}*/
}

void reverse(my_vector<int>& a, int start_point, int run_size) {
	int finish = start_point + run_size;
	int temp;
	for (int i= 0; i <(run_size/2) ; i++) {
		temp =a[i+ start_point];
		a[i + start_point] = a[finish - i-1];
		a[finish -i-1] = temp;
	}
}

void insertion_sort(my_vector<int>& a, int start_point, int run_size) {
	int finish_point = start_point + run_size;
	for (int i = start_point ; i < finish_point; i++) {
		int current = a[i];
		int check_ind = i - 1;
		while ((check_ind >= start_point) && (a[check_ind] > current)) {
			a[check_ind+1] = a[check_ind];
			check_ind --;
		}
		a[check_ind+1] = current;
	}
}

int binary_search(my_vector<int>&min_mass,int pos_min, my_vector<int>&max_mass,int pos_max) {
	int key = max_mass[pos_max];
	int low = pos_min;
	int high = min_mass.get_size() /*- pos_min*/ - 1; //верхняя граница индекса (условно присоединяем элемент max_mass[pos_max] к min_mass
	if (min_mass[min_mass.get_size() - 1] <= key) {
		return min_mass.get_size() /*- pos_min-1*/;
	}
	while (low <= high) {
		int mid = (high + low) / 2 + 1;
		if (min_mass[mid] < key) {
			low = mid + 1;
		}
		else if (min_mass[mid] > key) {
			high = mid - 1;
		}
		else if(min_mass[mid] == key) return mid;
	}
}

void Merge_runs(my_vector<int>&a,int run1_start,int run1_size,int run2_size) {

	int left_ptr = run1_start ;
	int right_ptr = run1_start + run1_size;
	int from_right_in_raw = 0;
	int from_left_in_raw = 0;
	const int edge_to_galop = 7;
	my_vector<int>left_s(run1_size);
	my_vector<int>right_s(run2_size);

	for (int k = 0; k < run1_size; k++) {
		left_s[k] = a[left_ptr + k];
	}
	for (int k = 0; k < run2_size; k++) {
		right_s[k] = a[right_ptr + k];
	}

	int Left_iter_a = 0;
	int Right_iter_a = 0;
	int i = left_ptr;

	while (Left_iter_a + Right_iter_a < run1_size + run2_size) {
		/*cout << "1";*/
		if ((Left_iter_a != run1_size) && (Right_iter_a != run2_size)) {
			if ((left_s[Left_iter_a] <= right_s[Right_iter_a])) {
				a[i] = left_s[Left_iter_a];
				i++;
				Left_iter_a++;
				from_left_in_raw++;
				from_right_in_raw = 0;
				if (from_left_in_raw == edge_to_galop) {
					//случай,когда мы перепрыгиваем весь массив
					if (left_s[run1_size - 1] <= right_s[Right_iter_a]) {
						for (int j = Left_iter_a; j < run1_size; j++) {
							a[i] = left_s[j];
							i++;
							Left_iter_a++;
						}
					}
					else {
						bool flag = false;
						int l_itr = Left_iter_a; // левая граница этого run
						int r_itr = run1_size - 1; // правая граница этого run
						int mid;
						while ((l_itr <= r_itr) && (flag != true)) {
							
							mid = (l_itr + r_itr) / 2; // считываем срединный индекс отрезка [l,r]

							if (left_s[mid] <= right_s[Right_iter_a] && left_s[mid + 1] > right_s[Right_iter_a]) {
								flag = true; //проверяем ключ со серединным элементом
							}
							if (left_s[mid] > right_s[Right_iter_a]) {
								r_itr = mid - 1; // середина больше - сдинуть влево
							}
							else {
								l_itr = mid + 1; // cередина меньше - сдвинуть вправо 
							}
						}
						for (int j = Left_iter_a; j <= mid; j++) {
							a[i] = left_s[j];
							i++;
							Left_iter_a++;
						}
					}
					from_left_in_raw = 0;
				}
			}
			else {
				a[i] = right_s[Right_iter_a];
				i++;
				Right_iter_a++;
				from_left_in_raw = 0;
				from_right_in_raw++;
				if (from_right_in_raw == edge_to_galop) {
					//случай,когда мы перепрыгиваем весь массив
					if (right_s[run2_size - 1] <= left_s[Left_iter_a]) {
						for (int j = Right_iter_a; j < run2_size; j++) {
							a[i] = right_s[j];
							i++;
							Right_iter_a++;
						}
					}
					else {
						bool flag = false;
						int l_itr = Right_iter_a; // левая граница этого run
						int r_itr =run2_size - 1; // правая граница этого run
						int mid;
						while ((l_itr <= r_itr) && (flag != true)) {
							
							mid = (l_itr + r_itr) / 2; // считываем срединный индекс отрезка [l,r]

							if (right_s[mid] <= left_s[Left_iter_a] && right_s[mid + 1] > left_s[Left_iter_a]) { 
								flag = true; // мидл должен быть крайним,который меньше либо равен
								
							}
							if (right_s[mid] > left_s[Left_iter_a]) {
								r_itr = mid - 1; // проверяем, какую часть нужно отбросить
							}
							else { 
								l_itr = mid + 1; 
								
							}
						}
						for (int j = Right_iter_a; j <= mid; j++) {
							a[i] = right_s[j];
							i++;
							Right_iter_a++;
						}
					}
					from_right_in_raw = 0;
				}
			}
			if (Left_iter_a == run1_size) {
				while (Right_iter_a < run2_size) {
					a[i] = right_s[Right_iter_a];
					i++;
					Right_iter_a++;
				}
			}
			if (Right_iter_a == run2_size) {
				while (Left_iter_a < run1_size) {
					a[i] = left_s[Left_iter_a];
					i++;
					Left_iter_a++;
				}
			}
		}
	}
}


void TimSort(my_vector<int>& array, int size) {
	Run run;
	run.size = 1; 
	run.start_index = 0;
	stack<Run> stack_runs;
	Run X;
	X.size = 0;
	Run Y;
	Y.size = 0;
	Run Z;
	Z.size = 0;
	int MinRun = get_MinRun(size);
	for (int i = 1; i < size;) {
		if (array[i] > array[i - 1]) {
			while (true) {
				if ((array[i] > array[i - 1]) && i < size) {
					run.size++;
					i++;
				}
				else {
					if (run.size <= MinRun) {				//можно оптимизировать:если размер run близок к minrun,но начинается 
						while ((run.size < MinRun) && i < size) {			// УБЫВ. последовательность,то мы запихнем ее в новый run
							run.size++;
							i++;
						}
						insertion_sort(array, run.start_index, run.size);
					}
					stack_runs.push(run);
					//cout << "add run : " << "run.start_index " << run.start_index << " ; run.size " << run.size << " ; Stack.size " << stack_runs.get_size() << endl;
					run.start_index = i;
					run.size = 1;
					i++;
					break;
				}
			}
		}
		else {
			while (true) {
				if ((array[i] < array[i - 1]) && i < size) {
					run.size++;
					i++;
				}
				else {
					reverse(array, run.start_index, run.size);
					if (run.size < MinRun) {						//можно оптимизировать:если размер run близок к minrun,но начинается 
						while ((run.size < MinRun) && i < size) {					// ВОЗРАСТ. последовательность,то мы запихнем ее в новый run
							run.size++;
							i++;
						}
						insertion_sort(array, run.start_index, run.size);
					}
					stack_runs.push(run);
					//cout << "add run : " << "run.start_index " << run.start_index << " ; run.size " << run.size << " ; Stack.size " << stack_runs.get_size() << endl;
					run.start_index = i;
					run.size = 1;
					i++;
					break;
				}
			}
		}
		if (stack_runs.get_size() >= 2) {
			X = stack_runs.pop();
			Y = stack_runs.pop();
			if (!stack_runs.is_empty()) {
				Z = stack_runs.peak();
			}
			stack_runs.push(Y);
			stack_runs.push(X);
		}
		while ((stack_runs.get_size() >= 2) && ((Y.size <= X.size) || (stack_runs.get_size() >= 3) && (Z.size <= Y.size + X.size))) {
			//cout << "problem 4 " << endl;
			while ((stack_runs.get_size() >= 2) && (Y.size <= X.size)) {
				//cout << "problem 5 " << endl;
				Merge_runs(array, Y.start_index, Y.size, X.size); // меньшие индексы будут у Y-run так как он первее попал в стек.
				Y.start_index = (Y.start_index < X.start_index) ? Y.start_index : X.start_index;
				Y.size += X.size; //слили X c Y ,то есть минус один run(X)
				X.size = 0;
				stack_runs.pop();
				stack_runs.pop();
				stack_runs.push(Y);
				if (stack_runs.get_size() >= 2) {
					X = stack_runs.pop();
					Y = stack_runs.pop();
					if (!stack_runs.is_empty()) {
						Z = stack_runs.peak();
					}
					stack_runs.push(Y);
					stack_runs.push(X);
				}
			}
			while ((stack_runs.get_size() >= 3) && (Z.size <= Y.size + X.size)) {
				X = stack_runs.pop();
				Y = stack_runs.pop();
				Z = stack_runs.pop();
				//cout << "problem 6 " << endl;
				if (X.size > Z.size) {
					Merge_runs(array, Z.start_index, Z.size, Y.size);
					Z.start_index = (Z.start_index < Y.start_index) ? Z.start_index : Y.start_index;
					Z.size += Y.size; //слили Y c Z ,то есть минус один run(Y)
					Y.size = 0;
					stack_runs.push(Z);
					stack_runs.push(X);

				}
				else {
					Merge_runs(array, Y.start_index, Y.size, X.size);
					X.start_index = (X.start_index < Y.start_index) ? X.start_index : Y.start_index;
					X.size += Y.size; //слили Y c X ,то есть минус один run(Y)
					Y.size = 0;
					stack_runs.push(Z);
					stack_runs.push(X);
				}
				if (stack_runs.get_size() >= 2) {
					X = stack_runs.pop();
					Y = stack_runs.pop();
					if (!stack_runs.is_empty()) {
						Z = stack_runs.peak();
					}
					stack_runs.push(Y);
					stack_runs.push(X);
				}
			}
		}
	}
	while (stack_runs.get_size() > 1) {
		X = stack_runs.pop();
		Y = stack_runs.pop();
		Merge_runs(array, Y.start_index, Y.size, X.size);
		Y.start_index = (Y.start_index < X.size) ? Y.start_index : X.start_index;
		Y.size += X.size;
		stack_runs.push(Y);
	}
}

int main() {
	srand(time(NULL));
	int size;
	cout << "Input the size  - > ";
	cin>> size;
    my_vector<int> array(size);
	fill_array(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << endl;
	TimSort(array, size);
	/*my_vector<int> array(10000);
	for (int i = 0; i < 200; i++) {
		fill_array(array, 10000);
		TimSort(array, 10000);
	}*/
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
}


