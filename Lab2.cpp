#include <iostream>
#include "pipeline_system.h"
#include "utils.h"
#include "logger.h"
#include <limits>

void showMenu() {
    std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ТРУБОПРОВОДАМИ ===" << std::endl;
    std::cout << "1. Добавить трубу" << std::endl;
    std::cout << "2. Добавить компрессорную станцию" << std::endl;
    std::cout << "3. Показать все объекты" << std::endl;
    std::cout << "4. Редактировать трубу" << std::endl;
    std::cout << "5. Редактировать станцию" << std::endl;
    std::cout << "6. Удалить объект" << std::endl;
    std::cout << "7. Найти трубы" << std::endl;
    std::cout << "8. Найти станции" << std::endl;
    std::cout << "9. Пакетное редактирование труб" << std::endl;
    std::cout << "10. Сохранить в файл" << std::endl;
    std::cout << "11. Загрузить из файла" << std::endl;
    std::cout << "0. Выход" << std::endl;
}

int main() {
    Logger::getInstance().log("Программа запущена");

    PipelineSystem system;
    int choice;

    do {
        showMenu();
        choice = getIntegerInput("Выберите действие: ", 0, 11);

        switch (choice) {
        case 1:
            Logger::getInstance().logAction("Добавление трубы");
            system.addPipe();
            break;
        case 2:
            Logger::getInstance().logAction("Добавление станции");
            system.addStation();
            break;
        case 3:
            Logger::getInstance().logAction("Просмотр всех объектов");
            system.showAllObjects();
            break;
        case 4:
            Logger::getInstance().logAction("Редактирование трубы");
            system.editPipe();
            break;
        case 5:
            Logger::getInstance().logAction("Редактирование станции");
            system.editStation();
            break;
        case 6:
            Logger::getInstance().logAction("Удаление объекта");
            system.deleteObject();
            break;
        case 7:
            Logger::getInstance().logAction("Поиск труб");
            system.findPipes();
            break;
        case 8:
            Logger::getInstance().logAction("Поиск станций");
            system.findStations();
            break;
        case 9:
            Logger::getInstance().logAction("Пакетное редактирование труб");
            system.batchEditPipes();
            break;
        case 10:
            Logger::getInstance().logAction("Сохранение в файл");
            system.saveToFile();
            break;
        case 11:
            Logger::getInstance().logAction("Загрузка из файла");
            system.loadFromFile();
            break;
        case 0:
            Logger::getInstance().log("Программа завершена");
            std::cout << "До свидания!" << std::endl;
            break;
        }

    } while (choice != 0);

    return 0;
}