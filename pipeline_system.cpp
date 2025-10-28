#include "pipeline_system.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void PipelineSystem::addPipe() {
    setlocale(LC_ALL, "RU");
    pipe newPipe;
    std::cin >> newPipe;
    pipes[newPipe.GetId()] = newPipe;
    std::cout << "Труба успешно добавлена! ID: " << newPipe.GetId() << std::endl;
}

void PipelineSystem::addStation() {
    setlocale(LC_ALL, "RU");
    cs newStation;
    std::cin >> newStation;
    stations[newStation.GetId()] = newStation;
    std::cout << "КС успешно добавлена! ID: " << newStation.GetId() << std::endl;
}

void PipelineSystem::showAllObjects() const {
    showPipes();
    showStations();
}

void PipelineSystem::showPipes() const {
    setlocale(LC_ALL, "RU");
    std::cout << "\n=== ТРУБЫ ===" << std::endl;
    if (pipes.empty()) {
        std::cout << "Трубы отсутствуют." << std::endl;
        return;
    }
    for (const auto& p : pipes) {
        std::cout << p.second << std::endl;
    }
}

void PipelineSystem::showStations() const {
    setlocale(LC_ALL, "RU");
    std::cout << "\n=== КОМПРЕССОРНЫЕ СТАНЦИИ ===" << std::endl;
    if (stations.empty()) {
        std::cout << "Станции отсутствуют." << std::endl;
        return;
    }
    for (const auto& s : stations) {
        std::cout << s.second << std::endl;
    }
}

void PipelineSystem::editPipe() {
    setlocale(LC_ALL, "RU");
    showPipes();
    if (pipes.empty()) return;

    int id = getIntegerInput("Введите ID трубы для редактирования: ", 1, 1000);

    if (pipeExists(id)) {
        std::cin >> pipes[id];
        std::cout << "Труба успешно обновлена!" << std::endl;
    }
    else {
        std::cout << "Труба с ID " << id << " не найдена." << std::endl;
    }
}

void PipelineSystem::editStation() {
    setlocale(LC_ALL, "RU");
    showStations();
    if (stations.empty()) return;

    int id = getIntegerInput("Введите ID станции для редактирования: ", 1, 1000);

    if (stationExists(id)) {
        std::cin >> stations[id];
        std::cout << "Станция успешно обновлена!" << std::endl;
    }
    else {
        std::cout << "Станция с ID " << id << " не найдена." << std::endl;
    }
}

void PipelineSystem::deleteObject() {
    setlocale(LC_ALL, "RU");
    std::cout << "Удалить:\n1. Трубу\n2. Станцию\n";
    int choice = getIntegerInput("Выберите: ", 1, 2);

    if (choice == 1) {
        showPipes();
        if (pipes.empty()) return;

        int id = getIntegerInput("Введите ID трубы для удаления: ", 1, 1000);
        if (pipes.erase(id)) {
            std::cout << "Труба успешно удалена!" << std::endl;
        }
        else {
            std::cout << "Труба не найдена." << std::endl;
        }
    }
    else {
        showStations();
        if (stations.empty()) return;

        int id = getIntegerInput("Введите ID станции для удаления: ", 1, 1000);
        if (stations.erase(id)) {
            std::cout << "Станция успешно удалена!" << std::endl;
        }
        else {
            std::cout << "Станция не найдена." << std::endl;
        }
    }
}

void PipelineSystem::findPipes() {
    setlocale(LC_ALL, "RU");
    std::cout << "Поиск труб по:\n1. Названию\n2. Статусу ремонта\n3. Обоим параметрам\n";
    int choice = getIntegerInput("Выберите: ", 1, 3);

    std::vector<pipe*> results;
    std::string nameFilter;
    bool repairFilter;
    bool useRepairFilter = false;

    if (choice == 1 || choice == 3) {
        nameFilter = getStringInput("Введите название для поиска: ");
        auto byName = findPipesByName(nameFilter);
        results.insert(results.end(), byName.begin(), byName.end());
    }

    if (choice == 2 || choice == 3) {
        repairFilter = getYesNoInput("В ремонте?");
        useRepairFilter = true;
        auto byRepair = findPipesByRepairStatus(repairFilter);

        if (choice == 2) {
            results = byRepair;
        }
        else {
            // Пересечение для "оба параметра"
            std::vector<pipe*> intersection;
            for (auto p : results) {
                if (p->GetInRepair() == repairFilter) {
                    intersection.push_back(p);
                }
            }
            results = intersection;
        }
    }

    std::cout << "\nНайдено " << results.size() << " труб:" << std::endl;
    for (auto p : results) {
        std::cout << *p << std::endl;
    }

    if (!results.empty() && getYesNoInput("Выполнить пакетное редактирование этих труб?")) {
        editPipeBatch(results);
    }
}

void PipelineSystem::findStations() {
    setlocale(LC_ALL, "RU");
    std::cout << "Поиск станций по:\n1. Названию\n2. Проценту незадействованных цехов\n";
    int choice = getIntegerInput("Выберите: ", 1, 2);

    std::vector<cs*> results;

    if (choice == 1) {
        std::string nameFilter = getStringInput("Введите название для поиска: ");
        results = findStationsByName(nameFilter);
    }
    else {
        double maxPercentage = getDoubleInput("Введите максимальный процент незадействованных цехов: ", 0, 100);
        results = findStationsByUnusedPercentage(maxPercentage);
    }

    std::cout << "\nНайдено " << results.size() << " станций:" << std::endl;
    for (auto s : results) {
        std::cout << *s << std::endl;
    }
}

