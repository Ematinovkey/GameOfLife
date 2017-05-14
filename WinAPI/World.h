#pragma once
#include <iostream>
#include <windows.h>

using namespace  std;

class World
{
	bool current_[40][40];
	bool previous_[40][40];
	bool next_[40][40];

	bool check_equality()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
				if (current_[i][j] != previous_[i][j])
					return false;
		return true;
	}

	void save_previous()
	{
		for (int i = 0; i < 40; i++)
			for (int j = 0; j < 40; j++)
				previous_[i][j] = current_[i][j];
	}

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
	void penta()
	{
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
