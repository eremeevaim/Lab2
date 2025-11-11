#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

struct Pipe {
    int id;
    string name;
    float length;
    int diameter;
    bool inRepair;

    friend ostream& operator<<(ostream& out, const Pipe& pipe) {
        out << "====================" << endl;
        out << "ТРУБА ID: " << pipe.id << endl;
        out << "====================" << endl;
        out << "Название: " << pipe.name << endl;
        out << "Длина: " << pipe.length << " км" << endl;
        out << "Диаметр: " << pipe.diameter << " мм" << endl;
        out << "В ремонте: " << (pipe.inRepair ? "Да" : "Нет") << endl;
        return out;
    }
};

struct KS {
    int id;
    string name;
    int totalWorkshops;
    int workingWorkshops;

    double getUnusedPercentage() const {
        if (totalWorkshops == 0) return 0.0;
        return ((totalWorkshops - workingWorkshops) * 100.0) / totalWorkshops;
    }

    friend ostream& operator<<(ostream& out, const KS& station) {
        out << "====================" << endl;
        out << "КОМПРЕССОРНАЯ СТАНЦИЯ ID: " << station.id << endl;
        out << "====================" << endl;
        out << "Название: " << station.name << endl;
        out << "Всего цехов: " << station.totalWorkshops << endl;
        out << "Работающих цехов: " << station.workingWorkshops << endl;
        out << "Незадействованных цехов: " << (station.totalWorkshops - station.workingWorkshops) << endl;
        out << "Процент незадействованных: " << station.getUnusedPercentage() << "%" << endl;
        return out;
    }
};

// Глобальные коллекции
unordered_map<int, Pipe> pipes;
unordered_map<int, KS> stations;
int nextPipeId = 1;
int nextStationId = 1;

// Вспомогательная функция для удаления пробелов
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

// Улучшенные функции проверки ввода
string checkString() {
    string input;
    while (true) {
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            return input;
        }
        cout << "Ошибка! Ввод не может быть пустым или состоять только из пробелов, попробуйте снова: ";
    }
}

bool checkBool() {
    while (true) {
        string input;
        getline(cin, input);
        input = trim(input);
        if (input == "1") return true;
        if (input == "0") return false;
        cout << "Ошибка! Введите 0 или 1: ";
    }
}

int checkInt() {
    string input;
    while (true) {
        getline(cin, input);
        input = trim(input);
        try {
            size_t pos;
            int result = stoi(input, &pos);
            if (pos == input.size()) {
                return result;
            }
        }
        catch (...) {
        }
        cout << "Ошибка! Введите целое число: ";
    }
}

float checkFloat() {
    string input;
    while (true) {
        getline(cin, input);
        input = trim(input);
        try {
            size_t pos;
            float result = stof(input, &pos);
            if (pos == input.size()) {
                return result;
            }
        }
        catch (...) {
        }
        cout << "Ошибка! Введите число: ";
    }
}

// Новая функция для проверки положительного float
float checkPositiveFloat(const string& fieldName) {
    float value;
    while (true) {
        value = checkFloat();
        if (value > 0) {
            return value;
        }
        cout << fieldName << " должно быть положительным! Повторите ввод: ";
    }
}

// Новая функция для проверки положительного int
int checkPositiveInt(const string& fieldName) {
    int value;
    while (true) {
        value = checkInt();
        if (value > 0) {
            return value;
        }
        cout << fieldName << " должно быть положительным! Повторите ввод: ";
    }
}

// Новая функция для проверки неотрицательного int
int checkNonNegativeInt(const string& fieldName) {
    int value;
    while (true) {
        value = checkInt();
        if (value >= 0) {
            return value;
        }
        cout << fieldName << " не может быть отрицательным! Повторите ввод: ";
    }
}

// Новая функция для проверки процента (0-100)
float checkPercentage() {
    float value;
    while (true) {
        value = checkFloat();
        if (value >= 0 && value <= 100) {
            return value;
        }
        cout << "Процент должен быть в диапазоне от 0 до 100! Повторите ввод: ";
    }
}

int checkMenuChoice() {
    string input;
    while (true) {
        getline(cin, input);
        input = trim(input);
        if (input.size() == 1 && input[0] >= '0' && input[0] <= '8') {
            return input[0] - '0';
        }
        cout << "Некорректный выбор. Пожалуйста, выберите пункт от 0 до 8: ";
    }
}

