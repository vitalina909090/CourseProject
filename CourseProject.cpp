#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

struct Workmate
{
    string name;
    string surname;
    string father_name;

    string post;
    string phone_number;
    string email;
};

struct Car
{
    string brand;
    int year = 0;
    string model;
    int cost = 0;
    int price = 0;

};

struct Sale
{
    string person_name;
    string person_surname;
    string person_father_name;

    string automobile;
    string date_sale;
    
    int real_price = 0;

    int total_cost_whan = 0;
};

vector<Workmate> workmates;
vector<Car> cars;
vector<Sale> sales;

void load();

void reports();

void information();

void add_workmate();
void add_car();
void add_sale();

void delete_workmate();
void delete_car();
void delete_sale();

void save();

bool MyDate(const string& date);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    load();

    int option_fun;
    cout << "\033[36m\tОблік продажу автомобілів в автосалоні\033[0m\n";
    do {
        cout << "\033[36m\n\t\t\tМЕНЮ\033[0m\n";
        cout << "[1] Звіти\n[2] Додавання/Видалення інформації\n[0] Вихід\n";
        cout << "Ваш вибір: ";
        cin >> option_fun;

        switch (option_fun)
        {
        case 1:
            reports();
            break;
        case 2:
        {
            information();
            break;
        }
        case 0:
            cout << "До побачення!\n";
            break;
        default:
            cout << "Невірний вибір\n";
            break;
        }

        save();

    } while (option_fun != 0);

    return 0;
}

void load()
{
    ifstream wm_file("workmates.txt");
    if (wm_file.is_open())
    {
        Workmate wm;
        while (wm_file >> wm.surname >> wm.name >> wm.father_name >> wm.post >> wm.phone_number >> wm.email)
        {
            workmates.push_back(wm);
        }
        wm_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'workmates.txt' для читання\n";
    }

    ifstream car_file("cars.txt");
    if (car_file.is_open())
    {
        Car car;
        while (car_file >> car.brand >> car.year >> car.model >> car.cost >> car.price)
        {
            cars.push_back(car);
        }
        car_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'cars.txt' для читання\n";
    }

    ifstream sales_file("sales.txt");
    if (sales_file.is_open())
    {
        Sale sale;
        while (sales_file >> sale.person_name >> sale.person_surname >> sale.person_father_name >> sale.automobile >> sale.date_sale >> sale.real_price >> sale.total_cost_whan)
        {
            sales.push_back(sale);
        }
        sales_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'sales.txt' для читання\n";
    }
}

