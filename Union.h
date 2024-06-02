Automat Union(int id1, int id2, bool console = true) {
    Automat* aut1 = Automats[id1];
    Automat* aut2 = Automats[id2];
    int new_states = aut1->states + aut2->states + 1;
    int new_start = new_states - 1;

    std::vector<int> new_finals;
    for(auto f : aut1->finals) new_finals.push_back(f);
    for(auto f : aut2->finals) new_finals.push_back(f+aut1->states);

    std::vector<std::vector<Automat::Edge>> new_automat(new_states);
    for(int i=0;i<aut1->states;i++) {
        for(auto edge : aut1->automat[i]) {
            new_automat[i].push_back(edge);
        }
    }
    for(int i=0;i<aut2->states;i++) {
        for(auto edge : aut2->automat[i]) {
            new_automat[i+aut1->states].push_back({edge.toVertex+aut1->states, edge.label});
        }
    }
    for(auto edge : aut1->automat[aut1->start]) new_automat[new_start].push_back(edge);
    for(auto edge : aut2->automat[aut2->start]) new_automat[new_start].push_back({edge.toVertex + aut1->states, edge.label});

    if(console) std::cout<<lastInd<<std::endl;

    return *(new Automat(new_states, new_automat, new_start, new_finals));
}