int checkEditChoice(int max) {
    string input;
    while (true) {
        getline(cin, input);
        input = trim(input);
        try {
            int choice = stoi(input);
            if (choice >= 0 && choice <= max) {
                return choice;
            }
        }
        catch (...) {
        }
        cout << "Некорректный выбор. Пожалуйста, выберите пункт от 0 до " << max << ": ";
    }
}

// Функция для поиска без учета регистра
bool containsIgnoreCase(const string& str, const string& substr) {
    string strLower = str;
    string substrLower = substr;
    transform(strLower.begin(), strLower.end(), strLower.begin(), ::tolower);
    transform(substrLower.begin(), substrLower.end(), substrLower.begin(), ::tolower);
    return strLower.find(substrLower) != string::npos;
}

// Функции поиска 
void findPipesByName() {
    if (pipes.empty()) {
        cout << "Нет труб для поиска." << endl;
        return;
    }

    cout << "Введите часть названия для поиска: ";
    string searchName = checkString();

    bool found = false;
    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        const Pipe& pipe = it->second;
        if (containsIgnoreCase(pipe.name, searchName)) {
            cout << pipe;
            found = true;
        }
    }

    if (!found) {
        cout << "Трубы с названием содержащим '" << searchName << "' не найдены." << endl;
    }
}

void findPipesByRepairStatus() {
    if (pipes.empty()) {
        cout << "Нет труб для поиска." << endl;
        return;
    }

    cout << "Искать трубы в ремонте? (1 - да, 0 - нет): ";
    bool searchStatus = checkBool();

    bool found = false;
    for (auto it = pipes.begin(); it != pipes.end(); ++it) {
        const Pipe& pipe = it->second;
        if (pipe.inRepair == searchStatus) {
            cout << pipe;
            found = true;
        }
    }

    if (!found) {
        cout << "Трубы с указанным статусом ремонта не найдены." << endl;
    }
}

void findStationsByName() {
    if (stations.empty()) {
        cout << "Нет КС для поиска." << endl;
        return;
    }

    cout << "Введите часть названия для поиска: ";
    string searchName = checkString();

    bool found = false;
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        const KS& station = it->second;
        if (containsIgnoreCase(station.name, searchName)) {
            cout << station;
            found = true;
        }
    }

    if (!found) {
        cout << "КС с названием содержащим '" << searchName << "' не найдены." << endl;
    }
}

void findStationsByUnusedPercentage() {
    if (stations.empty()) {
        cout << "Нет КС для поиска." << endl;
        return;
    }

    cout << "Введите минимальный процент незадействованных цехов (0-100): ";
    double minPercentage = checkPercentage();

    bool found = false;
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        const KS& station = it->second;
        if (station.getUnusedPercentage() >= minPercentage) {
            cout << station;
            found = true;
        }
    }

    if (!found) {
        cout << "КС с процентом незадействованных цехов >= " << minPercentage << "% не найдены." << endl;
    }
}

// Меню поиска
void searchMenu() {
    while (true) {
        cout << "\n=== МЕНЮ ПОИСКА ===" << endl;
        cout << "1 - Поиск труб по названию" << endl;
        cout << "2 - Поиск труб по статусу ремонта" << endl;
        cout << "3 - Поиск КС по названию" << endl;
        cout << "4 - Поиск КС по проценту незадействованных цехов" << endl;
        cout << "0 - Назад в главное меню" << endl;
        cout << "Выберите действие: ";

        int choice = checkEditChoice(4);
        switch (choice) {
        case 1: findPipesByName(); break;
        case 2: findPipesByRepairStatus(); break;
        case 3: findStationsByName(); break;
        case 4: findStationsByUnusedPercentage(); break;
        case 0: return;
        }
    }
}

// Основные функции 
void addPipe() {
    Pipe newPipe;
    newPipe.id = nextPipeId++;

    cout << "Введите характеристики для трубы (ID: " << newPipe.id << ")." << endl;
    cout << "Название: ";
    newPipe.name = checkString();
    cout << "Длина (км): ";
    newPipe.length = checkPositiveFloat("Длина");
    cout << "Диаметр (мм): ";
    newPipe.diameter = checkPositiveInt("Диаметр");
    cout << "В ремонте ли труба? (Да - '1', Нет - '0') ";
    newPipe.inRepair = checkBool();

    pipes[newPipe.id] = newPipe;
    cout << "Труба успешно добавлена с ID: " << newPipe.id << endl;
}

