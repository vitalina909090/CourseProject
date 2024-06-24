#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <Windows.h>

using namespace std;


// Structures
struct Workmate {
    string full_name;       // ПІБ 
    string post;            // Посада 
    string phone_number;    // Контактний телефон 
    string email;           // Email 
};

struct Car {
    string brand;   // Назва виробника 
    int year;       // Рік випуску 
    string model;   // Модель 
    int cost;       // Собівартість
    int price;      // Потенційна ціна продажу
};

struct Sale {
    string person;          // Співробітник
    string automobile;      // Автомобіль
    string date_sale;       // Дата продажу
    int real_price;         // Реальна ціна продажу
};

// Vectors based on structures 
vector<Workmate> workmates;
vector<Car> cars;
vector<Sale> sales;

// Function prototypes
void load();
void reports();
void add_workmate();
void add_car();
void add_sale();
void delete_workmate();
void delete_car();
void delete_sale();
void save();

// Main function
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    load();

    char option_fun;
    cout << "\033[36m\tОблік продажу автомобілів в автосалоні\033[0m\n";
    cout << "\t\t\tМЕНЮ\n";
    do {
        cout << "[1] Звіти\n[2] Додавання/Видалення інформації\n[0] Вихід\n";
        cout << "Ваш вибір: ";
        cin >> option_fun;

        switch (option_fun) {
        case '1':
            reports();
            break;
        case '2': {
            char option_object, option_operations;
            do {
                cout << "Яку інформацію змінюємо?\n";
                cout << "[1] Співробітники\n[2] Aвтомобілі\n[3] Продажі\n[0] Повернутися в головне меню\nВаш вибір: ";
                cin >> option_object;
                cout << "[1] додаємо | [2] видаляємо\nВаш вибір: ";
                cin >> option_operations;

                if (option_object == '1') {
                    if (option_operations == '1') {
                        add_workmate();
                    }
                    else if (option_operations == '2') {
                        delete_workmate();
                    }
                }
                else if (option_object == '2') {
                    if (option_operations == '1') {
                        add_car();
                    }
                    else if (option_operations == '2') {
                        delete_car();
                    }
                }
                else if (option_object == '3') {
                    if (option_operations == '1') {
                        add_sale();
                    }
                    else if (option_operations == '2') {
                        delete_sale();
                    }
                }
                break;
            } while (option_object != '0');
        }
        case '0':
            cout << "До побачення!\n";
            break;
        default:
            cout << "Невірний вибір\n";
            break;
        }

        save(); // Save data after each operation

    } while (option_fun != '0');

    return 0;
}

// Load data from files
void load() {
    ifstream wm_file("workmates.txt");
    if (wm_file.is_open()) {
        Workmate wm;
        while (wm_file >> wm.full_name >> wm.post >> wm.phone_number >> wm.email) {
            workmates.push_back(wm);
        }
        wm_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'workmates.txt' для читання\n";
    }

    ifstream car_file("cars.txt");
    if (car_file.is_open()) {
        Car car;
        while (car_file >> car.brand >> car.year >> car.model >> car.cost >> car.price) {
            cars.push_back(car);
        }
        car_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'cars.txt' для читання\n";
    }

    ifstream sales_file("sales.txt");
    if (sales_file.is_open()) {
        Sale sale;
        while (sales_file >> sale.person >> sale.automobile >> sale.date_sale >> sale.real_price) {
            sales.push_back(sale);
        }
        sales_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'sales.txt' для читання\n";
    }
}

