#include "Automat.h"

class FileManager
{
private:
    std::string fileDirectory = "";
    std::string fileName = "";
    std::string getFileNameFromDir(const std::string& fileDirectory) const;
    void rewrite(const std::string& fileDir) const;

public:
    std::string open(const std::string& fileDirectory);
    std::string close();
    std::string save() const;
    std::string saveAs(const std::string& fileDirectory) const;

};

std::string FileManager::getFileNameFromDir(const std::string& fileDirectoryName) const
{
    size_t lastpos = fileDirectoryName.find_last_of("/\\");
    if (lastpos == std::string::npos) return fileDirectoryName;

    return fileDirectoryName.substr(lastpos+1);
}

std::string FileManager::close()
{
    fileDirectory = "";
    std::string result = fileName + "Closed\n";
    fileName = "";
    return result;
}

std::string FileManager::saveAs(const std::string& fileDir) const
{
    std::ofstream file(fileDir);
    if (!file.is_open()) throw std::runtime_error("File is not open\n");
    rewrite(fileDir);
    file.close();
    return getFileNameFromDir(fileDir)+"Saved\n";
}

std::string FileManager::save() const
{
    saveAs(fileDirectory);
    return "Saved\n";
}

std::string FileManager::open(const std::string& fileDir)
{
    fileDirectory = fileDir;
    fileName = getFileNameFromDir(fileDirectory);
    std::ifstream file(fileDirectory);
    if (!file.is_open())
        throw std::runtime_error(fileName + "error opening this file");
    std::string line;

    int states, edges;
    std::getline(file, line, ' ');
    states = stoi(line);
    std::getline(file, line);
    edges = stoi(line);

    std::vector<std::vector<Automat::Edge>> automat(states);
    for(int i=0;i<edges;i++) {
        int from, to;
        char label;
        std::getline(file, line, ' ');
        from = stoi(line);
        std::getline(file, line, ' ');
        label = line[0];
        std::getline(file, line);
        to = stoi(line);

        automat[from].push_back({to, label});
    }
    int start;
    std::vector<int> finals;

    std::getline(file, line);
    start = stoi(line);

    while(std::getline(file, line, ' ')) {
        finals.push_back(stoi(line));
    }

    Automat* newAutomat = new Automat(states, automat, start, finals);

    std::cout << newAutomat->get_id() << std::endl;

    file.close();

    return fileName + "Opened\n";
}

void FileManager::rewrite(const std::string& fileDir) const
{
    std::ofstream file(fileDir);

    int states, edges;
    std::cin >> states >> edges;

    file << states << " " << edges << std::endl;

    for (int i = 0; i < edges; i++)
    {
        int from, to;
        char label;
        std::cin >> from >> label >> to;
        file << from << " "  << label << " " << to << std::endl;
    }

    int start, finals;
    std::cin >> start;
    file << start << std::endl;
    while(std::cin >> finals) {
        file << finals << " ";
    }

    file.close();

}

