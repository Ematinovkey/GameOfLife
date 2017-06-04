#pragma once
#include <iostream>
#include <windows.h>

using namespace  std;

class World
{
	bool current_[40][40];
	bool next_[40][40];

	int count_alive_neighbours(int st_ind, int col_ind)
	{
		int count = 0;
		for (int i = st_ind - 1; i <= st_ind + 1; i++)
			for (int j = col_ind - 1; j <= col_ind + 1; j++)
				if (i >= 0 && j >= 0 && i < 40 && j < 40 && !(i == st_ind && j == col_ind))
					if (current_[i][j])
						count++;
		return count;
	}


public:
	World()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
			{
				current_[i][j] = false;
				next_[i][j] = false;
			}
	}

	void reset()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
			{
				current_[i][j] = false;
				next_[i][j] = false;
			}
	}
	//Pre-loaded structures
	void penta()
	{
		reset();
		current_[19][21] = true;
		current_[19][26] = true;
		current_[21][21] = true;
		current_[21][26] = true;
		current_[20][19] = true;
		current_[20][20] = true;
		current_[20][22] = true;
		current_[20][23] = true;
		current_[20][24] = true;
		current_[20][25] = true;
		current_[20][27] = true;
		current_[20][28] = true;
	}
	void blinker()
	{
		reset();
		current_[20][21] = true;
		current_[20][22] = true;
		current_[20][23] = true;
	}
	void beacon()
	{
		reset();
		current_[20][20] = true;
		current_[20][21] = true;
		current_[21][20] = true;
		current_[21][21] = true;
		current_[22][22] = true;
		current_[22][23] = true;
		current_[23][22] = true;
		current_[23][23] = true;
	}
	void dieHard()
	{
		reset();
		current_[18][11] = true;
		current_[18][12] = true;
		current_[19][12] = true;
		current_[19][16] = true;
		current_[19][17] = true;
		current_[19][18] = true;
		current_[17][17] = true;
	}
	void rPentomino()
	{
		reset();
		current_[19][20] = true;
		current_[20][21] = true;
		current_[20][20] = true;
		current_[20][19] = true;
		current_[21][19] = true;
	}
void gliderGun()
	{
	reset();
	current_[24][2] = true;
	current_[25][2] = true;
	current_[24][3] = true;
	current_[25][3] = true;
	current_[24][12] = true;
	current_[25][12] = true;
	current_[26][12] = true;
	current_[27][13] = true;
	current_[23][13] = true;
	current_[22][14] = true;
	current_[22][15] = true;
	current_[28][14] = true;
	current_[28][15] = true;
	current_[25][16] = true;
	current_[25][18] = true;
	current_[25][19] = true;
	current_[24][18] = true;
	current_[26][18] = true;
	current_[23][17] = true;
	current_[27][17] = true;
	current_[24][22] = true;
	current_[24][23] = true;
	current_[23][22] = true;
	current_[23][23] = true;
	current_[22][22] = true;
	current_[22][23] = true;
	current_[21][24] = true; 
	current_[25][24] = true;
	current_[25][26] = true;
	current_[26][26] = true;
	current_[21][26] = true;
	current_[20][26] = true;
	current_[22][36] = true;
	current_[23][36] = true;
	current_[22][37] = true;
	current_[23][37] = true;

	}
	void create_new_gen()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
			{
				int alive_n = count_alive_neighbours(i, j);
				if (current_[i][j])
				{
					if (alive_n != 2 && alive_n != 3)
						next_[i][j] = false;
					else
						next_[i][j] = current_[i][j];
				}
				else
					if (alive_n == 3)
						next_[i][j] = true;
			}
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
			{
				current_[i][j] = next_[i][j];
			}
	}
	void set_cell_state1(int st_ind, int col_ind)
	{
		current_[st_ind][col_ind] = true;
	}

	void set_cell_state0(int st_ind, int col_ind)
	{
		current_[st_ind][col_ind] = false;
	}

	int get_cell_state(int st_ind, int col_ind)
	{
		return current_[st_ind][col_ind];
	}


	bool check_life()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
				if (current_[i][j])
					return true;
		return false;

	}

	bool check_equality()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
				if (current_[i][j] != next_[i][j])
					return false;
		return true;
	}

};


int main()
{
	World a;
	do
	{
		system("cls");
		a.create_new_gen();
		Sleep(700);
	} while (1 < 100);
}
