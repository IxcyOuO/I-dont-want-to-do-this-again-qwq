#include <iostream>
#include <optional>
#include <vector>
#include <initializer_list>

template<typename type, typename compare_rule = greater<type>>
class HEAP{
    public:
    HEAP(){}
    HEAP(initializer_list<type> given_data){
        for(const type& x : given_data){
            node_list.push_back(x);
        }
        heapify();
    }
    HEAP(const vector<type>& given_data){
        for(const type& x : given_data){
            node_list.push_back(x);
        }
        heapify();
    }

    bool empty(){
        if(node_list.size() == 0){
            return true;
        }
        else{
            return false;
        }
    }

    type top(){
        if(empty() == false){
            return node_list[0];
        }
        else{
            return nullopt;
        }
    }

    void pop(){
        if(empty() == true){
            return;
        }
        int n = node_list.size();
        node_list[0] = node_list[n - 1]; //複製最後一個值
        node_list.erase(node_list.begin() + n - 1); //從最後一個值移走
        n--;
        int ptr = 0;
        int bound = (n >> 1) - 1;
        while(ptr <= bound){
            type point = node_list[ptr];
            type left = node_list[(ptr + 1 << 1) - 1]; //左子葉
            type right; //右子葉
            type compare; //left跟right選一個
            int compare_id;
            if((ptr + 1 << 1) < n){
                right = node_list[ptr + 1 << 1];
                if(cmp(left, right)){
                    compare = left;
                    compare_id = (ptr + 1 << 1) - 1;
                }
                else{
                    compare = right;
                    compare_id = (ptr + 1 << 1);
                }
            }
            else{
                compare = left;
                compare_id = (ptr + 1 << 1) - 1;
            }
            if(cmp(compare, point)){
                node_list[ptr] = compare;
                node_list[compare_id] = point;
                ptr = compare_id;
            }
            else{
                break;//結束
            }
        }
    }

    void push(type value){
        node_list.push_back(value);
        int ptr = node_list.size() - 1;
        while(ptr >= 1){
            type point = node_list[ptr];
            int root_id = (ptr + 1 >> 1) - 1;
            type root = node_list[root_id];
            if(cmp(point, root)){
                node_list[ptr] = root;
                node_list[root_id] = point;
                ptr = root_id;
            }
            else{
                break;
            }
        }
    }

    void print(){
        int n = node_list.size();
        if(n == 0){
            return;
        }
        cout << node_list[0];
        for(int i = 1; i < n; i++){
            cout << ' ' << node_list[i];
        }
    }

    private:
    std::vector<type> node_list = {};
    //這段程式並沒有node（或者說node只有一個value）
    compare_rule cmp;

    void heapify(){
        int n = node_list.size();
        for(int i = 2; i <= n; i <<= 1){
            for(int j = n - 1; j >= i - 1; j--){
                type leaf = node_list[j];
                type root = node_list[(j + 1 >> 1) - 1];
                if(cmp(leaf, root) == true){
                    node_list[j] = root;
                    node_list[(j + 1 >> 1) - 1] = leaf;
                }
            }
        }
    }
};