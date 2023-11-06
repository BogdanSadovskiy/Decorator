using namespace std;
#include <iostream>
#include <string>
class MESSAGE {
protected:
    string txt;
    string setting = "Default";
public:
    MESSAGE() { txt = ""; }
    void setMessage(string txt) {
        this->txt = txt;
    }
    string getMessage(){
        return this->txt;
    }
    void setSetting(string setting) {
        this->setting = setting;
    };
    string getSetting() {
        return setting;
    }
};

class TXTMessageEdited : public MESSAGE{
public:
    TXTMessageEdited(string str) {
        this->txt = str;
    }
    TXTMessageEdited(TXTMessageEdited* tmp) {
        this->txt = tmp->getMessage();
        this->setting = tmp->getSetting();
    }
};

class Decorator {
protected:
    virtual void operation(TXTMessageEdited*& tmp) = 0{}
};

class UppercaseDecorator: public Decorator {
public:
    void operation(TXTMessageEdited*& tmp) override {
       
        string str = tmp->getMessage();
        for (int i = 0; str[i] != '\0'; i++) {
            if ((int)str[i] > 96 && (int)str[i] < 123) {
                str[i] = (int)str[i] - 32;
            }
        }
        tmp->setMessage(str);
        tmp->setSetting("EDITED BY UPPERCASING");
    }
};

class NONNumberDecorator : public Decorator {
public:
    void operation(TXTMessageEdited*& tmp) override {
       
        string str = tmp->getMessage();
        string str_;
        for (int i = 0; str[i] != '\0'; i++) {
            if ((int)str[i] > 47 && (int)str[i] < 58) {
                continue;
            }
            str_.push_back(str[i]);
        }
        tmp->setMessage(str_);
        tmp->setSetting("EDITED BY DELETING NUMBERS");
    }
};

class FrameDEcorator : public Decorator {
public:
    void operation(TXTMessageEdited*& tmp) override {
      
        string str = tmp->getMessage();                         
        int iterator = str.size();
        int i = 0;
        string str_ = "+";
        str.resize(iterator * 3);
        for (i = 0; i != iterator; i++) {
            str_.push_back('-');
        }
        str_+= "+\n|"; 
        for (int ii = 0; str[ii] != '\0'; ii++) {
            str_.push_back(str[ii]);
        }
        str_ += "|\n+";
        for (int i = 0; i != iterator; i++) {
            str_.push_back ( '-');
        }
        str_+= "+";
        tmp->setMessage(str_);
        tmp->setSetting("EDITED BY FRAMING");
    }
};
int main()
{
    cout << "Input message:\n";
    string str; 
    getline(cin, str);
    TXTMessageEdited*  defaultMessage = new TXTMessageEdited(str);
    TXTMessageEdited* Uppercase = new TXTMessageEdited(defaultMessage);

    UppercaseDecorator().operation(Uppercase);

    TXTMessageEdited* NonNUmber = new TXTMessageEdited(defaultMessage);
    NONNumberDecorator().operation(NonNUmber);

    TXTMessageEdited* Framed = new TXTMessageEdited(defaultMessage);
    FrameDEcorator().operation(Framed);

    system("cls");

    cout << defaultMessage->getSetting()<<endl;
    cout << defaultMessage->getMessage()<<endl<<endl;

    cout << Uppercase->getSetting() << endl;
    cout << Uppercase->getMessage() << endl << endl;

    cout << NonNUmber->getSetting() << endl;
    cout << NonNUmber->getMessage() << endl << endl;
    cout << Framed->getSetting() << endl;
    cout << Framed->getMessage() << endl;

 }

