#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <thread>
#include <map>
#include <mutex>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::thread;
using std::map;

struct Players {
	string name;
	string surname;
	string patronimic;
	int age;
	int code;
};
void Dices(map<int, int>& map_CodeChips,vector<int>& dices_players, int size_dices_players);
void Roulette(map<int, int>& map_CodeChips, vector<int>& Roulette_players, int size_Roulette_players);
void Guess(map<int, int>& map_CodeChips, vector<int> &Guess_players, int size_Guess_players);

int main() {
	srand(time(NULL));
	map<int, int> map_CodeChips;
	int num_players;
	int num_real_players;
	cout << "Enter the number of potentional players : ";
	cin >> num_players;
	Players* player;     // указатель на поле структуры
	player = new Players[num_players];  // выделяем память на массив из структур
	cout << '\n';
	for (int i = 0; i < num_players; ++i) {
		cout << "Warring!!! You're not allowed to play if you under 18" << endl;
		cout << '\n';
		cout << "Player " << i + 1 << " enter your age : ";
		cin >> player[i].age;
		cout << '\n';
		if (player[i].age < 18) {
			cout << "  < O_o >  you've tried to decieve us , you're little twister" << endl;
			cout << '\n';
			player[i].code = 0;
			if (i < num_players) {
				continue;
			}
			
		}
		player[i].code = rand() % 99999;
		map_CodeChips[player[i].code] = 50;
		cout << "Player " << i + 1 << " enter your name : ";
		cin >> player[i].name;
		cout << '\n';
		cout << '\t' << "enter your surname : ";
		cin >> player[i].surname;
		cout << '\n';
		cout << '\t' << "enter your patronimic : ";
		cin >> player[i].patronimic;  // элемент структуры i-й яйчейки массива вводим с клавиатуры
		cout << '\n';
		cout << '\t' << '\t' << "Your code is : " << player[i].code <<" . Please remind it to track your chips" <<endl;
		cout << '\n';
	}
	int name_game;
	vector<int> codes_dices_players;
	vector<int> codes_Roulette_players;
	vector<int> codes_Guess_players;
	for (int k = 0; k < num_players; ++k) {
		if (player[k].code != 0) {
			cout << "Player " << player[k].code << " , print '1' , if you want to play 'Dices' , but You need two playersa at least to play 'Dices' " << endl;
			cout << '\t' << "   print '2' , if you want to play 'Roulette'" << endl;
			cout << '\t' << "   print '3' , if you want to play 'Guess the number'" << endl;
			cin >> name_game;
			if (name_game == 1&&(map_CodeChips[player[k].code]>=50)) {
				codes_dices_players.push_back(player[k].code);
			}
			if (name_game == 2 && (map_CodeChips[player[k].code] >= 50)) {
				codes_Roulette_players.push_back(player[k].code);
			}
			if (name_game == 3 && (map_CodeChips[player[k].code] >= 50)) {
				codes_Guess_players.push_back(player[k].code);
			}
		}
	}
	// нужно сделать функции,которые будут проверять количество фишек у игкроков
	// 
	// Для каждой игры нужно минимум 50 фишек (Мб кости сделать по 10 фишек за 1 бросок)
	// ??Возможность перехода из одной игры в другую
	// ??возможность запускать кости и угадай число несколько раз

	if (codes_dices_players.size() == 1) {
		cout << "Sorry! You need second paкtiсipant to play 'Dices'. You can't play Dices right now" << endl;
		cout << '\n';
	}
	if (codes_dices_players.size() >= 2) {
		Dices(map_CodeChips, codes_dices_players, codes_dices_players.size());
	}
	if (codes_Roulette_players.size() >=1) {
		thread th1(Roulette,std::ref(map_CodeChips), std::ref(codes_Roulette_players), codes_Roulette_players.size());	
		th1.join();
	}
	if (codes_Guess_players.size() >=1) {
		thread th2(Guess,std::ref(map_CodeChips), std::ref(codes_Guess_players), codes_Guess_players.size());
		th2.join();
	}
	for (auto it = map_CodeChips.begin(); it != map_CodeChips.end(); ++it) {
		if ((it->first)!=0) {
			cout << "Code " << it->first << " ; Chips " << it->second << endl;
		}
	}
	delete[] player;
}
// в функции на вход подавать контейнер map ,где ключ - код игрока,а значение - кол-во фишек игрока.
void Dices(map<int, int> &map_CodeChips,vector <int> &codes_dices_players,int size_codes_dices_players){
	cout << "Players ";
	for (int i = 0; i < size_codes_dices_players; ++i) {
		cout << codes_dices_players[i] << " ";
	}
	cout<<". Welcome to 'Dices' !" << endl;
	const int times = 5;
	int players = size_codes_dices_players;
	int** arr_games_sums = new int* [players] {};  //воспользуемся двойным динамическим массивом
	for (int i = 0; i < players; ++i) {
		arr_games_sums[i] = new int[times] {};
	}
	for (int i = 0; i < times; ++i) {
		cout << "DICES : Game (" << i + 1 << ") has begun " << endl;
		for (int k = 0; k < players; ++k) {
			cout << "Player " << codes_dices_players[k] << " press any button to dice. ";
			_getch();
			int value_1st_dice = rand() % 6 + 1;
			int value_2nd_dice = rand() % 6 + 1;
			int value_3d_dice = rand() % 6 + 1;
			cout << " You" << " got ( " << value_1st_dice << " ; " << value_2nd_dice << " ; " << value_3d_dice <<" )" << endl;
			int current_value = value_1st_dice+ value_2nd_dice+ value_3d_dice;
			arr_games_sums[k][i] += current_value;		
		}
		cout << '\n' << '\n';
	}
	int max_sum = 0;
	int number_player_max_sum = 0;
	for (int i = 0; i < players; ++i) {
		int curr_sum = 0;
		for (int j = 0; j < times; ++j) {
			curr_sum += arr_games_sums[i][j];
		}
		if (curr_sum > max_sum) {
			max_sum = curr_sum;
			number_player_max_sum = i;
		}
	}
	int code_player_max_sum = codes_dices_players[number_player_max_sum];
	map_CodeChips[code_player_max_sum] += 50 * (players-1);
	cout << " The lukiest man in 'Dices' is " << code_player_max_sum << " grats!!! " << endl;
	for (auto it = map_CodeChips.begin(); it != map_CodeChips.end(); ++it) {
		for (int m = 0; m < players; ++m) {
			if ((it->first) != code_player_max_sum) {
				if ((it->first) == codes_dices_players[m]) {
					(it->second) -= 50;
				}
			}
		}
	}
	for (int i = 0; i < players; ++i) {
		delete[]arr_games_sums[i];
	}
	delete[]arr_games_sums;
}
// коэффициенты для рулетки (выплата-ставка)  : число+цвет - 5 к 1  ; цвет - 2 к 1  ; четность - 2 к 1
void Roulette( map <int, int> &map_CodeChips, vector<int>& codes_Roulette_players, int size_codes_Roulette_players) {
	cout << "Players ";
	for (int i = 0; i < size_codes_Roulette_players; ++i) {
		cout << codes_Roulette_players[i] << " ";
	}
	cout << ". Welcome to 'Alternative Roulette' !" << endl;
	vector<int>mass_winners;
	srand(time(NULL));
	int type_bet;
	int color = rand() % 3;
	int number = rand() % 37 + 1;
	string parity[2] = { "even","odd" };
	string arr_colors[3] = { "green","black","red"};
	for (int i = 0; i < size_codes_Roulette_players; ++i) {
		string player_color = "*";
		int player_number=-1;
		string player_parity = "*";
		cout << "Player " << codes_Roulette_players[i] << ", too bet on COLOR enter '1' , to bet on NUMBER && COLOR enter '2' , to bet on EVEN || ODD enter '3' "<<endl;
		cin >> type_bet;
		if (type_bet == 1) {
			cout << " Make your bet (enter the color) ";
			cin >> player_color;
			cout << " Your bet is : '" << player_color <<"'"<< endl;
			if (player_color == arr_colors[color]) {
				map_CodeChips[codes_Roulette_players[i]] += 50 * 2;
				mass_winners.push_back(codes_Roulette_players[i]);
			}
			else {
				map_CodeChips[codes_Roulette_players[i]] -= 50;
			}
		}
		if (type_bet == 2) {
			cout << " Make your bet (Enter the number and color) " ;
			cin >> player_number;
			cin >> player_color;
			cout << " Your bet is : " << player_number << " '" << player_color << "'" << endl;
			if ((player_number == number)&&(player_color == arr_colors[color])){
				map_CodeChips[codes_Roulette_players[i]] += 50 * 5;
				mass_winners.push_back(codes_Roulette_players[i]);
			}
			else {
				map_CodeChips[codes_Roulette_players[i]] -= 50;
			}
		}
		if (type_bet == 3) {
			cout << " Make your bet (Enter 'odd' or 'even') " ;
			cin >> player_parity;
			cout << " Your bet is : '" << player_parity << "'"<<endl;
			cout << '\n';
			if ((player_parity.size()) % 2 == number % 2) {
				map_CodeChips[codes_Roulette_players[i]] += 50 * 2;
				mass_winners.push_back(codes_Roulette_players[i]);
			}
			else {
				map_CodeChips[codes_Roulette_players[i]] -= 50;
			}
		}
	}
	cout <<'\t'<<'\t' << "Results : "<<parity[number%2]<<" number - " << number << "; color - " << arr_colors[color] << endl;
	cout << '\n';
	int size_mass_winners = mass_winners.size();
	if (size_mass_winners > 0) {
		cout << " Grats to the lukiest ";
		for (int i = 0; i < size_mass_winners; ++i) {
			cout << mass_winners[i] << " ";
		}
		cout << "and don't worry who's less = ) ";
		cout << '\n';
		cout << '\n';
	}
	else {
		cout << "Come back next time, probably , you will be lackier";
	}
	cout << '\n';
	cout << '\n';
}
void Guess(map <int, int>& map_CodeChips, vector<int>& codes_Guess_players, int size_codes_Guess_players) {
	cout << "Players ";
	for (int i = 0; i < size_codes_Guess_players; ++i) {
		cout << codes_Guess_players[i] << " ";
	}
	cout << ". Welcome to 'Guess' !" << endl;
	vector<int>mass_winners;
	srand(time(NULL));
	int number = rand() % 11;
	for (int i = 0; i < size_codes_Guess_players; ++i) {
		int player_number = -1;
		cout << "Player " << codes_Guess_players[i] << " chose number from 0 to 10. ";
		cin >> player_number;
		cout << "Your bet is " << player_number << endl;
		if (player_number == number) {
			map_CodeChips[codes_Guess_players[i]] += 50;
			mass_winners.push_back(codes_Guess_players[i]);
		}
		else {
			map_CodeChips[codes_Guess_players[i]] -= 50;
		}
	}
	cout << '\t' << '\t' << "Result is : " << number << endl;
	int size_mass_winners = mass_winners.size();
	if (size_mass_winners > 0) {
		cout << " Ooo my God ! ";
		for (int i = 0; i < size_mass_winners; ++i) {
			cout << mass_winners[i] << " ";
		}
		cout << "gonna be ";
		if (size_mass_winners == 1) {
			cout << "a ";
		}
		cout << "wang";
		if (size_mass_winners > 1) {
			cout << "s!)" << endl;

		}
		else {
			cout << endl;
		}
		cout << '\n';
		cout << '\n';
	}
	else {
		cout << "Come back next time, probably , you will be lackier";
	}
	cout << '\n';
	cout << '\n';
}	