// Reports
void reports() {
    char option;
    cout << "\t\t\tЗВІТИ\n";
    cout << "[1] Повна інформація про співробітників фірми\n";
    cout << "[2] Повна інформація про автомобілі\n";
    cout << "[3] Повна інформація про продажі\n";
    cout << "[4] Усі продажі за певну дату\n";
    cout << "[5] Усі продажі за певний період часу\n";
    cout << "[6] Всі продажі конкретного співробітника\n";
    cout << "[7] Назва найпопулярнішого автомобіля, який продали за вказаний період часу\n";
    cout << "[8] Інформація про найуспішнішого співробітника за вказаний період часу\n";
    cout << "[9] Сумарний прибуток за вказаний період часу\n";
    cout << "[0] Вихід\n";
    do {
        cout << "Ваш вибір: ";
        cin >> option;

        switch (option) {
        case '1': {
            cout << "Повна інформація про співробітників фірми:\n";
            for (const auto& wm : workmates) {
                cout << "ПІБ: " << wm.full_name << ", Посада: " << wm.post << ", Контактний телефон: " << wm.phone_number << ", Email: " << wm.email << endl;
            }
            break;
        }
        case '2': {
            cout << "Повна інформація про автомобілі:\n";
            for (const auto& car : cars) {
                cout << "Назва виробника: " << car.brand << ", Рік випуску: " << car.year << ", Модель: " << car.model << ", Собівартість: " << car.cost << ", Потенційна ціна продажу: " << car.price << endl;
            }
            break;
        }
        case '3': {
            cout << "Повна інформація про продажі:\n";
            for (const auto& sale : sales) {
                cout << "Співробітник: " << sale.person << ", Автомобіль: " << sale.automobile << ", Дата продажу: " << sale.date_sale << ", Реальна ціна продажу: " << sale.real_price << endl;
            }
            break;
        }
        case '4': {
            string date;
            cout << "Введіть дату продажу: ";
            cin >> date;
            cout << "Усі продажі за дату " << date << ":\n";
            for (const auto& sale : sales) {
                if (sale.date_sale == date) {
                    cout << "Співробітник: " << sale.person << ", Автомобіль: " << sale.automobile << ", Реальна ціна продажу: " << sale.real_price << endl;
                }
            }
            break;
        }
        case '5': {
            string start_date, end_date;
            cout << "Введіть початкову дату періоду: ";
            cin >> start_date;
            cout << "Введіть кінцеву дату періоду: ";
            cin >> end_date;
            cout << "Усі продажі з " << start_date << " по " << end_date << ":\n";
            for (const auto& sale : sales) {
                if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                    cout << "Співробітник: " << sale.person << ", Автомобіль: " << sale.automobile << ", Реальна ціна продажу: " << sale.real_price << endl;
                }
            }
            break;
        }
        case '6': {
            string employee_name;
            cout << "Введіть ім'я співробітника: ";
            cin.ignore();
            getline(cin, employee_name);
            cout << "Усі продажі співробітника " << employee_name << ":\n";
            for (const auto& sale : sales) {
                if (sale.person == employee_name) {
                    cout << "Автомобіль: " << sale.automobile << ", Дата продажу: " << sale.date_sale << ", Реальна ціна продажу: " << sale.real_price << endl;
                }
            }
            break;
        }
        case '7': {
            string start_date, end_date;
            cout << "Введіть початкову дату періоду: ";
            cin >> start_date;
            cout << "Введіть кінцеву дату періоду: ";
            cin >> end_date;

            map<string, int> car_sales_count;
            for (const auto& sale : sales) {
                if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                    car_sales_count[sale.automobile]++;
                }
            }

            string popular_car;
            int max_sales = 0;
            for (const auto& pair : car_sales_count) {
                if (pair.second > max_sales) {
                    max_sales = pair.second;
                    popular_car = pair.first;
                }
            }

            cout << "Найпопулярніший автомобіль за період з " << start_date << " по " << end_date << " - " << popular_car << endl;
            break;
        }
        case '8': {
            string start_date, end_date;
            cout << "Введіть початкову дату періоду: ";
            cin >> start_date;
            cout << "Введіть кінцеву дату періоду: ";
            cin >> end_date;

            map<string, int> employee_sales_count;
            for (const auto& sale : sales) {
                if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                    employee_sales_count[sale.person] += sale.real_price;
                }
            }

            string most_successful_employee;
            int max_sales_amount = 0;
            for (const auto& pair : employee_sales_count) {
                if (pair.second > max_sales_amount) {
                    max_sales_amount = pair.second;
                    most_successful_employee = pair.first;
                }
            }

            cout << "Найуспішніший співробітник за період з " << start_date << " по " << end_date << " - " << most_successful_employee << endl;
            break;
        }
        case '9': {
            string start_date, end_date;
            cout << "Введіть початкову дату періоду: ";
            cin >> start_date;
            cout << "Введіть кінцеву дату періоду: ";
            cin >> end_date;

            int total_profit = 0;
            for (const auto& sale : sales) {
                if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                    // Находим автомобиль по названию в векторе cars
                    auto it = std::find_if(cars.begin(), cars.end(), [&sale](const Car& car) {
                        return car.model == sale.automobile;
                        });

                    if (it != cars.end()) {
                        total_profit += sale.real_price - it->cost;
                    }
                    else {
                        // Обработка ситуации, если автомобиль не найден (ошибка в данных)
                        std::cerr << "Ошибка: Автомобиль '" << sale.automobile << "' не найден в базе данных." << std::endl;
                    }
                }
            }

            cout << "Сумарний прибуток за період з " << start_date << " по " << end_date << " - " << total_profit << endl;
            break;
        }
        default: {
            cout << "Невірний вибір\n";
            break;
        }
        }
    } while (option != '0');
}

