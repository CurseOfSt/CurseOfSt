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
	for (int i = 0; i < size; i++) {
		a[i] = rand() % 1000;
	}
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
		if ((Left_iter_a != run1_size) && (Right_iter_a != run2_size)){
			if ((left_s[Left_iter_a] <= right_s[Right_iter_a])) {
				a[i] = left_s[Left_iter_a];
				i++;
				Left_iter_a++;
				from_left_in_raw++;
				from_right_in_raw = 0;
				if (from_left_in_raw > edge_to_galop) {
					int galop_add = 1;
					while (left_s[Left_iter_a+galop_add] <= right_s[Right_iter_a] && (Left_iter_a + galop_add) < run1_size) {
						for (int k = Left_iter_a; k < (Left_iter_a+ galop_add); k++) {
							a[i] = left_s[k];
							i++;
						}
						Left_iter_a+= galop_add;
						galop_add +=1;
					}
					from_left_in_raw = 0;
				}
			}
			else {
				a[i] = right_s[Right_iter_a ];
				i++;
				Right_iter_a++;
				from_left_in_raw = 0;
				from_right_in_raw++;
				if (from_right_in_raw > edge_to_galop) {
					int galop_add = 1;
					while (left_s[Left_iter_a] > right_s[Right_iter_a+ galop_add] && (Right_iter_a + galop_add) < run2_size) {
						for (int k = Right_iter_a; k < Right_iter_a + galop_add; k++) {
							a[i] = right_s[k];
							i++;
						}
						Right_iter_a += galop_add;
						galop_add += 1;
					}
					from_right_in_raw = 0;
				}
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
		cout << "Run create" << endl;
		if (array[i] > array[i - 1]) {
			while (true) {
				if ((array[i] > array[i - 1]) && i < size) {
					run.size++;
					i++;
				}
				else {
					if (run.size < MinRun) {				//можно оптимизировать:если размер run близок к minrun,но начинается 
						while ((run.size <= MinRun) && i < size) {			// УБЫВ. последовательность,то мы запихнем ее в новый run
							run.size++;
							i++;
						}
						insertion_sort(array, run.start_index, run.size);
					}
					stack_runs.push(run);
					cout << "add run : " << "run.start_index " << run.start_index << " ; run.size " << run.size << " ; Stack.size "<< stack_runs.get_size()<<endl;
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
						while ((run.size <= MinRun) && i < size) {					// ВОЗРАСТ. последовательность,то мы запихнем ее в новый run
							run.size++;
							i++;
						}
						insertion_sort(array, run.start_index, run.size);
					}
					stack_runs.push(run);
					cout << "add run : " << "run.start_index " << run.start_index << " ; run.size " << run.size << " ; Stack.size " << stack_runs.get_size() << endl;
					run.start_index = i;
					run.size = 1;
					i++;
					break;
				}
			}
		}


		if (stack_runs.get_size() == 2) {
			X = stack_runs.pop();

			Y = stack_runs.pop();

			if (Y.size <= X.size   || Y.size >= X.size) {

				Merge_runs(array, Y.start_index, Y.size, X.size); // меньшие индексы будут у Y-run так как он первее попал в стек.
				X.start_index = (X.start_index < Y.start_index) ? X.start_index : Y.start_index;
				X.size += Y.size; //слили X c Y ,то есть минус один run
				stack_runs.push(X);
			}
		}
		if (stack_runs.get_size() >= 3) {
			X = stack_runs.pop();
			Y = stack_runs.pop();
			Z = stack_runs.pop();
			if (Z.size <= X.size + Y.size) {

				if (X.size > Z.size) {
					Merge_runs(array, Z.start_index, Z.size, Y.size);
					Y.start_index = (Y.start_index < Z.start_index) ? Y.start_index : Z.start_index;
					Y.size += Z.size;
					stack_runs.push(Y);
					stack_runs.push(X);
				}
				else {
					Merge_runs(array, Y.start_index, Y.size, X.size);
					X.start_index = (X.start_index < Y.start_index) ? X.start_index : Y.start_index;
					X.size += Y.size;
					stack_runs.push(Z);
					stack_runs.push(X);

				}
			}
		}
	}
}

int main() {
	srand(time(NULL));
	int size;
	cout << "Input the size  - > ";
	cin >> size;
    my_vector<int> array(size);
	fill_array(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
    cout << endl;
	TimSort(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
}

