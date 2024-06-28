#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <unordered_map>
#include <algorithm>

double Qnr(double x, double y);
double Qnk(double x, double y);
double Rnk(double x, double y, double z);
double Gnk(double x, double y, double z);
double Wnk(double x, double y);
double U(double x, const std::unordered_map<double, double>& data);
double T(double x, const std::unordered_map<double, double>& data);
double Tfun(double u, double v, const std::string& text, const std::unordered_map<std::string, double>& dat3);

double func(double u, double v, const std::string& text, const std::unordered_map<std::string, double>& dat3) {
    if (u < 0.5 && v < 0.5) {
        return Tfun(u, v, text, dat3);
    }
    else if (u < 0.5 && v >= 0.5) {
        return Tfun(0, v, text, dat3);
    }
    else if (u >= 0.5 && v < 0.5) {
        return Tfun(u, 0, text, dat3);
    }
    else {
        return Tfun(0, 0, "", dat3);
    }
}

int main() {
    // Зчитування файлів dat1.dat, dat2.dat та dat3.dat
    std::unordered_map<double, double> dat1, dat2;
    std::unordered_map<std::string, double> dat3;

    std::ifstream file1("dat1.dat");
    if (file1.is_open()) {
        double x, y;
        while (file1 >> x >> y) {
            dat1[x] = y;
        }
        file1.close();
    }

    std::ifstream file2("dat2.dat");
    if (file2.is_open()) {
        double x, y;
        while (file2 >> x >> y) {
            dat2[x] = y;
        }
        file2.close();
    }

    std::ifstream file3("dat3.dat");
    if (file3.is_open()) {
        std::string key;
        double value;
        while (file3 >> key >> value) {
            dat3[key] = value;
        }
        file3.close();
    }

    // Введення x, y, z та text
    double x, y, z;
    std::string text;
    std::cin >> x >> y >> z;
    std::cin.ignore(); // Ігноруємо залишок рядка після чисел
    std::getline(std::cin, text);

    // Обчислення функції
    double u, v;
    u = Qnk(x, y) + Rnk(x, y, z);
    v = 2 * Gnk(x, y, z);

    if (x * y - 10 > 0) {
        z = 1.25;
        u = Qnk(x, y) + Rnk(x, y, z);
    }
    else if (x * y - 2 > 0) {
        z = 1.5;
        u = Qnk(x, y) + Rnk(x, y, z);
    }
    else if (x - y > 0) {
        y = 0;
        u = Qnk(x, y);
    }

    double result = func(u, v, text, dat3);

    // Виведення результату
    std::cout << "Result: " << result << std::endl;

    return 0;
}

// Реалізація функцій
double Qnr(double x, double y) {
    if (x != 0 && y != 0) {
        if (x > 0 && y <= 0) {
            return 1.0 / (10 * y - 2 * x);
        }
        else if (x > 0 && y > 0) {
            return std::log(10 * y - 3 * x) * 10;
        }
        else if (x <= 0 && y <= 0) {
            return 3 * x * y;
        }
    }
    return 1.0;
}

double Qnk(double x, double y) {
    return 10 - 5 * Qnr(2 * x, 2 * y) + 3.75 * Qnr(y, x);
}

double Rnk(double x, double y, double z) {
    return Qnk(x, z) + Qnk(z, y) + Qnk(y, x);
}

double Gnk(double x, double y, double z) {
    return Wnk(x, z) + Wnk(z, y) + Wnk(y, x);
}

double Wnk(double x, double y) {
    return 10 - 5 * Qnr(2 * x, 2 * y) + 3.75 * Qnr(y, x);
}

double U(double x, const std::unordered_map<double, double>& data) {
    auto it = data.find(x);
    if (it != data.end()) {
        return it->second;
    }
    return 0.0; // Значення за замовчуванням
}

double T(double x, const std::unordered_map<double, double>& data) {
    auto it = data.find(x);
    if (it != data.end()) {
        return it->second;
    }
    return 0.0; // Значення за замовчуванням
}

double Tfun(double u, double v, const std::string& text, const std::unordered_map<std::string, double>& dat3) {
    double r = 0.0;
    auto it = dat3.find(text);
    if (it != dat3.end()) {
        r = it->second;
    }
    return std::sqrt((u - v) * (u - v) + r * r * r);
}
