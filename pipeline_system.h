#pragma once
#include "pipe.h"
#include "cs.h"
#include <map>
#include <vector>
#include <string>

class PipelineSystem {
private:
    std::map<int, pipe> pipes;
    std::map<int, cs> stations;

public:
    void addPipe();
    void addStation();
    void showAllObjects() const;
    void editPipe();
    void editStation();
    void deleteObject();
    void findPipes();
    void findStations();
    void batchEditPipes();
    void saveToFile();
    void loadFromFile();

private:
    void showPipes() const;
    void showStations() const;
    std::vector<pipe*> findPipesByName(const std::string& name);
    std::vector<pipe*> findPipesByRepairStatus(bool inRepair);
    std::vector<cs*> findStationsByName(const std::string& name);
    std::vector<cs*> findStationsByUnusedPercentage(double maxPercentage);
    void editPipeBatch(const std::vector<pipe*>& pipesToEdit);
    bool pipeExists(int id) const;
    bool stationExists(int id) const;
};