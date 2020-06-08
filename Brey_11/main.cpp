#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <direct.h>

using namespace std;

int sum_col(double** data, int column)
{
	int sum = 0;
	for (int i = 0; i < 30; i++)
	{
		sum += data[i][column];
	}
	return sum;
}

int find_max_col_sum_index(double** data)
{
	double max_sum_col = -1;
	int max_sum_col_index = -1;

	for (int i = 0; i < 5; i++)
	{
		double sum = sum_col(data, i);
		if (sum > max_sum_col)
		{
			max_sum_col = sum;
			max_sum_col_index = i;
		}
	}

	return max_sum_col_index;
}

int find_min_col_sum_index(double** data)
{
	double min_sum_col = DBL_MAX;
	int min_sum_col_index = -1;

	for (int i = 0; i < 5; i++)
	{
		double sum = sum_col(data, i);
		if (sum < min_sum_col)
		{
			min_sum_col = sum;
			min_sum_col_index = i;
		}
	}

	return min_sum_col_index;
}

double*** read_file(string& directory)
{
	double*** datas = new double**[3];
	for (int i = 0; i < 3; i++)
	{
		datas[i] = new double*[30];
	}

	for (int i = 0; i < 30; i++)
	{
		ifstream f(directory + "d" + to_string(i + 1) + ".txt");
		f.peek();
		if (!f.good())
		{
			return nullptr;
		}
		datas[0][i] = new double[5];
		datas[1][i] = new double[5];
		datas[2][i] = new double[5];
		for (int j = 0; j < 5; j++)
		{
			f >> datas[0][i][j] >> datas[1][i][j];
			datas[2][i][j] = datas[0][i][j] * datas[1][i][j];
		}
		cout << "Считано " << i + 1 << "/30 файлов\n";
		f.close();
	}
	return datas;
}

string column_to_name(int column_index)
{
	switch (column_index)
	{
	case 0:
		return "Молоко";
	case 1:
		return "Сметана";
	case 2:
		return "Творог";
	case 3:
		return "Масло";
	case 4:
		return "Сыр";
	}
}

void gen_files(string& directory)
{
	_mkdir(directory.c_str());
	for (int i = 0; i < 30; i++)
	{
		ofstream f(directory + "d" + to_string(i + 1) + ".txt");
		for (int j = 0; j < 5; j++)
		{
			f << rand() % 1000 / 10. << " " << rand() % 15 << "\n";
		}
		cout << "Сгенерирован " << i + 1 << "/30 файлов\n";
		f.close();
	}
}

int main()
{
	setlocale(LC_ALL, "russian");

	cout << "Программу сделала Брей Валерия студент группы УМЛ-112\n";
	cout << "Программа для расчёта прибылей кота Матроскина\n";

	string path = "data/";

	if (false)
	{
		cout << "Запущен режим генерации файлов!\n";
		gen_files(path);
		cout << "Файлы сгенерированы!\n";
	}
	else
	{
		cout << "Запущен режим расчёта!\n";
		double*** datas = read_file(path);
		if (datas != nullptr)
		{
			double** prices = datas[0];
			double** counts = datas[1];
			double** totals = datas[2];

			int finest_average_price_index = find_max_col_sum_index(prices);
			double finest_average_price = sum_col(prices, finest_average_price_index) / 30.;
			int worst_average_price_index = find_min_col_sum_index(prices);
			double worst_average_price = sum_col(prices, worst_average_price_index) / 30.;

			cout << "Лучшая средняя цена на товар '" << column_to_name(finest_average_price_index) << "' в день: " <<
				finest_average_price << " р\n";
			cout << "Худшая средняя цена на товар '" << column_to_name(worst_average_price_index) << "' в день: " <<
				worst_average_price << " р\n";

			int finest_average_count_index = find_max_col_sum_index(counts);
			double finest_average_count = sum_col(counts, finest_average_count_index) / 30.;
			int worst_average_count_index = find_min_col_sum_index(counts);
			double worst_average_count = sum_col(counts, worst_average_count_index) / 30.;

			cout << "Лучший средний сбыт товара '" << column_to_name(finest_average_count_index) << "' в день: " <<
				finest_average_count << " шт\n";
			cout << "Худший средний сбыт товара '" << column_to_name(worst_average_count_index) << "' в день: " <<
				worst_average_count << " шт\n";

			int finest_average_total_index = find_max_col_sum_index(totals);
			double finest_average_total = sum_col(totals, finest_average_total_index) / 30.;
			int worst_average_total_index = find_min_col_sum_index(totals);
			double worst_average_total = sum_col(totals, worst_average_total_index) / 30.;

			cout << "Лучшая средняя выручка от товара '" << column_to_name(finest_average_total_index) << "' в день: "
				<<
				finest_average_total << " р\n";
			cout << "Худший средняя выручка от товара '" << column_to_name(worst_average_total_index) << "' в день: " <<
				worst_average_total << " р\n";
		}
		else
		{
			cout << "Произошла ошибка при чтении файлов!\nПожалуйста, запустите программу в режиме генерации!\n";
		}
	}

	system("pause");

	return 0;
}
