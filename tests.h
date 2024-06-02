void TestDeterministic() {
    FileManager file;
    file.open("tests/aut2.txt");

    int id = lastInd - 1;
    draw(id, "visualization/automat.dot");

    if(deterministic(id)) {
        std::cout << "The Automaton is deterministic " << std::endl;
    }
    else {
        std::cout << "The Automaton is nondeterministic " << std::endl;
    }

    Automats[id]->MakeDeterministic();
    draw(id, "visualization/deterministic.dot");

    if(deterministic(id)) {
        std::cout << "The Automaton is now deterministic " << std::endl;
    }
    else {
        std::cout << "The Automaton is now nondeterministic " << std::endl;
    }

    delete Automats[id];
}

void TestDeterministicWithEpsilonTranzitions() {

    FileManager file;
    file.open("tests/aut3.txt");

    int id = lastInd-1;

    draw(id, "visualization/automat.dot");

    if(deterministic(id)) {
        std::cout << "The Automaton is deterministic " << std::endl;
    }
    else {
        std::cout << "The Automaton is nondeterministic " << std::endl;
    }

    Automats[id]->MakeDeterministic();
    draw(id, "visualization/deterministic.dot");

    if(deterministic(id)) {
        std::cout << "The Automaton is now deterministic " << std::endl;
    }
    else {
        std::cout << "The Automaton is now nondeterministic " << std::endl;
    }

    delete Automats[id];
}

void TestFunctions() {
// Tests empty(), finnite(), print() and list()
    FileManager file;

    file.open("tests/aut1.txt");

    int id = lastInd-1;
    std::vector<int> list1 = list();
    draw(id, "visualization/automatFunctions.dot");

    if(empty(id)) {
        std::cout << "The language is empty" << std::endl;
    }
    else {
        std::cout << "The language is not empty" << std::endl;
    }

    if(finite(id)) {
        std::cout << "The language is finite" << std::endl;
    }
    else {
        std::cout << "The language is infinite" << std::endl;
    }

    delete Automats[id];

    file.open("tests/aut4.txt");

    id = lastInd-1;
    std::vector<int> list2 = list();
    draw(id, "visualization/automatFunctions2.dot");

    if(empty(id)) {
        std::cout << "The language is empty" << std::endl;
    }
    else {
        std::cout << "The language is not empty" << std::endl;
    }

    if(finite(id)) {
        std::cout << "The language is finite" << std::endl;
    }
    else {
        std::cout << "The language is infinite" << std::endl;
    }

    print(id);

    std::cout<<"List of ids after reading the first automaton:"<<std::endl;
    for(auto state : list1) {
        std::cout<<state<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"List of ids after reading the second automaton:"<<std::endl;
    for(auto state : list2) {
        std::cout<<state<<" ";
    }
    std::cout<<std::endl;

    delete Automats[id];
}

void TestRecognize() {
    FileManager file;
    file.open("tests/N(a)=N(b).txt");

    int id = lastInd-1;
    if(recognize(id, "bbabababba")) {
        std::cout<<"The word bbabababba is recognized"<<std::endl;
    }
    else {
        std::cout<<"The word bbabababba is not recognized"<<std::endl;
    }

    if(recognize(id, "baabba")) {
        std::cout<<"The word baabba is recognized"<<std::endl;
    }
    else {
        std::cout<<"The word baabba is not recognized"<<std::endl;
    }

    if(recognize(id, "aabbabab")) {
        std::cout<<"The word aabbabab is recognized"<<std::endl;
    }
    else {
        std::cout<<"The word aabbabab is not recognized"<<std::endl;
    }

    draw(id, "visualization/N(a)=N(b).dot");

    delete Automats[id];
}

void TestRegularExpression() {
    Reg("[hg](18g)*[g7-9](a)+");

    std::vector<int> allIds = list();
    int id = allIds[allIds.size()-1];
    draw(id, "visualization/regular.dot");

    delete Automats[id];
}

void TestUn() {
    FileManager file;

    file.open("tests/ending-ab.txt");
    int id = lastInd-1;
    Un(id);
    draw(id, "visualization/ending-ab.dot");
    draw(id+1, "visualization/un.dot");

    delete Automats[id];
    delete Automats[id+1];
}

void TestConcat() {
    FileManager file;
    file.open("tests/ending-ab.txt");
    file.open("tests/containing-aa.txt");
    int id1 = lastInd-2, id2 = lastInd-1;
    draw(id1, "visualization/ending-ab.dot");
    draw(id2, "visualization/containing-aa.dot");

    Concat(id1, id2);
    std::vector<int> allIds = list();
    int id = allIds[allIds.size()-1];
    draw(id, "visualization/concat.dot");

    delete Automats[id];
    delete Automats[id1];
    delete Automats[id2];
}

void TestUnion() {
    FileManager file;
    file.open("tests/ending-ab.txt");
    file.open("tests/containing-aa.txt");
    int id1 = lastInd-2, id2 = lastInd-1;
    draw(id1, "visualization/ending-ab.dot");
    draw(id2, "visualization/containing-aa.dot");

    Union(id1, id2);
    std::vector<int> allIds = list();
    int id = allIds[allIds.size()-1];
    draw(id, "visualization/union.dot");

    delete Automats[id];
    delete Automats[id1];
    delete Automats[id2];
}
