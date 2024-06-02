void draw(int id, const std::string& fileName)
{
    std::ofstream file(fileName);

    file << "digraph A { \n";

    Automat* aut = Automats[id];

    file << aut->start << "[ shape = \"box\" ];" << std::endl;

    for(auto f : aut->finals) {
        file << f << "[ shape = \"septagon\" ];" << std::endl;
    }

    for(int st=0;st<aut->states;st++) {
        for(auto edge : aut->automat[st]) {
            file << st << " -> " << edge.toVertex;
            if(edge.label != '~') file << "[ label = \"" << edge.label << " \"]";
            file << ";" << std::endl;
        }
    }

    file << " } \n";
}

