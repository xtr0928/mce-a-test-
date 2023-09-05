#pragma GCC optimize(2)
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<ctime>
#include"mce(1).cpp"
using namespace std;

map<string, number> variables;

// 分割字符串
vector<string> split(const string &str, char delimiter){
    vector<string> res;
    string prm;
    for(char c:str){
        if(c == delimiter){
            if(!prm.empty()){
                res.push_back(prm);
                prm = "";
            }
        }else{
            prm.push_back(c);
        }
    }
    if(!prm.empty()){
        res.push_back(prm);
    }
    return res;
}

bool is_valid_name(string str){
    for(char c:str){
        if(!isalpha(c)){
            return false;
        }
    }
    return true;
}

bool get_number(string str, number &num){
    // 判断是变量名还是数字
    if(is_valid_name(str)){
        if(!variables.count(str)){
            return false;
        }
        num = variables[str];
    }else if(!parse_number(str, num)){
        return false;
    }
    return true;
}

void print_variables(){
    for(const auto& itm:variables){
        cout<<itm.first<<" = ";
        print(itm.second);
        cout<<endl;
    }
}

int main() {
    cout<<"High-precision calculator"<<endl;
    while(true){
        // 读指令
        string line;
        cout<<"> ";
        getline(cin, line);
        vector<string> params = split(line, ' ');
        if(params.empty()){
            cout<<"Invalid input"<<endl;
        }
        if(params[0] == "help"){
            cout<<"number a = b"<<endl;
            cout<<"\ta should be a variable name (only alphabet), and b should be a variable name or a number"<<endl;
            cout<<endl;
            cout<<"print a"<<endl;
            cout<<"\ta should be a variable name"<<endl;
            cout<<endl;
            cout<<"listv"<<endl;
            cout<<"\tList all variables in memory"<<endl;
            cout<<endl;
            cout<<"add a b"<<endl;
            cout<<"\ta and b should be a variable name or a number"<<endl;
            cout<<endl;
            cout<<"multiply a b"<<endl;
            cout<<"\ta and b should be a variable name or a number"<<endl;
            cout<<endl;
            cout<<"divide a b"<<endl;
            cout<<"\ta and b should be a variable name or a number"<<endl;
            cout<<endl;
            cout<<"exit"<<endl;
            cout<<"\tExit the program"<<endl;
            cout<<endl;
            cout<<"Note: the result of the last operation is store at the variable 'result'"<<endl;
            cout<<endl;
        }else if(params[0] == "number"){
            if(params.size() != 4 || params[2] != "="){
                cout<<"Invalid input"<<endl;
                continue;
            }
            string name = params[1];
            string value = params[3];
            if(!is_valid_name(params[1])){
                cout<<"Invalid variable name"<<endl;
                continue;
            }
            number num;
            if(!get_number(value, num)){
                cout<<"Invalid value"<<endl;
                continue;
            }
            variables[name] = num;
        }else if(params[0] == "print"){
            if(params.size() != 2){
                cout<<"Invalid input"<<endl;
                continue;
            }
            string name = params[1];
            if(!is_valid_name(params[1])){
                cout<<"Invalid variable name"<<endl;
                continue;
            }
            if(!variables.count(params[1])){
                cout<<"This variable does not exist"<<endl;
                continue;
            }
            print(variables[name]);
            cout<<endl;
        }else if(params[0] == "listv"){
            print_variables();
        }else if(params[0] == "add"){
            if(params.size() != 3){
                cout<<"Invalid input"<<endl;
                continue;
            }
            string param1 = params[1];
            string param2 = params[2];
            number number1, number2;
            if(!get_number(param1, number1) || !get_number(param2, number2)){
                cout<<"Invalid input"<<endl;
                continue;
            }
            number result = add(number1, number2);
            print(result);
            cout<<endl;
            // 将结果保存到result变量中
            variables["result"] = result;
        }else if(params[0] == "multiply"){
            if(params.size() != 3){
                cout<<"Invalid input"<<endl;
                continue;
            }
            string param1 = params[1];
            string param2 = params[2];
            number number1, number2;
            if(!get_number(param1, number1) || !get_number(param2, number2)){
                cout<<"Invalid input"<<endl;
                continue;
            }
            number result = multiplication(number1, number2);
            print(result);
            cout<<endl;
            // 将结果保存到result变量中
            variables["result"] = result;
        }else if(params[0] == "divide"){
            if(params.size() != 3){
                cout<<"Invalid input"<<endl;
                continue;
            }
            string param1 = params[1];
            string param2 = params[2];
            number number1, number2;
            if(!get_number(param1, number1) || !get_number(param2, number2)){
                cout<<"Invalid input"<<endl;
                continue;
            }
            number result = division(number1, number2);
            print(result);
            cout<<endl;
            // 将结果保存到result变量中
            variables["result"] = result;
        }else if(params[0] == "exit"){
            break;
        }else{
            cout<<"Invalid input"<<endl;
        }
    }
	return 0;
}