void PipelineSystem::batchEditPipes() {
    setlocale(LC_ALL, "RU");
    std::cout << "Пакетное редактирование:\n1. Все трубы\n2. Выбранные трубы\n";
    int choice = getIntegerInput("Выберите: ", 1, 2);

    std::vector<pipe*> pipesToEdit;

    if (choice == 1) {
        for (auto& p : pipes) {
            pipesToEdit.push_back(&p.second);
        }
    }
    else {
        showPipes();
        if (pipes.empty()) return;

        std::string input = getStringInput("Введите ID труб через пробел: ");
        std::stringstream ss(input);
        int id;

        while (ss >> id) {
            if (pipeExists(id)) {
                pipesToEdit.push_back(&pipes[id]);
            }
        }
    }

    editPipeBatch(pipesToEdit);
}

void PipelineSystem::saveToFile() {
    setlocale(LC_ALL, "RU");
    std::string filename = getStringInput("Введите имя файла для сохранения: ");
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
        filename += ".txt";
    }

    std::ofstream out(filename);
    if (out.is_open()) {
        out << pipes.size() << std::endl;
        for (const auto& p : pipes) {
            out << p.second.GetId() << std::endl;
            out << p.second.GetName() << std::endl;
            out << p.second.GetLength() << std::endl;
            out << p.second.GetDiameter() << std::endl;
            out << p.second.GetInRepair() << std::endl;
        }

        out << stations.size() << std::endl;
        for (const auto& s : stations) {
            out << s.second.GetId() << std::endl;
            out << s.second.GetName() << std::endl;
            out << s.second.GetNumFac() << std::endl;
            out << s.second.GetNumWorkFac() << std::endl;
            out << s.second.GetEff() << std::endl;
        }

        std::cout << "Данные сохранены в файл " << filename << std::endl;
    }
    else {
        std::cout << "Ошибка сохранения файла!" << std::endl;
    }
}

void PipelineSystem::loadFromFile() {
    setlocale(LC_ALL, "RU");
    std::string filename = getStringInput("Введите имя файла для загрузки: ");
    if (filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") {
        filename += ".txt";
    }

    std::ifstream in(filename);
    if (in.is_open()) {
        pipes.clear();
        stations.clear();

        int pipeCount;
        in >> pipeCount;
        in.ignore();

        for (int i = 0; i < pipeCount; i++) {
            int id, length, diameter;
            std::string name;
            bool inRepair;

            in >> id;
            in.ignore();
            getline(in, name);
            in >> length >> diameter >> inRepair;
            in.ignore();

            pipe p(name, length, diameter, inRepair);
            pipes[id] = p;
        }

        int stationCount;
        in >> stationCount;
        in.ignore();

        for (int i = 0; i < stationCount; i++) {
            int id, numFac, numWorkFac, eff;
            std::string name;

            in >> id;
            in.ignore();
            getline(in, name);
            in >> numFac >> numWorkFac >> eff;
            in.ignore();

            cs s(name, numFac, numWorkFac, eff);
            stations[id] = s;
        }

        std::cout << "Данные загружены из файла " << filename << std::endl;
    }
    else {
        std::cout << "Ошибка загрузки файла!" << std::endl;
    }
}

// Приватные методы
std::vector<pipe*> PipelineSystem::findPipesByName(const std::string& name) {
    std::vector<pipe*> results;
    for (auto& p : pipes) {
        if (p.second.GetName().find(name) != std::string::npos) {
            results.push_back(&p.second);
        }
    }
    return results;
}

std::vector<pipe*> PipelineSystem::findPipesByRepairStatus(bool inRepair) {
    std::vector<pipe*> results;
    for (auto& p : pipes) {
        if (p.second.GetInRepair() == inRepair) {
            results.push_back(&p.second);
        }
    }
    return results;
}

std::vector<cs*> PipelineSystem::findStationsByName(const std::string& name) {
    std::vector<cs*> results;
    for (auto& s : stations) {
        if (s.second.GetName().find(name) != std::string::npos) {
            results.push_back(&s.second);
        }
    }
    return results;
}

std::vector<cs*> PipelineSystem::findStationsByUnusedPercentage(double maxPercentage) {
    std::vector<cs*> results;
    for (auto& s : stations) {
        if (s.second.GetUnusedPercentage() <= maxPercentage) {
            results.push_back(&s.second);
        }
    }
    return results;
}

void PipelineSystem::editPipeBatch(const std::vector<pipe*>& pipesToEdit) {
    setlocale(LC_ALL, "RU");
    if (pipesToEdit.empty()) return;

    std::cout << "Пакетное редактирование " << pipesToEdit.size() << " труб:" << std::endl;

    // Редактирование названия
    if (getYesNoInput("Изменить название для всех труб?")) {
        std::string newName = getStringInput("Введите новое название: ");
        for (auto p : pipesToEdit) {
            p->SetName(newName);
        }
    }

    // Редактирование статуса ремонта
    if (getYesNoInput("Изменить статус ремонта для всех труб?")) {
        bool newStatus = getYesNoInput("Установить статус ремонта 'да'?");
        for (auto p : pipesToEdit) {
            p->SetInRepair(newStatus);
        }
    }

    std::cout << "Пакетное редактирование завершено!" << std::endl;
}

bool PipelineSystem::pipeExists(int id) const {
    return pipes.find(id) != pipes.end();
}

bool PipelineSystem::stationExists(int id) const {
    return stations.find(id) != stations.end();
}