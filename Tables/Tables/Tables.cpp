#include <iostream>
#include "Tables.h"
#include <string.h>


int main()
{
	setlocale(LC_ALL, "ru");
	std::string s = "yes";

	UnorderTable<Polinom<double>> un_table;

	OrderTable<Polinom<double>> or_table;

	int Size = 100;
	HashTable<Polinom<double>> hash_table(Size);

	try {
		

		while (s == "yes")
		{
			std::cout << "Выберите действие:" << std::endl;
			std::cout << "\t 1 - Записать полином в таблицы" << std::endl;
			std::cout << "\t 2 - Извлечь полином из таблиц" << std::endl;
			std::cout << "\t 3 - Найти сумму полиномов" << std::endl;
			std::cout << "\t 4 - Найти разность полиномов" << std::endl;
			std::cout << "\t 5 - Найти произведение полиномов" << std::endl;
			std::cout << "\t 6 - Показать таблицы" << std::endl;

			int pkey = 0;

			std::cin >> pkey;

			switch (pkey)
			{
			case 1:
			{
				Polinom<double> pol1;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;


				double coef = -1;
				int degree = 0;

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					if (coef != 0)
					{
						pol1.push_back(coef, degree);
					}

				} while (coef != 0);


				std::cin.clear();
				while (std::cin.get() != '\n');

				int key = 0;
				do
				{
					std::cout << "Введите ключ" << std::endl;
					std::cin >> key;
				} while (un_table.GetSize() && un_table.key_is_busy(key));

				push(pol1, key, un_table);


				push(pol1, key, or_table);


				push_polinom_ht(pol1, key, hash_table);
				break;
			}
			case 2:
			{
				std::cout << "Введите ключ" << std::endl;
				int key = 0;
				std::cin >> key;

				un_table.remove_by_key(key);
				
				or_table.remove_by_key(key);

 				remove_by_key(key, hash_table);

				break;
			}
			case 3:
			{

				Polinom<double> pol1, pol2;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;


				double coef = -1;
				int degree = 0;

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol1.push_back(coef, degree);
				} while (coef != 0);

				coef = -1;
				degree = 0;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;

				std::cin.clear();
				while (std::cin.get() != '\n');

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol2.push_back(coef, degree);
				} while (coef != 0);

				Polinom<double> result;

				CompressionPolinom(pol1);
				RemoveZeros(pol1);
				CompressionPolinom(pol2);
				RemoveZeros(pol2);

				MergePolinoms(pol1, pol2, result);
				result.Show();

				std::cout << std::endl;
				std::cout << "Сохранить результат в таблицу?\t(yes\\no)" << std::endl;
				std::string v = "yes";
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cin >> v;

				if (v == "yes")
				{
					std::cout << "Введите ключ" << std::endl;
					int key = 0;
					std::cin >> key;


					push(result, key, un_table);

					push(result, key, or_table);

					push_polinom_ht(result, key, hash_table);
				}
				break;

			}
			case 4:
			{
				Polinom<double> pol1, pol2;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;


				double coef = -1;
				int degree = 0;

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol1.push_back(coef, degree);
				} while (coef != 0);

				coef = -1;
				degree = 0;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;

				std::cin.clear();
				while (std::cin.get() != '\n');

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol2.push_back(coef, degree);
				} while (coef != 0);

				Polinom<double> result;

				CompressionPolinom(pol1);
				RemoveZeros(pol1);
				CompressionPolinom(pol2);
				RemoveZeros(pol2);

				SubtractPolinoms(pol1, pol2, result);
				result.Show();

				std::cout << std::endl;
				std::cout << "Сохранить результат в таблицу?\t(yes\\no)" << std::endl;
				std::string v = "yes";
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cin >> v;

				if (v == "yes")
				{
					std::cout << "Введите ключ" << std::endl;
					int key = 0;
					std::cin >> key;


					push(result, key, un_table);


					push(result, key, or_table);


					push_polinom_ht(result, key, hash_table);
				}
				break;
			}
			case 5:
			{
				Polinom<double> pol1, pol2;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;


				double coef = -1;
				int degree = 0;

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol1.push_back(coef, degree);
				} while (coef != 0);

				coef = -1;
				degree = 0;

				std::cout << "Введите коэффициент, а затем степень (трёхзначное число)" << std::endl;
				std::cout << "Если вы хотите закончить ввод полинома, то введите любую букву" << std::endl;

				std::cin.clear();
				while (std::cin.get() != '\n');

				do
				{
					std::cin >> coef;
					std::cin >> degree;

					pol2.push_back(coef, degree);
				} while (coef != 0);

				Polinom<double> result;

				CompressionPolinom(pol1);
				RemoveZeros(pol1);
				CompressionPolinom(pol2);
				RemoveZeros(pol2);

				MultiplyPolinoms(pol1, pol2, result);
				result.Show();

				std::cout << std::endl;
				std::cout << "Сохранить результат в таблицу?\t(yes\\no)" << std::endl;
				std::string v = "yes";
				std::cin.clear();
				while (std::cin.get() != '\n');
				std::cin >> v;

				if (v == "yes")
				{
					std::cout << "Введите ключ" << std::endl;
					int key = 0;
					std::cin >> key;

					;
					push(result, key, un_table);


					push(result, key, or_table);

					push_polinom_ht(result, key, hash_table);
				}
				break;
			}
			case 6:
			{
				std::cout << "Unorder Table:" << std::endl;
				show_list_of_polinoms(un_table);
				std::cout << std::endl;
				std::cout << "Order Table:" << std::endl;
				show_list_of_polinoms(or_table);
				std::cout << std::endl;
				std::cout << "Hash Table:" << std::endl;
				show_list_of_polinoms(hash_table);
				std::cout << std::endl;
			}
			}
			std::cout << "Хотите ли вы повторить вычисления? (yes/no)" << std::endl;

			std::cin.clear();
			while (std::cin.get() != '\n');

			std::cin >> s;
		}
	}
	catch (char *error)
	{
		std::cout << error << std::endl;
	}


	return 0;
}