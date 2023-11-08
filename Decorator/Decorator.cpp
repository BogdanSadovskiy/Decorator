using namespace std;
#include <iostream>
#include <string>
class MESSAGE {
protected:
    string txt;
    string setting;
public:
    MESSAGE() { txt = ""; }
    MESSAGE(string txt) {
        this->txt = txt;
        this->setting = "Defailt";
    }
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

//class TXTMessageEdited : public MESSAGE{
//public:
//    TXTMessageEdited(string str) {
//        this->txt = str;
//    }
//    TXTMessageEdited(TXTMessageEdited* tmp) {
//        this->txt = tmp->getMessage();
//        this->setting = tmp->getSetting();
//    }
//};

class Decorator {
protected:
    string txt;
    string setting;
    virtual void operation() {};
public:
    Decorator(MESSAGE*& message) {
        this->txt = message->getMessage();
        this->setting = message->getSetting();
    };
    Decorator(Decorator* decorator) {
        this->txt = decorator->txt;
        this->setting = decorator->setting;
    };
    string getMessage() { return txt; }
    string getSetting() { return setting; }
};

class UppercaseDecorator: public Decorator {
private:
    void operation() override {

        string str = this->txt;
        for (int i = 0; str[i] != '\0'; i++) {
            if ((int)str[i] > 96 && (int)str[i] < 123) {
                str[i] = (int)str[i] - 32;
            }
        }
        this->txt = str;
        this->setting = "EDITED BY UPPERCASING";
    }
public:

    UppercaseDecorator(MESSAGE*& message) : Decorator(message){
        operation();
    }
    UppercaseDecorator(Decorator* decorator) : Decorator(decorator) {
        operation();
    }
};

class NONNumberDecorator : public Decorator {
private:
    void operation() override {

        string str = this->txt;
        string str_;
        for (int i = 0; str[i] != '\0'; i++) {
            if ((int)str[i] > 47 && (int)str[i] < 58) {
                continue;
            }
            str_.push_back(str[i]);
        }
        this->txt = str_;
        this->setting = "EDITED BY DELETING NUMBERS";
    }
public:
    NONNumberDecorator(MESSAGE*& message) : Decorator(message) {
        operation();
    }

    NONNumberDecorator(Decorator* decorator) : Decorator(decorator) {
        operation();
    }
};

class FrameDEcorator : public Decorator {
private:
    void operation() override {

        string str = this->txt;
        int iterator = str.size();
        int i = 0;
        string str_ = "+";
        str.resize(iterator * 3);
        for (i = 0; i != iterator; i++) {
            str_.push_back('-');
        }
        str_ += "+\n|";
        for (int ii = 0; str[ii] != '\0'; ii++) {
            str_.push_back(str[ii]);
        }
        str_ += "|\n+";
        for (int i = 0; i != iterator; i++) {
            str_.push_back('-');
        }
        str_ += "+";
        this->txt = str_;
        this->setting = "EDITED BY FRAMING";
    }
public:
    FrameDEcorator(MESSAGE*& message) : Decorator(message) {
        operation();
    }
    FrameDEcorator(Decorator* decorator) : Decorator(decorator) {
        operation();
    }
};
int main()
{
    cout << "Input message:\n";
    string str; 
    getline(cin, str);
    MESSAGE*  defaultMessage = new MESSAGE(str);
    Decorator* Uppercase = new UppercaseDecorator(defaultMessage);
    Decorator* NonNumbers = new NONNumberDecorator(Uppercase);
    Decorator* Frame = new FrameDEcorator(NonNumbers);

    system("cls");
    cout << "Message:\n";
    cout << defaultMessage->getMessage() << endl << endl;

    cout << Uppercase->getSetting()<< endl;
    cout << Uppercase->getMessage() << endl << endl;

    cout << NonNumbers->getSetting() << endl;
    cout << NonNumbers->getMessage() << endl << endl;

    cout << Frame->getSetting() << endl;
    cout << Frame->getMessage() << endl << endl;
 }

