#include <vector>

class DSU{
    public:
    struct node{
        int id;
        int rank;
        node* parent;

        node(){
            rank = 0;
            parent = this;
        }
    };

    DSU(int n){
        node_list.resize(n);
        for(int ID = 0; ID < n; ID++){
            node_list[ID] = new node;
            node_list[ID]->id = ID + 1;
        }
    }

    ~DSU(){
        for(node* x : node_list){
            delete x;
        }
    }

    node* find_set(int number_x){
        node* x = node_list[number_x - 1];
        if(x->parent != x){
            x->parent = find_set(x->parent->id);
        }
        return x->parent;
    }

    bool is_same_group(int number_a, int number_b){
        if(find_set(number_a) == find_set(number_b)){
            return true;
        }
        else{
            return false;
        }
    }

    void merge(int number_a, int number_b){
        node* root_a = find_set(number_a);
        node* root_b = find_set(number_b);
        if(root_a == root_b){
            return;
        }

        if(root_a->rank == root_b->rank){
            root_a->rank++;
            root_b->parent = root_a;
            return;
        }
        else if(root_a->rank > root_b->rank){
            root_b->parent = root_a;
            return;
        }
        else{
            root_a->parent = root_b;
            return;
        }
    }

    DSU(const DSU&) = delete;
    DSU& operator=(const DSU&) = delete;

    private:
        std::vector<node*> node_list;
};
//1-based的外部查詢