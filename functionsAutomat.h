std::vector<int> list()
{
    std::vector<int> allInd;
    for (int i = 0; i < lastInd; i++) {
        if(Automats[i] != NULL)
            allInd.push_back(i);
    }
    return allInd;
}

void print(int id)
{
    Automat *aut = Automats[id];

    std::cout << "The transitions in automaton with id " << id << " are: " <<std::endl;

    for (int i = 0; i < aut->states; i++)
    {
        for (auto edge : aut->automat[i])
            std::cout << i << " --> " << edge.label << " --> " << edge.toVertex << std::endl;
    }
}

bool empty(int id)
{
    Automat *aut = Automats[id];
    aut->clearVisited();
    return !(aut->dfsCheck(aut->start));
}

bool finite(int id)
{
    Automat *aut = Automats[id];
    aut->clearVisitedLoop();
    return !(aut->loopCheck(aut->start));
}

bool deterministic(int id)
{
    Automat *aut = Automats[id];

    std::vector<bool> labels(36);
    int hesh = 0;

    for (int i = 0; i < aut->states; i++)
    {
        std::fill(labels.begin(), labels.end(), 0);
        for (auto edge : aut->automat[i])
        {
            if (edge.label == '~')
                return false;
            if (edge.label >= '0' && edge.label <= '9')
                hesh = edge.label - '0';
            else
                hesh = edge.label - 'a' + 10;

            if (labels[hesh])
                return false;
            labels[hesh] = true;
        }
    }

    return true;
}

bool recognize(int id, std::string word)
{
    Automat *aut = Automats[id];

    std::set<int> curStates;
    curStates.insert(aut->start);
    for (auto edge : aut->automat[aut->start])
    {
        if (edge.label == '~')
            curStates.insert(edge.toVertex);
    }

    for (auto letter : word)
    {
        std::set<int> newStates;
        for (auto state : curStates)
        {
            for (auto edge : aut->automat[state])
            {
                if (edge.label == letter)
                    newStates.insert(edge.toVertex);
            }
        }
        curStates = newStates;

        for (auto state : curStates)
        {
            for (auto edge : aut->automat[state])
            {
                if (edge.label == '~')
                    curStates.insert(edge.toVertex);
            }
        }
    }

    for (auto state : curStates)
    {
        if (std::find(aut->finals.begin(), aut->finals.end(), state) != aut->finals.end())
            return true;
    }

    return false;
}