// Add a new workmate
void add_workmate() {
    Workmate wm;
    cout << "Введіть ПІБ співробітника: ";
    cin.ignore();
    getline(cin, wm.full_name);
    cout << "Введіть посаду: ";
    getline(cin, wm.post);
    cout << "Введіть контактний телефон: ";
    getline(cin, wm.phone_number);
    cout << "Введіть email: ";
    getline(cin, wm.email);

    workmates.push_back(wm);
    cout << "Співробітник доданий успішно!\n";
}

// Add a new car
void add_car() {
    Car car;
    cout << "Введіть назву виробника: ";
    cin.ignore();
    getline(cin, car.brand);
    cout << "Введіть рік випуску: ";
    cin >> car.year;
    cout << "Введіть модель: ";
    cin.ignore();
    getline(cin, car.model);
    cout << "Введіть собівартість: ";
    cin >> car.cost;
    cout << "Введіть потенційну ціну продажу: ";
    cin >> car.price;

    cars.push_back(car);
    cout << "Автомобіль доданий успішно!\n";
}

// Add a new sale
void add_sale() {
    Sale sale;
    cout << "Введіть ім'я співробітника: ";
    cin.ignore();
    getline(cin, sale.person);
    cout << "Введіть назву автомобіля: ";
    getline(cin, sale.automobile);
    cout << "Введіть дату продажу (ДД.ММ.РРРР): ";
    getline(cin, sale.date_sale);
    cout << "Введіть реальну ціну продажу: ";
    cin >> sale.real_price;

    sales.push_back(sale);
    cout << "Продаж зареєстровано успішно!\n";
}

// Delete a workmate
void delete_workmate() {
    int index;
    cout << "Введіть індекс співробітника для видалення: ";
    cin >> index;

    if (index >= 0 && index < workmates.size()) {
        workmates.erase(workmates.begin() + index);
        cout << "Співробітник видалений успішно!\n";
    }
    else {
        cout << "Неправильний індекс співробітника!\n";
    }
}

// Delete a car
void delete_car() {
    int index;
    cout << "Введіть індекс автомобіля для видалення: ";
    cin >> index;

    if (index >= 0 && index < cars.size()) {
        cars.erase(cars.begin() + index);
        cout << "Автомобіль видалений успішно!\n";
    }
    else {
        cout << "Неправильний індекс автомобіля!\n";
    }
}

// Delete a sale
void delete_sale() {
    int index;
    cout << "Введіть індекс продажу для видалення: ";
    cin >> index;

    if (index >= 0 && index < sales.size()) {
        sales.erase(sales.begin() + index);
        cout << "Продаж видалено успішно!\n";
    }
    else {
        cout << "Неправильний індекс продажу!\n";
    }
}

// Save data to files
void save() {
    ofstream wm_file("workmates.txt");
    if (wm_file.is_open()) {
        for (const auto& wm : workmates) {
            wm_file << wm.full_name << " " << wm.post << " " << wm.phone_number << " " << wm.email << endl;
        }
        wm_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'workmates.txt' для запису\n";
    }

    ofstream car_file("cars.txt");
    if (car_file.is_open()) {
        for (const auto& car : cars) {
            car_file << car.brand << " " << car.year << " " << car.model << " " << car.cost << " " << car.price << endl;
        }
        car_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'cars.txt' для запису\n";
    }

    ofstream sales_file("sales.txt");
    if (sales_file.is_open()) {
        for (const auto& sale : sales) {
            sales_file << sale.person << " " << sale.automobile << " " << sale.date_sale << " " << sale.real_price << endl;
        }
        sales_file.close();
    }
    else {
        cerr << "Не вдалося відкрити файл 'sales.txt' для запису\n";
    }
}