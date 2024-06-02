Automat Un(int id, bool console = true) {
    Automat* aut = Automats[id];

    int new_start = aut->start;
    int new_states = aut->states;
    std::vector<int> new_finals = aut->finals;
    std::vector<std::vector<Automat::Edge>> new_automat = aut->automat;

    for(auto f : aut->finals) {
        for(auto edge : aut->automat[aut->start]) {
            new_automat[f].push_back(edge);
        }
    }

    if(console) std::cout<<lastInd<<std::endl;

    return *(new Automat(new_states, new_automat, new_start, new_finals));
}
