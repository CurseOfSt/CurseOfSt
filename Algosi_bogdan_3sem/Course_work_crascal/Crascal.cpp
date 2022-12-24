#include<iostream>
#include <fstream>
#include"vector_stack_list.h"
#include<string>
	

using std::string;
using std::cout;
using std::cin;
using std::endl;

struct rib {
	int start;
	int finish;
	int weight;
};
class graph {
	my_vector<rib> ribs;
	my_vector<rib> min_ost;
	my_vector<string> vertexes;
	my_vector<int>podmnozestva;
	my_vector<int> color;

	void make_set(int element) {
		podmnozestva.push_back(element);
		color[element] = 0;
	}
	int find_set(int element) {
		if (element == podmnozestva[element]) {
			return element;
		}
		else {
			podmnozestva[element] = find_set(podmnozestva[element]);
			return podmnozestva[element];
		}
	}
	void unioN(int el_1, int el_2) {
		el_1 = find_set(el_1);
		el_2 = find_set(el_2);
		if (el_1 == el_2) return;
		if (color[el_1] < color[el_2]) {
			podmnozestva[el_1] = el_2;
		}
		else {
			podmnozestva[el_2] = el_1;
			if (color[el_1] == color[el_2])
				color[el_1]++;
		}
	}
	void sort_vert() {
		rib tmp;
		int j;
		for (int i = 1; i < ribs.get_size(); i++) {
			tmp = ribs[i];
			j = i - 1;
			while (j >= 0 && ribs[j].weight > tmp.weight) {
				ribs[j + 1] = ribs[j];
				j -= 1;
			}
			ribs[j + 1] = tmp;
		}
	}
	void deep_search(int vert,my_vector<bool>&was) {
		if (vert == 0) {
			for (int i = 0; i < vertexes.get_size(); i++) {
				was[i] = 0;
			}
		}
		was[vert] = 1;
		cout << vertexes[vert] << endl;
		for (int i = 0; i < ribs.get_size(); i++) {
			if (ribs[i].start == vert && was[ribs[i].finish] == 0) {
				deep_search(ribs[i].finish, was);
			}
			if (ribs[i].finish == vert && was[ribs[i].start] == 0) {
				deep_search(ribs[i].start, was);
			}
		}
	}

public:

	void read_() {
		setlocale(LC_ALL, "ru");
		std::ifstream fin;
		fin.open("Weird.txt");
		//if (fin.is_open()) cout<<"rwrw";
		string str="";
		string tmp = "";
		getline(fin, str); //Считываем вершины
		for (int i = 0; i < str.size(); i++) {
			tmp.append(str, i, (str.find_first_of(" ", i) - i)); // добавляем в строку tmp cимволы из str начиная с i-й позиции в количестве (индекс первого вхождения минус i) 
			vertexes.push_back(tmp);
			tmp = "";
			i = str.find_first_of(" \n", i); // новые элементы будем искать с момента,когда в строке str встретится Пробел или Перенос строки
			if (i == -1) break;
		}
		rib r;
		for (int i = 0; i < vertexes.get_size() - 1; i++) {

			getline(fin, str);
			int finish = 0;

			for (int j = 0; j < str.size(); j++) {
				tmp = "";
				tmp.append(str, j, (str.find_first_of(" ", j) - j));
				j = str.find_first_of(" ", j);

				if (j == -1 && tmp != "0") {
					r.start = i;
					r.finish = finish;
					finish++;
					r.weight = stoi(tmp);// переводим string в int
					ribs.push_back(r);
					break;
				}
				else {
					if (j == -1 && tmp == "0") break;
				}
				if (tmp == "0" || finish <= i) {  // так как матрица симм. то можно искать эл-ты до верхней диагонали(на ней нули), след-но эл-ты этой строки до главной диагонали мы рассмотрели,ищем дальше
					finish++;
					continue; // продолжаем поиск ребер
				}
				r.start = i;
				r.finish = finish;
				finish++;
				r.weight = stoi(tmp);
				ribs.push_back(r);
			}
		}
		fin.close();
	}
	void print() {
		for (int i = 0; i < vertexes.get_size(); i++) {
			cout << vertexes[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < vertexes.get_size(); i++) {
			for (int j = 0; j < vertexes.get_size(); j++) {
				if (i == j) cout << 0 << " ";
				else {
					for (int k = 0; k < ribs.get_size(); k++) {
						if (ribs[k].start == i && ribs[k].finish == j || ribs[k].start == j && ribs[k].finish == i) { 
							cout << ribs[k].weight << " ";
							break;
						}
						else if (k == ribs.get_size() - 1) {
							cout << 0 << " ";
						}
					}
				}
			}
			cout << endl;
		}
	}
	void krask_alg() {
		int rib_1;
		int rib_2;
		sort_vert();
		for (int i = 0; i < vertexes.get_size(); i++) {
			make_set(i);
		}
		for (int i = 0; min_ost.get_size() < vertexes.get_size() - 1; i++)
		{
			rib_1 = find_set(ribs[i].start);
			rib_2 = find_set(ribs[i].finish);
			if (rib_1 != rib_2)
			{
				min_ost.push_back(ribs[i]);
				unioN(rib_1, rib_2);
			}
		}
		int weight=0;
		for (int i = 0; i < min_ost.get_size(); i++) {
			cout << vertexes[min_ost[i].start] << " <---> " << vertexes[min_ost[i].finish] << endl;
			weight += min_ost[i].weight;
		}
		cout << weight << endl;
	}
	void BFS() {
		my_vector<int>queue;
		my_vector<bool>was(vertexes.get_size());
		for (int i = 0; i < vertexes.get_size(); i++) {
			was[i] = 0;
		}
		int vert = 0;
		queue.push_back(0);
		while (queue.get_size() != 0) {
			vert = queue.pop_back();
			for (int i = 0; i < ribs.get_size(); i++) {
				if (ribs[i].start == vert && was[ribs[i].finish] == 0) {
					queue.push_back(ribs[i].finish);
					was[ribs[i].finish] = 1;
				}
				else if (ribs[i].finish == vert && was[ribs[i].start] == 0) {
					queue.push_back(ribs[i].start);
					was[ribs[i].start] = 1;
				}
			}
			cout << vertexes[vert] << endl;
		}
	}
	void dfs() {
		my_vector<bool>was;
		deep_search(0, was);
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	graph test;
	cout << "graph from file " << endl;
	cout << endl;
	test.read_();
	test.print();
	cout << endl;
	cout << "Krascal algorithm" << endl;
	cout << endl;
	test.krask_alg();
	cout << endl;
	cout << "Breadt fisrt search" << endl;
	cout << endl;
	test.BFS();
	cout << endl;
	cout << "Deep search" << endl;
	cout << endl;
	test.dfs();
	cout << endl;

	/*my_vector<int> test;
	test.resize(2);
	test.push_back(12);
	test.push_back(2423);
	test.push_back(2423);
	test.push_back(2423);
	test.erase(0);
	int a=test.pop_back();
	cout << test.pop_back();
	cout << test.pop_back();
	cout << a;*/
	
}