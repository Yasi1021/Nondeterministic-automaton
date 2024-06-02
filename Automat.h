int lastInd = 0;
extern std::vector<class Automat *> Automats;

class Automat
{
public:
    struct Edge
    {
        int toVertex;
        char label;
    };

private:
    int ind;
    int start;
    int states;
    std::vector<std::vector<Edge>> automat;
    std::vector<int> finals;

    std::vector<bool> visited;
    std::vector<int> visitedLoop;

    void clearVisited();
    void clearVisitedLoop();
    bool dfsCheck(int vertex);
    bool loopCheck(int vertex);

public:
    Automat(int _states, std::vector<std::vector<Edge>> _automat, int _start, std::vector<int> _finals)
    {
        states = _states;
        automat = _automat;
        start = _start;
        finals = _finals;

        ind = lastInd++;
        Automats.push_back(this);

        visited.reserve(states);
        visitedLoop.reserve(states);
    }

    Automat(const Automat &other)
    {
        *this = other;
        this->ind = lastInd++;
        Automats.push_back(this);
    }

    int get_id() { return ind; }

    friend void print(int id);
    friend bool empty(int id);
    friend bool finite(int id);
    friend bool deterministic(int id);
    friend bool recognize(int id, std::string word);
    friend Automat Union(int id1, int id2, bool console);
    friend Automat Concat(int id1, int id2, bool console);
    friend Automat Un(int id, bool console);
    friend void draw(int id,const std::string& fileName);
    friend Automat Reg(std::string regex);

    void MakeDeterministic();

    ~Automat()
    {
        Automats[this->ind] = NULL;
    }
};
std::vector<Automat *> Automats;

void Automat::clearVisited()
{
    for (int i = 0; i < states; i++)
        visited[i] = 0;
}

void Automat::clearVisitedLoop()
{
    for (int i = 0; i < states; i++)
        visitedLoop[i] = 0;
}

bool Automat::dfsCheck(int vertex)
{
    if (std::find(finals.begin(), finals.end(), vertex) != finals.end())
        return true;

    if (visited[vertex])
        return false;
    visited[vertex] = true;
    for (auto edge : automat[vertex])
    {
        if (dfsCheck(edge.toVertex))
            return true;
    }
    return false;
}

bool Automat::loopCheck(int vertex)
{
    if (visitedLoop[vertex] == 2)
        return false;
    if (visitedLoop[vertex] == 1)
    {
        clearVisited();
        if (dfsCheck(vertex))
            return true;
        else
            return false;
    }
    visitedLoop[vertex] = 1;

    for (auto edge : automat[vertex])
    {
        if (loopCheck(edge.toVertex))
            return true;
    }
    visitedLoop[vertex] = 2;
    return false;
}

#include "MakeDeterministic.h"

#include "Union.h"
#include "Concat.h"
#include "Un.h"
#include "RegularExpression.h"
#include "Draw.h"

#include "functionsAutomat.h"