void addStation() {
    KS newStation;
    newStation.id = nextStationId++;

    cout << "Введите характеристики для станции (ID: " << newStation.id << ")." << endl;
    cout << "Название: ";
    newStation.name = checkString();
    cout << "Количество цехов: ";
    newStation.totalWorkshops = checkPositiveInt("Количество цехов");

    cout << "Количество цехов (в работе): ";
    while (true) {
        newStation.workingWorkshops = checkNonNegativeInt("Количество работающих цехов");
        if (newStation.workingWorkshops <= newStation.totalWorkshops) {
            break;
        }
        cout << "Количество работающих цехов не может быть больше общего количества ("
            << newStation.totalWorkshops << ")! Повторите ввод: ";
    }

    stations[newStation.id] = newStation;
    cout << "КС успешно добавлена с ID: " << newStation.id << endl;
}

void viewAllObjects() {
    if (pipes.empty() && stations.empty()) {
        cout << "Никаких данных не было введено." << endl;
        return;
    }

    if (!pipes.empty()) {
        cout << "\n=== ВСЕ ТРУБЫ (" << pipes.size() << " шт.) ===" << endl;
        for (auto it = pipes.begin(); it != pipes.end(); ++it) {
            cout << it->second;
        }
    }

    if (!stations.empty()) {
        cout << "\n=== ВСЕ КОМПРЕССОРНЫЕ СТАНЦИИ (" << stations.size() << " шт.) ===" << endl;
        for (auto it = stations.begin(); it != stations.end(); ++it) {
            cout << it->second;
        }
    }
}

// Улучшенные функции редактирования
void editPipe() {
    if (pipes.empty()) {
        cout << "Нет труб для редактирования." << endl;
        return;
    }

    cout << "Введите ID трубы для редактирования: ";
    int pipeId = checkInt();

    if (pipes.find(pipeId) == pipes.end()) {
        cout << "Труба с ID " << pipeId << " не найдена!" << endl;
        return;
    }

    Pipe& pipe = pipes[pipeId];
    cout << "Редактирование трубы: " << pipe.name << " (ID: " << pipeId << ")" << endl;

    cout << "Новое название: ";
    pipe.name = checkString();
    cout << "Новая длина (км): ";
    pipe.length = checkPositiveFloat("Длина");
    cout << "Новый диаметр (мм): ";
    pipe.diameter = checkPositiveInt("Диаметр");
    cout << "В ремонте? (1 - да, 0 - нет): ";
    pipe.inRepair = checkBool();

    cout << "Труба успешно отредактирована!" << endl;
}

void editStation() {
    if (stations.empty()) {
        cout << "Нет станций для редактирования." << endl;
        return;
    }

    cout << "Введите ID станции для редактирования: ";
    int stationId = checkInt();

    if (stations.find(stationId) == stations.end()) {
        cout << "Станция с ID " << stationId << " не найдена!" << endl;
        return;
    }

    KS& station = stations[stationId];
    cout << "Редактирование станции: " << station.name << " (ID: " << stationId << ")" << endl;

    cout << "Новое название: ";
    station.name = checkString();
    cout << "Новое общее количество цехов: ";
    station.totalWorkshops = checkPositiveInt("Количество цехов");

    cout << "Новое количество работающих цехов: ";
    while (true) {
        station.workingWorkshops = checkNonNegativeInt("Количество работающих цехов");
        if (station.workingWorkshops <= station.totalWorkshops) {
            break;
        }
        cout << "Количество работающих цехов не может быть больше общего количества ("
            << station.totalWorkshops << ")! Повторите ввод: ";
    }

    cout << "Станция успешно отредактирована!" << endl;
}

// Улучшенные функции работы с файлами
void saveToFile() {
    cout << "Введите имя файла для сохранения: ";
    string filename = checkString();

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    // Сохраняем трубы
    file << pipes.size() << endl;
    for (const auto& pipe : pipes) {
        file << pipe.second.id << endl;
        file << pipe.second.name << endl;
        file << pipe.second.length << endl;
        file << pipe.second.diameter << endl;
        file << pipe.second.inRepair << endl;
    }

    // Сохраняем станции
    file << stations.size() << endl;
    for (const auto& station : stations) {
        file << station.second.id << endl;
        file << station.second.name << endl;
        file << station.second.totalWorkshops << endl;
        file << station.second.workingWorkshops << endl;
    }

    if (file.fail()) {
        cout << "Ошибка при записи данных в файл!" << endl;
        file.close();
        return;
    }

    file.close();
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}

