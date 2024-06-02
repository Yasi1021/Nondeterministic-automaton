Automat Reg(std::string regex) {

    auto OneEdgeAutomat = [] (std::vector<bool> labels) {
        std::vector<std::vector<Automat::Edge>> automat(2);
        for(int i=0;i<labels.size();i++) {
            if(labels[i] == 1) {
                if(i <= 9) automat[0].push_back({1, char(i+'0')});
                else automat[0].push_back({1, char(i-10+'a')});
            }
        }

         return Automat(2, automat, 0, {1});
    };

    auto EmptyWordAut = []() {
        std::vector<std::vector<Automat::Edge>> automat(2);
        automat[0].push_back({1, '~'});
        return  Automat(2, automat, 0, {1});
    };

    std::stack<Automat> stackID;


    stackID.push(Automat(0, {}, -1, {}));

    for(int i=0;i<regex.size();i++) {
        if(regex[i] == '(') {
            stackID.push(Automat(0, {}, -1, {}));
        }
        else if(regex[i] == ')') {
            if(i+1 < regex.size()) {
            if(regex[i+1] == '+') {
                Automat un = Un(stackID.top().ind, false);
                stackID.pop();
                stackID.push(un);
                i++;
            }
            else if(regex[i+1] == '*') {
                Automat emptyword = EmptyWordAut();
                Automat un = Un(stackID.top().ind, false);
                Automat unionn = Union(emptyword.ind, un.ind, false);
                stackID.pop();
                stackID.push(unionn);
                i++;
            }
            }

            Automat last = stackID.top();
            stackID.pop();
            if(!stackID.empty() && stackID.top().start != -1) {
                Automat concat = Concat(stackID.top().ind, last.ind, false);
                stackID.pop();
                stackID.push(concat);
            }
            else {
                stackID.push(last);
            }
        }
        else {
        std::vector<bool> labels(36);
        if(regex[i] == '[') {
            i++;
            while(regex[i] != ']') {
                if(regex[i] >= 'a' && regex[i] <= 'z') {
                    labels[regex[i]-'a'+10] = 1;
                    if(regex[i+1] == '-') {
                        for(int j=regex[i]-'a'+10;j<=regex[i+2]-'a'+10;j++) labels[j] = 1;
                        i+= 2;
                    }
                }
                else if(regex[i] >= '0' && regex[i] <= '9') {
                    labels[regex[i]-'0'] = 1;
                    if(regex[i+1] == '-') {
                        for(int j=regex[i]-'0';j<=regex[i+2]-'0';j++) labels[j] = 1;
                        i+=2;
                    }
                }
                i++;
            }
        }
        else if(regex[i] >= 'a' && regex[i] <= 'z') labels[regex[i]-'a'+10] = 1;
        else if(regex[i] >= '0' && regex[i] <= '9') labels[regex[i]-'0'] = 1;

        Automat oneedge = OneEdgeAutomat(labels);

        if(stackID.top().start != -1) {
            Automat concat = Concat(stackID.top().ind, oneedge.ind, false);
            stackID.pop();
            stackID.push(concat);
        }
        else {
            stackID.pop();
            stackID.push(oneedge);
        }
        }
    }

    Automat* result = new Automat(stackID.top());

    std::cout<<result->ind<<std::endl;

    return *result;
}

