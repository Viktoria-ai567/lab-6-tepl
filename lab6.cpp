#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

const int mf = 500; // Максимальное количество узлов

// Определяем вектор типа double для хранения температур и коэффициентов
typedef vector<double> Vector;
// Раздел описания переменных, которые мы будем использовать в программе
int main() {
    system("chcp 1251"); // Установка кодировки консоли для корректного отображения символов
    system("cls"); // Очистка экрана
   
    int i, j, N; // Количество узлов и вспомогательные переменные
    Vector T(mf), alfa(mf), beta(mf); // Температура и прогоночные коэффициенты
    double ai, bi, ci, fi; // Коэффициенты уравнения
    double lamda, ro, c, h, tau; // Параметры материала и шаги
    double Tl, T0, Tr, L, t_end, time; // Граничные условия и переменные времени

    // Ввод данных с клавиатуры
    cout << "Enter the number of spatial nodes, N: ";
    cin >> N;
    cout << "Enter the end time, t_end: ";
    cin >> t_end;
    cout << "Enter the thickness of the plate, L: ";
    cin >> L;
    cout << "Enter the thermal conductivity coefficient of the plate material, lambda: ";
    cin >> lamda;
    cout << "Enter the density of the plate material, ro: ";
    cin >> ro;0.0;

    // Определяем поле температуры в начальный момент времени
    for (i = 0; i < N; i++) {
        T[i] = T0;
    }

    // Проводим интегрирование нестационарного уравнения теплопроводности
    time = 0;
    while (time < t_end) { // Цикл по времени
        time += tau; // Увеличиваем время на шаг

        // Определяем начальные прогоночные коэффициенты на основе левого граничного условия
        alfa[0] = 0.0; // Коэффициент alfa для первого узла
        beta[0] = Tl; // Коэффициент beta для первого узла

        // Расчет прогоночных коэффициентов (ai, bi, ci, fi – коэффициенты канонического представления СЛАУ с трехдиагональной матрицей)
        for (i = 1; i < N - 1; i++) {
            ai = lamda / (h * h);
            bi = 2.0 * lamda / (h * h) + ro * c / tau;
            ci = lamda / (h * h);
            fi = -ro * c * T[i] 

    cout << "Enter the heat capacity of the plate material, c: ";
    cin >> c;
    cout << "Enter the initial temperature, T0: ";
    cin >> T0;
    cout << "Enter the temperature at the border x=0, Tl: ";
    cin >> Tl;
    cout << "Enter the temperature at the border x=L, Tr: ";
    cin >> Tr;

    // Определяем расчетный шаг сетки по пространственной координате
    h = L / (N - 1);

    // Определяем расчетный шаг сетки по времени
    tau = t_end / 10/ tau;
        // alfa[i], beta[i] – прогоночные коэффициенты
            alfa[i] = ai / (bi - ci * alfa[i - 1]);
            beta[i] = (ci * beta[i - 1] - fi) / (bi - ci * alfa[i - 1]);
        }

        // Определяем значение температуры на правой границе
        T[N - 1] = Tr;

        // Вычисление температурного поля
        for (i = N - 2; i >= 0; i--) {
            T[i] = alfa[i] * T[i + 1] + beta[i];
        }
    }

    // Выводим результаты в файл "res.txt"
    ofstream f("res.txt");
    f << fixed << setprecision(4); // Установка точности вывода
    f << "Толщина пластины L = " << L << endl;
    f << "Число узлов по координате N = " << N << endl;
    f << "Коэффициент теплопроводности материала пластины lambda = " << lamda << endl;
    f << "Плотность материала пластины ro = " << ro << endl;
    f << "Теплоемкость материала пластины c = " << c << endl;
    f << "Начальная температура T0 = " << T0 << endl;
    f << "Температура на границе x = 0, Tl = " << Tl << endl;
    f << "Температура на границе x = L, Tr = " << Tr << endl;
    f << "Результат получен с шагом по координате h = " << h << endl;
    f << "Результат получен с шагом по времени tau = " << tau << endl;
    f << "Температурное поле в момент времени t = " << t_end << endl;
    f.close();

    // Запись температурного поля в файл "tempr.txt"
    ofstream g("tempr.txt");
    g << fixed << setprecision(5); // Установка точности вывода
    for (i = 0; i < N; i++) {
        g << setw(6) << h * i << " " << setw(8) << T[i] << endl; // Запись координаты и температуры
    }
    g.close();

    return 0;
}