void loadFromFile() {
    cout << "Введите имя файла для загрузки: ";
    string filename = checkString();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для чтения! Проверьте, что файл существует." << endl;
        return;
    }

    // Предупреждение о перезаписи
    if (!pipes.empty() || !stations.empty()) {
        cout << "ВНИМАНИЕ! Текущие данные будут удалены. Продолжить? (1 - да, 0 - нет): ";
        if (!checkBool()) {
            file.close();
            cout << "Загрузка отменена." << endl;
            return;
        }
    }

    // Создаем временные коллекции для безопасной загрузки
    unordered_map<int, Pipe> tempPipes;
    unordered_map<int, KS> tempStations;
    int tempNextPipeId = 1;
    int tempNextStationId = 1;

    try {
        // Загружаем трубы
        int pipeCount;
        file >> pipeCount;
        if (file.fail() || pipeCount < 0) {
            throw runtime_error("Неверный формат файла: некорректное количество труб");
        }
        file.ignore();

        for (int i = 0; i < pipeCount; i++) {
            Pipe pipe;
            file >> pipe.id;
            if (file.fail()) throw runtime_error("Ошибка чтения ID трубы");
            file.ignore();

            getline(file, pipe.name);
            if (pipe.name.empty()) throw runtime_error("Ошибка чтения названия трубы");

            file >> pipe.length;
            if (file.fail() || pipe.length <= 0) throw runtime_error("Ошибка чтения длины трубы");

            file >> pipe.diameter;
            if (file.fail() || pipe.diameter <= 0) throw runtime_error("Ошибка чтения диаметра трубы");

            file >> pipe.inRepair;
            if (file.fail()) throw runtime_error("Ошибка чтения статуса ремонта трубы");
            file.ignore();

            tempPipes[pipe.id] = pipe;
            tempNextPipeId = max(tempNextPipeId, pipe.id + 1);
        }

        // Загружаем станции
        int stationCount;
        file >> stationCount;
        if (file.fail() || stationCount < 0) {
            throw runtime_error("Неверный формат файла: некорректное количество станций");
        }
        file.ignore();

        for (int i = 0; i < stationCount; i++) {
            KS station;
            file >> station.id;
            if (file.fail()) throw runtime_error("Ошибка чтения ID станции");
            file.ignore();

            getline(file, station.name);
            if (station.name.empty()) throw runtime_error("Ошибка чтения названия станции");

            file >> station.totalWorkshops;
            if (file.fail() || station.totalWorkshops <= 0) throw runtime_error("Ошибка чтения количества цехов");

            file >> station.workingWorkshops;
            if (file.fail() || station.workingWorkshops < 0 || station.workingWorkshops > station.totalWorkshops) {
                throw runtime_error("Ошибка чтения количества работающих цехов");
            }
            file.ignore();

            tempStations[station.id] = station;
            tempNextStationId = max(tempNextStationId, station.id + 1);
        }

        // Если все прошло успешно, переносим данные
        pipes = tempPipes;
        stations = tempStations;
        nextPipeId = tempNextPipeId;
        nextStationId = tempNextStationId;

        file.close();
        cout << "Данные успешно загружены из файла: " << filename << endl;
        cout << "Загружено труб: " << pipes.size() << ", станций: " << stations.size() << endl;

    }
    catch (const exception& e) {
        cout << "ОШИБКА при загрузке файла: " << e.what() << endl;
        cout << "Текущие данные не были изменены." << endl;
        file.close();
        return;
    }
}

void displayMenu() {
    cout << "\n=== ГЛАВНОЕ МЕНЮ ===" << endl;
    cout << "1 - Добавить трубу" << endl;
    cout << "2 - Добавить КС" << endl;
    cout << "3 - Просмотр всех объектов" << endl;
    cout << "4 - Поиск объектов" << endl;
    cout << "5 - Редактировать трубу" << endl;
    cout << "6 - Редактировать КС" << endl;
    cout << "7 - Сохранить" << endl;
    cout << "8 - Загрузить" << endl;
    cout << "0 - Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "RU");

    while (true) {
        displayMenu();
        int choice = checkMenuChoice();

        switch (choice) {
        case 1: addPipe(); break;
        case 2: addStation(); break;
        case 3: viewAllObjects(); break;
        case 4: searchMenu(); break;
        case 5: editPipe(); break;
        case 6: editStation(); break;
        case 7: saveToFile(); break;
        case 8: loadFromFile(); break;
        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        }
    }

    return 0;
}