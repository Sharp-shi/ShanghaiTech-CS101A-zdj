#include <iostream>
#include <string>
#include <vector>
#include <functional>

class hashtable{
    private:
    std::vector<std::string> table; 
    std::vector<bool> occupied;
    int size,capacity; 
    
    int hash(const std::string& key) const {
        return std::hash <std::string> {}(key) % capacity;
    }

    void rehash(){
        std::vector<std::string> oldtable=table; 
        std::vector<bool> oldoccupied=occupied;
        int oldcapacity=capacity;

        capacity*=2;
        table.clear();
        table.resize(capacity);
        occupied.clear();
        occupied.resize(capacity, false);
        size=0;

        for(int i=0;i<oldcapacity;i++){
            if(oldoccupied[i]){
                insert(oldtable[i], false);
            }
        }
    }

    public:
    hashtable():size(0), capacity(16){
        table.resize(capacity);
        occupied.resize(capacity,false);
    }

    void insert(const std::string& key,bool print){
        int idx=hash(key);

        while(occupied[idx]){
            if(table[idx]==key){
                if(print) std::cout<<key<<" already exists at "<<idx<<std::endl;
                return; 
            }
            idx=(idx+1)%capacity;
        }

        table[idx]=key;
        occupied[idx]=true;
        size++;

        if(print) std::cout<<key<<" inserted at "<<idx<<std::endl;

        if((double)size/capacity>0.5) rehash();
    }

    int find(const std::string& key,bool print) const {
        int idx=hash(key);
        int startidx=idx;

        while(occupied[idx]){
            if(table[idx]==key){
                if(print) std::cout<<key<<" found at "<<idx<<std::endl;
                return idx;
            }
            idx=(idx+1)%capacity;
            if(idx==startidx) break; 
        }
        if(print) std::cout<<key<<" does not exist"<<std::endl;
        return -1;

    }

    void erase(const std::string& key){
        int idx=find(key,false);
        if(idx==-1){
            std::cout<<key<<" does not exist"<<std::endl;
            return;
        }
        occupied[idx]=false;
        size--;
        std::cout<<key<<" erased at "<<idx;
        
        int current=(idx+1)%capacity;
        while(occupied[current]){
            std::string moving_key=table[current];
            int home=hash(moving_key);
            
            bool shouldMove = false;
            if (home <= current) {
                shouldMove = (home <= idx && idx < current);
            } else {
                shouldMove = (idx >= home || idx < current);
            }
            
            if(shouldMove){
                table[idx]=moving_key;
                occupied[idx]=true;
                occupied[current]=false;
                std::cout<<", moving "<<moving_key<<" from "<<current;
                idx=current;
            }
            current=(current+1)%capacity;
        }
        std::cout<<std::endl;
    }
};

int main(){
    hashtable ht;
    std::string key;
    int op;

    while(std::cin>>op && op!=0){
        std::cin>>key;

        if(op==1){
            ht.insert(key,true);
        }else if(op==2){
            ht.find(key,true);
        }else if(op==3){
            ht.erase(key);
        }
    }

    return 0;
}