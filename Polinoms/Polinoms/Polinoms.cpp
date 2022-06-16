#include <iostream>
#include <string>
#include "Polinoms.h"

int main()
{
    setlocale(LC_ALL, "ru");
    try
    {
        std::string v = "yes";

        while (v == "yes")
        {
            int n = 0;
            std::cout << "Введите 1 для сложения двух полиномов" << std::endl;
            std::cout << "Введите 2 для вычисления разности двух полиномов" << std::endl;
            std::cout << "Введите 3 для вычисления произведения двух полиномов" << std::endl;

            do
            {
                std::cin >> n;
            } while (n != 1 && n != 2 && n != 3);

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

            switch (n)
            {
            case 1:
                MergePolinoms(pol1, pol2, result);
                result.Show();
                break;
            case 2:
                SubtractPolinoms(pol1, pol2, result);
                result.Show();
                break;
            case 3:
                MultiplyPolinoms(pol1, pol2, result);
                result.Show();
                break;
            }


            std::cout << "Хотите ли вы повторить вычисления? (yes/no)" << std::endl;

            std::cin.clear();
            while (std::cin.get() != '\n');

            std::cin >> v;
        }
    }
    catch (char* er) {
        std::cout << er << std::endl;
    }

    return 0;
}