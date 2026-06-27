#include <string>
#include <algorithm>

std::string str_add(std::string, std::string);
std::string str_sub(std::string, std::string);
std::string str_pod(std::string, std::string);
std::string str_div(std::string, std::string);
std::string str_mod(std::string, std::string);

std::string str_add(std::string a, std::string b){
    if(a[0] == '-' && b[0] != '-'){
        a.erase(0, 1);
        return str_sub(b, a);
    }
    if(a[0] != '-' && b[0] == '-'){
        b.erase(0, 1);
        return str_sub(a, b);
    }
    bool minus_sign = false;
    if(a[0] == '-' && b[0] == '-'){
        minus_sign = true;
        a.erase(0, 1);
        b.erase(0, 1);
    }

    int len_a = a.length();
    int len_b = b.length();
    int len_ret;
    int remain_a = 0;
    int remain_b = 0;
    if(len_a > len_b){
        len_ret = len_a;
        remain_b = len_a - len_b;
    }
    else{
        len_ret = len_b;
        remain_a = len_b - len_a;
    }

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    std::string fit_a(remain_a, '0');
    std::string fit_b(remain_b, '0');
    a += fit_a;
    b += fit_b;
    std::string ret(len_ret + 1, '0');

    for(int i = 0; i < len_ret; i++){
        ret[i] += (a[i] - '0') + (b[i] - '0');
        if(ret[i] > '9'){
            ret[i] -= 10;
            ret[i + 1]++;
        }
    }
    if(ret[len_ret] == '0'){
        ret.erase(len_ret, 1);
    }
    if(minus_sign){
        ret += "-";
    }
    reverse(ret.begin(), ret.end());

    return ret;
}

std::string str_sub(std::string a, std::string b){
    if(a[0] == '-' && b[0] != '-'){
        b = "-" + b;
        return str_add(a, b);
    }
    if(a[0] != '-' && b[0] == '-'){
        b.erase(0, 1);
        return str_add(a, b);
    }
    bool minus_sign = false;
    int len_a = a.length();
    int len_b = b.length();
    if(a[0] == '-' && b[0] == '-'){
        if(len_a > len_b){
            minus_sign = true;
        }
        else if(len_a < len_b){
            minus_sign = false;
        }
        else{
            for(int i = 1; i < len_a; i++){
                if(a[i] > b[i]){
                    minus_sign = true;
                    break;
                }
            }
        }
    }
    else{
        if(len_a > len_b){
            minus_sign = false;
        }
        else if(len_a < len_b){
            minus_sign = true;
        }
        else{
            for(int i = 0; i < len_a; i++){
                if(a[i] < b[i]){
                    minus_sign = true;
                    break;
                }
            }
        }
    }

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    if(*(a.end() - 1) == '-'){
        a.erase(len_a - 1, 1);
        len_a--;
    }
    if(*(b.end() - 1) == '-'){
        b.erase(len_b - 1, 1);
        len_b--;
    }
    int remain_a = 0;
    int remain_b = 0;
    int len_ret;
    if(minus_sign){
        len_ret = len_b;
        remain_a = len_b - len_a;
    }
    else{
        len_ret = len_a;
        remain_b = len_a - len_b;
    }
    std::string fit_a(remain_a, '0');
    std::string fit_b(remain_b, '0');
    a += fit_a;
    b += fit_b;
    std::string ret(len_ret, '0');

    if(minus_sign){
        for(int i = 0; i < len_ret; i++){
            ret[i] += b[i] - a[i];
            if(ret[i] < '0'){
                ret[i] += 10;
                ret[i + 1]--;
            }
        }
        ret += "-";
    }
    else{
        for(int i = 0; i < len_ret; i++){
            ret[i] += a[i] - b[i];
            if(ret[i] < '0'){
                ret[i] += 10;
                ret[i + 1]--;
            }
        }
    }
    std::reverse(ret.begin(), ret.end());

    return ret;
}