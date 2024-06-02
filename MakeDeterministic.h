void Automat::MakeDeterministic()
{
    Automat autCopy = *this;

    finals.clear();
    for (int i = 0; i < states; i++)
        automat[i].clear();
    states = 1;
    start = 0;

    std::map<std::set<int>, int> Name;
    std::set<int> Vertex[36];
    Vertex[0].insert(autCopy.start);
    bool epsilonClosed = false;
    while (!epsilonClosed)
    {
        epsilonClosed = true;
        for (auto state : Vertex[0])
        {
            for (auto edge : autCopy.automat[state])
            {
                if (edge.label == '~' && Vertex[0].find(edge.toVertex) == Vertex[0].end())
                {
                    Vertex[0].insert(edge.toVertex);
                    epsilonClosed = false;
                }
            }
        }
    }
    for (auto state : Vertex[0])
    {
        if (std::find(autCopy.finals.begin(), autCopy.finals.end(), state) != autCopy.finals.end())
        {
            finals.push_back(0);
            break;
        }
    }

    Name.insert({Vertex[0], 0});
    std::queue<std::set<int>> unprocessed;
    unprocessed.push(Vertex[0]);
    Vertex[0].clear();

    while (!unprocessed.empty())
    {
        std::set<int> curVertex = unprocessed.front();
        unprocessed.pop();

        for (auto state : curVertex)
        {
            for (auto edge : autCopy.automat[state])
            {
                if (edge.label >= '0' && edge.label <= '9')
                    Vertex[edge.label - '0'].insert(edge.toVertex);
                else if (edge.label >= 'a' && edge.label <= 'z')
                    Vertex[edge.label - 'a' + 10].insert(edge.toVertex);
            }
        }

        for (int i = 0; i < 36; i++)
        {
            if (Vertex[i].empty())
                continue;

            epsilonClosed = false;
            while (!epsilonClosed)
            {
                epsilonClosed = true;
                for (auto state : Vertex[i])
                {
                    for (auto edge : autCopy.automat[state])
                    {
                        if (edge.label == '~' && Vertex[i].find(edge.toVertex) == Vertex[i].end())
                        {
                            Vertex[i].insert(edge.toVertex);
                            epsilonClosed = false;
                        }
                    }
                }
            }

            if (Name.find(Vertex[i]) == Name.end())
            {
                Name.insert({Vertex[i], states++});
                if (automat.capacity() < states)
                    automat.reserve(states);
                unprocessed.push(Vertex[i]);

                for (auto state : Vertex[i])
                {
                    if (std::find(autCopy.finals.begin(), autCopy.finals.end(), state) != autCopy.finals.end())
                    {
                        finals.push_back(Name[Vertex[i]]);
                        break;
                    }
                }
            }

            if (i < 10)
                automat[Name[curVertex]].push_back({Name[Vertex[i]], char(i + '0')});
            else
                automat[Name[curVertex]].push_back({Name[Vertex[i]], char(i + 'a' - 10)});

            Vertex[i].clear();
        }
    }
}