void reports()
{
    int option;
    cout << "\033[36m\n\t\t\tЗВІТИ\n\033[0m";
    cout << "[1] Повна інформація про співробітників фірми\n";
    cout << "[2] Повна інформація про автомобілі\n";
    cout << "[3] Повна інформація про продажі\n";
    cout << "[4] Усі продажі за певну дату\n";
    cout << "[5] Усі продажі за певний період часу\n";
    cout << "[6] Всі продажі конкретного співробітника\n";
    cout << "[7] Назва найпопулярнішого автомобіля, який продали за вказаний період часу\n";
    cout << "[8] Інформація про найуспішнішого співробітника за вказаний період часу\n";
    cout << "[9] Сумарний прибуток за вказаний період часу\n";
    cout << "[0] Вихід у меню\n";
    do
    {
        cout << "\nВаш вибір: ";
        cin >> option;

        switch (option)
        {
            case 1:
            {
                cout << "Повна інформація про співробітників фірми:\n";
                for (const auto& wm : workmates)
                {
                    cout << "ПІБ: " << wm.surname << " " << wm.name << " " << wm.father_name << ", Посада: " << wm.post << ", Контактний телефон: " << wm.phone_number << ", Email: " << wm.email << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Повна інформація про автомобілі:\n";
                for (const auto& car : cars)
                {
                    cout << "Назва виробника: " << car.brand << ", Рік випуску: " << car.year << ", Модель: " << car.model << ", Собівартість: " << car.cost << ", Потенційна ціна продажу: " << car.price << endl;
                }
                break;
            }
            case 3:
            {
                cout << "Повна інформація про продажі:\n";
                for (const auto& sale : sales)
                {
                    cout << "Співробітник: " << sale.person_surname << " " << sale.person_name << " " << sale.person_father_name << ", Автомобіль: " << sale.automobile << ", Дата продажу: " << sale.date_sale << ", Реальна ціна продажу: " << sale.real_price << endl;
                }
                break;
            }
            case 4:
            {
                string date;
                do {
                    cout << "Введіть дату продажу (YYYY-MM-DD): ";
                    cin >> date;
                } while (!MyDate(date));

                cout << "Усі продажі за дату " << date << ":\n";
                for (const auto& sale : sales)
                {
                    if (sale.date_sale == date)
                    {
                        cout << "Співробітник: " << sale.person_surname << " " << sale.person_name << " " << sale.person_father_name << ", Автомобіль: " << sale.automobile << ", Реальна ціна продажу: " << sale.real_price << endl;
                    }
                }
                break;
            }
            case 5:
            {
                string start_date, end_date;
                do {
                    cout << "Введіть початкову дату періоду (YYYY-MM-DD): ";
                    cin >> start_date;
                } while (!MyDate(start_date));

                do {
                    cout << "Введіть кінцеву дату періоду (YYYY-MM-DD): ";
                    cin >> end_date;
                } while (!MyDate(end_date));

                cout << "Усі продажі з " << start_date << " по " << end_date << ":\n";
                for (const auto& sale : sales)
                {
                    if (sale.date_sale >= start_date && sale.date_sale <= end_date)
                    {
                        cout << "Співробітник: " << sale.person_surname << " " << sale.person_name << " " << sale.person_father_name << ", Автомобіль: " << sale.automobile << ", Реальна ціна продажу: " << sale.real_price << endl;
                    }
                }
                break;
            }
            case 6: {
                int name_index = 0;
                cout << "Список співробітників:\n";
                for (int i = 0; i < workmates.size(); ++i) {
                    cout << "[" << i + 1 << "] " << workmates[i].surname << " " << workmates[i].name << " " << workmates[i].father_name << endl;
                }

                cout << "Введіть номер співробітника, щоб переглянути його продажі: ";
                cin >> name_index;
                name_index--;

                bool foundSales = false;
                if (name_index >= 0 && name_index < workmates.size()) {
                    cout << "Продажі для " << workmates[name_index].surname << " " << workmates[name_index].name << " " << workmates[name_index].father_name << ":\n";
                    for (const auto& sale : sales) {
                        if (workmates[name_index].surname == sale.person_name &&
                            workmates[name_index].name == sale.person_surname &&
                            workmates[name_index].father_name == sale.person_father_name) {
                            cout << "Автомобіль: " << sale.automobile << ", Дата продажу: " << sale.date_sale << ", Реальна ціна продажу: " << sale.real_price << endl;
                            foundSales = true;
                        }
                    }
                }
                else {
                    cout << "Неправильно введено номер працівника." << endl;
                }

                if (!foundSales) {
                    cout << "Вибраний співробітник не має продажів." << endl;
                }

                break;
            }
            case 7:
            {
                string start_date, end_date;
                do {
                    cout << "Введіть початкову дату періоду (YYYY-MM-DD): ";
                    cin >> start_date;
                } while (!MyDate(start_date));

                do {
                    cout << "Введіть кінцеву дату періоду (YYYY-MM-DD): ";
                    cin >> end_date;
                } while (!MyDate(end_date));

                cout << "Найпопулярніші автомобілі за вказаний період часу:\n";

                vector<string> automobiles;
                vector<int> sales_count;

                for (const auto& sale : sales) {
                    if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                        int i;
                        for (i = 0; i < automobiles.size(); ++i) {
                            if (automobiles[i] == sale.automobile) {
                                sales_count[i]++;
                                break;
                            }
                        }
                        if (i == automobiles.size()) {
                            automobiles.push_back(sale.automobile);
                            sales_count.push_back(1);
                        }
                    }
                }

                int max_sales = 0;
                for (int i = 0; i < automobiles.size(); ++i) {
                    if (sales_count[i] > max_sales) {
                        max_sales = sales_count[i];
                    }
                }

                if (max_sales > 0) {
                    cout << "Автомобілі з максимальною кількістю продажів (" << max_sales << " продажів):\n";
                    for (int i = 0; i < automobiles.size(); ++i) {
                        if (sales_count[i] == max_sales) {
                            cout << "Автомобіль: " << automobiles[i] << endl;
                        }
                    }
                }
                else {
                    cout << "За вказаний період часу продажі не здійснювалися.\n";
                }
                break;
            }

            case 8:
            {
                string start_date, end_date;
                do {
                    cout << "Введите начальную дату периода (YYYY-MM-DD): ";
                    cin >> start_date;
                } while (!MyDate(start_date));

                do {
                    cout << "Введите конечную дату периода (YYYY-MM-DD): ";
                    cin >> end_date;
                } while (!MyDate(end_date));

                cout << "Наиболее успешные сотрудники за указанный период времени:\n";

                vector<string> employee_names;
                vector<int> sales_amounts;

                for (const auto& sale : sales)
                {
                    // Проверяем, что дата продажи находится в заданном периоде
                    if (sale.date_sale >= start_date && sale.date_sale <= end_date)
                    {
                        string full_name = sale.person_surname + " " + sale.person_name + " " + sale.person_father_name;
                        bool found = false;

                        // Ищем сотрудника в списке employee_names
                        for (size_t i = 0; i < employee_names.size(); ++i)
                        {
                            if (employee_names[i] == full_name)
                            {
                                // Вычитаем из суммы продажи цену автомобиля, найденного в списке cars
                                for (const auto& car : cars) {
                                    if (car.model == sale.automobile) {
                                        sales_amounts[i] += (sale.real_price - sale.total_cost_whan);
                                        found = true;
                                        break;
                                    }
                                }
                                break;
                            }
                        }

                        if (!found)
                        {
                            // Если сотрудник не найден в списке, добавляем его и начальное значение суммы продаж
                            employee_names.push_back(full_name);
                            int sales_amount = 0;
                            for (const auto& car : cars) {
                                if (car.model == sale.automobile) {
                                    sales_amount = sale.real_price - sale.total_cost_whan;
                                    break;
                                }
                            }
                            sales_amounts.push_back(sales_amount);
                        }
                    }
                }

                // Находим максимальную сумму продаж
                int max_sales_amount = 0;
                for (size_t i = 0; i < employee_names.size(); ++i)
                {
                    if (sales_amounts[i] > max_sales_amount)
                    {
                        max_sales_amount = sales_amounts[i];
                    }
                }

                // Выводим всех сотрудников с максимальной суммой продаж
                if (max_sales_amount > 0)
                {
                    cout << "Наиболее успешные сотрудники за указанный период времени:\n";
                    for (size_t i = 0; i < employee_names.size(); ++i)
                    {
                        if (sales_amounts[i] == max_sales_amount)
                        {
                            cout << "Сотрудник: " << employee_names[i] << ", Сумма продаж: " << sales_amounts[i] << endl;
                        }
                    }
                }
                else
                {
                    cout << "За указанный период времени продажи не совершались.\n";
                }

                break;
            }

        case 9: {
            string start_date, end_date;
            do {
                cout << "Введіть початкову дату періоду (YYYY-MM-DD): ";
                cin >> start_date;
            } while (!MyDate(start_date));

            do {
                cout << "Введіть кінцеву дату періоду (YYYY-MM-DD): ";
                cin >> end_date;
            } while (!MyDate(end_date));

            int total_profit = 0;
            for (const auto& sale : sales) {
                if (sale.date_sale >= start_date && sale.date_sale <= end_date) {
                    total_profit += sale.real_price - sale.total_cost_whan;
                }
            }

            cout << "Загальний прибуток за період з " << start_date << " по " << end_date << ": " << total_profit << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Невірний вибір\n";
            break;
        }
    } while (option != 0);
}


void information() {
    char option_object, option_operations;
    cout << "\033[36m\n\t\t\tІНФОРМАЦІЯ\033[0m\n";
    cout << "Яку інформацію змінюємо?\n";
    cout << "[1] Співробітники\n[2] Aвтомобілі\n[3] Продажі\n[0] Вихід у меню\nВаш вибір: ";
    cin >> option_object;

    while (option_object != '0') {
        cout << "[1] додаємо | [2] видаляємо\nВаш вибір: ";
        cin >> option_operations;
        if (option_object == '1')
        {
            if (option_operations == '1')
            {
                add_workmate();
            }
            else if (option_operations == '2')
            {
                delete_workmate();
            }
        }
        else if (option_object == '2')
        {
            if (option_operations == '1')
            {
                add_car();
            }
            else if (option_operations == '2')
            {
                delete_car();
            }
        }
        else if (option_object == '3')
        {
            if (option_operations == '1')
            {
                add_sale();
            }
            else if (option_operations == '2')
            {
                delete_sale();
            }
        }
        break;
    }
}


void add_workmate()
{
    Workmate wm;
    cin.ignore();
    cout << "ВАЖЛИВО: Не використовуйте пробіли при вводі данних\n";
    cout << "Введіть прізвище: ";
    getline(cin, wm.surname);
    cout << "Введіть ім'я: ";
    getline(cin, wm.name);
    cout << "Введіть по-батькові: ";
    getline(cin, wm.father_name);
    cout << "Введіть посаду: ";
    getline(cin, wm.post);
    cout << "Введіть контактний телефон: ";
    getline(cin, wm.phone_number);
    cout << "Введіть email: ";
    getline(cin, wm.email);


    workmates.push_back(wm);
    save();
    cout << "Співробітника додано.\n";
}

void add_car()
{
    Car car;
    cin.ignore();
    cout << "Введіть назву виробника: ";
    getline(cin, car.brand);

    cout << "Введіть рік випуску: ";
    cin >> car.year;

    cin.ignore();
    cout << "Введіть модель: ";
    getline(cin, car.model);

    cout << "Введіть собівартість: ";
    cin >> car.cost;

    cout << "Введіть потенційну ціну продажу: ";
    cin >> car.price;

    cars.push_back(car);
    save();
    cout << "Автомобіль додано.\n";
}

void add_sale()
{
    Sale sale;

    for (int i = 0; i < workmates.size(); i++)
    {
        cout << "[" << i + 1 << "] " << workmates[i].surname << " " << workmates[i].name << " " << workmates[i].father_name << endl;
    }

    cout << "Виберіть співробітника: \n";
    int workmate_index;
    cin >> workmate_index;
    workmate_index--;

    sale.person_name = workmates[workmate_index].name;
    sale.person_surname = workmates[workmate_index].surname;
    sale.person_father_name = workmates[workmate_index].father_name;


    cout << "Виберіть автомобіль: \n";
    for (int i = 0; i < cars.size(); i++)
    {
        cout << "[" << i + 1 << "] " << cars[i].model << endl;
    }
    int car_index;
    cin >> car_index;
    car_index--;

    sale.automobile = cars[car_index].model;

    sale.total_cost_whan = cars[car_index].cost;

    string date;
    do
    {
        cout << "Введіть дату продажу (YYYY-MM-DD): ";
        cin >> date;
    } while (!MyDate(date));
    sale.date_sale = date;

    cout << "Введіть реальну ціну продажу: ";
    cin >> sale.real_price;

    sales.push_back(sale);
    cout << "Продажу додано успішно.\n";
}


void delete_workmate()
{
    int indexDel = 0;
    for (int i = 0; i < workmates.size(); i++)
    {
        cout << "[" << i + 1 << "] " << workmates[i].name << " " << workmates[i].surname << " " << workmates[i].father_name << endl;
    }
    cout << "Виберіть номер співробітника, якого потрібно видалити:\n";
    cout << "Ваш вибір: ";
    cin >> indexDel;

    if (indexDel > 0 && indexDel <= workmates.size())
    {
        indexDel--;
        cout << "Видалення співробітника: " << workmates[indexDel].name << " " << workmates[indexDel].surname << " " << workmates[indexDel].father_name << endl;
        for (int i = indexDel; i < workmates.size() - 1; i++)
        {
            workmates[i] = workmates[i + 1];
        }
        workmates.pop_back();
        cout << "Співробітника видалено успішно.\n";
    }
    else
    {
        cout << "Неправильний вибір. Співробітника не видалено.\n";
    }
}

void delete_car()
{
    int indexDel = 0;
    cout << "Виберіть номер автомобіля, який потрібно видалити:\n";
    for (int i = 0; i < cars.size(); i++)
    {
        cout << "[" << i + 1 << "] " << cars[i].brand << " " << cars[i].model << endl;
    }
    cout << "Ваш вибір: ";
    cin >> indexDel;

    if (indexDel > 0 && indexDel <= cars.size())
    {
        indexDel--;
        cout << "Видалення автомобіля: " << cars[indexDel].brand << " " << cars[indexDel].model << endl;
        for (int i = indexDel; i < cars.size() - 1; i++)
        {
            cars[i] = cars[i + 1];
        }
        cars.pop_back();
        cout << "Автомобіль видалено успішно.\n";
    }
    else
    {
        cout << "Неправильний вибір. Автомобіль не видалено.\n";
    }
}

void delete_sale()
{
    int indexDel = 0;
    cout << "Виберіть номер продажу, який потрібно видалити:\n";
    for (int i = 0; i < sales.size(); i++)
    {
        cout << "[" << i + 1 << "] " << sales[i].person_name << " " << sales[i].person_surname << " " << sales[i].person_father_name << " - " << sales[i].automobile << endl;
    }
    cout << "Ваш вибір: ";
    cin >> indexDel;

    if (indexDel > 0 && indexDel <= sales.size())
    {
        indexDel--;
        cout << "Видалення продажу: " << sales[indexDel].person_name << " " << sales[indexDel].person_surname << " " << sales[indexDel].person_father_name << " - " << sales[indexDel].automobile << endl;
        for (int i = indexDel; i < sales.size() - 1; i++)
        {
            sales[i] = sales[i + 1];
        }
        sales.pop_back();
        cout << "Продаж видалено успішно.\n";
    }
    else
    {
        cout << "Неправильний вибір. Продаж не видалено.\n";
    }
}


void save()
{
    ofstream wm_file("workmates.txt");
    if (wm_file.is_open())
    {
        for (const auto& wm : workmates)
        {
            wm_file << wm.surname << " " << wm.name << " " << wm.father_name << " " << wm.post << " " << wm.phone_number << " " << wm.email << endl;
        }
        wm_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'workmates.txt' для запису\n";
    }

    ofstream car_file("cars.txt");
    if (car_file.is_open())
    {
        for (const auto& car : cars)
        {
            car_file << car.brand << " " << car.year << " " << car.model << " " << car.cost << " " << car.price << endl;
        }
        car_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'cars.txt' для запису\n";
    }

    ofstream sales_file("sales.txt");
    if (sales_file.is_open())
    {
        for (const auto& sale : sales)
        {
            sales_file << sale.person_surname << " " << sale.person_name << " " << sale.person_father_name << " " << sale.automobile << " " << sale.date_sale << " " << sale.real_price << " " << sale.total_cost_whan << endl;
        }
        sales_file.close();
    }
    else
    {
        cerr << "Не вдалося відкрити файл 'sales.txt' для запису\n";
    }
}

bool MyDate(const string& date)
{
    if (date.size() != 10)
    {
        cout << "Некоректна довжина дати." << endl;
        return false;
    }

    if (date[4] != '-' || date[7] != '-')
    {
        cout << "Неправильний формат дати." << endl;
        return false;
    }

    int year = 0, month = 0, day = 0;

    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(date[i]))
        {
            cout << "Знайдено некоректний символ у році." << endl;
            return false;
        }
        year = year * 10 + (date[i] - '0');
    }

    for (int i = 5; i < 7; i++)
    {
        if (!isdigit(date[i]))
        {
            cout << "Знайдено некоректний символ у місяці." << endl;
            return false;
        }
        month = month * 10 + (date[i] - '0');
    }

    for (int i = 8; i < 10; i++)
    {
        if (!isdigit(date[i]))
        {
            cout << "Знайдено некоректний символ у дні." << endl;
            return false;
        }
        day = day * 10 + (date[i] - '0');
    }

    if (month < 1 || month > 12)
    {
        cout << "Місяць виходить за допустимі межі (1-12)." << endl;
        return false;
    }

    if (day < 1 || day > 31)
    {
        cout << "День виходить за допустимі межі (1-31)." << endl;
        return false;
    }
    return true;
}