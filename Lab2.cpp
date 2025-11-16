#include "pipe.h"
#include "station.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <algorithm>

class PipelineManager {
private:
    std::vector<Pipe> pipes;
    std::vector<Station> stations;

public:
    // Основные операции
    void addPipe() {
        Pipe pipe;
        pipe.readFromConsole();
        pipes.push_back(pipe);
        logAction("Добавлена труба ID: " + std::to_string(pipe.getId()));
    }

    void addStation() {
        Station station;
        station.readFromConsole();
        stations.push_back(station);
        logAction("Добавлена станция ID: " + std::to_string(station.getId()));
    }

    void showAll() const {
        std::cout << "\n=== ВСЕ ТРУБЫ ===\n";
        for (const auto& pipe : pipes) {
            pipe.printToConsole();
        }

        std::cout << "\n=== ВСЕ СТАНЦИИ ===\n";
        for (const auto& station : stations) {
            station.printToConsole();
        }
    }

    // Поиск труб
    void findPipes() {
        std::cout << "\nПоиск труб:\n";
        std::cout << "1 - По названию\n";
        std::cout << "2 - По статусу ремонта\n";
        std::cout << "Выберите: ";

        int choice = getIntInRange(1, 2);

        if (choice == 1) {
            std::cout << "Введите название для поиска: ";
            std::string name = getStringInput();

            bool found = false;
            for (const auto& pipe : pipes) {
                if (pipe.getName().find(name) != std::string::npos) {
                    pipe.printToConsole();
                    found = true;
                }
            }
            if (!found) std::cout << "Трубы не найдены.\n";

        }
        else {
            std::cout << "Искать трубы в ремонте? (1-да, 0-нет): ";
            bool inRepair = getYesNoInput();

            bool found = false;
            for (const auto& pipe : pipes) {
                if (pipe.isInRepair() == inRepair) {
                    pipe.printToConsole();
                    found = true;
                }
            }
            if (!found) std::cout << "Трубы не найдены.\n";
        }
    }

    // Поиск станций
    void findStations() {
        std::cout << "\nПоиск станций:\n";
        std::cout << "1 - По названию\n";
        std::cout << "2 - По проценту незадействованных\n";
        std::cout << "Выберите: ";

        int choice = getIntInRange(1, 2);

        if (choice == 1) {
            std::cout << "Введите название для поиска: ";
            std::string name = getStringInput();

            bool found = false;
            for (const auto& station : stations) {
                if (station.getName().find(name) != std::string::npos) {
                    station.printToConsole();
                    found = true;
                }
            }
            if (!found) std::cout << "Станции не найдены.\n";

        }
        else {
            std::cout << "Введите максимальный процент незадействованных: ";
            double maxPercent = getDoubleInput();

            bool found = false;
            for (const auto& station : stations) {
                if (station.getUnusedPercentage() <= maxPercent) {
                    station.printToConsole();
                    found = true;
                }
            }
            if (!found) std::cout << "Станции не найдены.\n";
        }
    }

    // Пакетное редактирование труб
    void batchEditPipes() {
        std::cout << "\nПакетное редактирование труб:\n";
        std::vector<Pipe*> pipesToEdit;

        // Поиск труб для редактирования
        std::cout << "Искать трубы:\n";
        std::cout << "1 - Все трубы\n";
        std::cout << "2 - По названию\n";
        std::cout << "3 - По статусу ремонта\n";
        std::cout << "Выберите: ";

        int choice = getIntInRange(1, 3);

        if (choice == 1) {
            for (auto& pipe : pipes) {
                pipesToEdit.push_back(&pipe);
            }
        }
        else if (choice == 2) {
            std::cout << "Введите название: ";
            std::string name = getStringInput();

            for (auto& pipe : pipes) {
                if (pipe.getName().find(name) != std::string::npos) {
                    pipesToEdit.push_back(&pipe);
                }
            }
        }
        else {
            std::cout << "В ремонте? (1-да, 0-нет): ";
            bool inRepair = getYesNoInput();

            for (auto& pipe : pipes) {
                if (pipe.isInRepair() == inRepair) {
                    pipesToEdit.push_back(&pipe);
                }
            }
        }

        if (pipesToEdit.empty()) {
            std::cout << "Трубы не найдены.\n";
            return;
        }

        std::cout << "Найдено " << pipesToEdit.size() << " труб.\n";

        // Редактирование
        std::cout << "Изменить статус ремонта для всех? (1-да, 0-нет): ";
        if (getYesNoInput()) {
            std::cout << "Установить статус 'в ремонте'? (1-да, 0-нет): ";
            bool newStatus = getYesNoInput();

            for (auto pipe : pipesToEdit) {
                pipe->setRepair(newStatus);
            }
            logAction("Пакетное изменение статуса ремонта для " +
                std::to_string(pipesToEdit.size()) + " труб");
        }
    }

    // Сохранение в файл
    void saveToFile() {
        std::cout << "Введите имя файла: ";
        std::string filename = getStringInput();

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка сохранения!\n";
            return;
        }

        // Сохраняем трубы
        file << pipes.size() << "\n";
        for (const auto& pipe : pipes) {
            pipe.saveToFile(file);
        }

        // Сохраняем станции
        file << stations.size() << "\n";
        for (const auto& station : stations) {
            station.saveToFile(file);
        }

        file.close();
        logAction("Сохранено в файл: " + filename);
        std::cout << "Данные сохранены!\n";
    }

    // Загрузка из файла
    void loadFromFile() {
        std::cout << "Введите имя файла: ";
        std::string filename = getStringInput();

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка загрузки!\n";
            return;
        }

        pipes.clear();
        stations.clear();

        // Загружаем трубы
        int pipeCount;
        file >> pipeCount;
        file.ignore();

        for (int i = 0; i < pipeCount; i++) {
            Pipe pipe;
            pipe.loadFromFile(file);
            pipes.push_back(pipe);
        }

        // Загружаем станции
        int stationCount;
        file >> stationCount;
        file.ignore();

        for (int i = 0; i < stationCount; i++) {
            Station station;
            station.loadFromFile(file);
            stations.push_back(station);
        }

        file.close();
        logAction("Загружено из файла: " + filename);
        std::cout << "Данные загружены!\n";
    }
};

void showMenu() {
    std::cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
    std::cout << "1 - Добавить трубу\n";
    std::cout << "2 - Добавить станцию\n";
    std::cout << "3 - Показать все\n";
    std::cout << "4 - Поиск труб\n";
    std::cout << "5 - Поиск станций\n";
    std::cout << "6 - Пакетное редактирование труб\n";
    std::cout << "7 - Сохранить\n";
    std::cout << "8 - Загрузить\n";
    std::cout << "0 - Выход\n";
    std::cout << "Выберите: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    PipelineManager manager;

    logAction("Программа запущена");

    while (true) {
        showMenu();
        int choice = getIntInput();

        switch (choice) {
        case 1: manager.addPipe(); break;
        case 2: manager.addStation(); break;
        case 3: manager.showAll(); break;
        case 4: manager.findPipes(); break;
        case 5: manager.findStations(); break;
        case 6: manager.batchEditPipes(); break;
        case 7: manager.saveToFile(); break;
        case 8: manager.loadFromFile(); break;
        case 0:
            logAction("Программа завершена");
            return 0;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}