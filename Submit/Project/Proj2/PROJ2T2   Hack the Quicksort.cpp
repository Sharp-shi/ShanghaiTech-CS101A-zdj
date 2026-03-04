#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

const int N = 1e5;
const int MAX_INSERTION = 5;
std::mt19937 engine;

std::vector<int> pos;  
std::vector<int> val;  
int nextVal;

void freeze(int origPos) {
    if (val[origPos]==-1) {
        val[origPos]=nextVal++;
    }
}

void antiQuicksort(int first, int last,int strategy) {
    while (last-first>MAX_INSERTION) {
        int n=last-first;
        int pivotIdx;
        
        if (strategy==1) {
            pivotIdx=first;
        } else if (strategy == 2) {
            int p=std::uniform_int_distribution<>(0,n-1)(engine);
            pivotIdx = first + p;
        } else {
            int p1=std::uniform_int_distribution<>(0,n-1)(engine);
            int p2=std::uniform_int_distribution<>(0,n-2)(engine);
            int p3=std::uniform_int_distribution<>(0,n-3)(engine);
            p3+=p3>=p2;
            p3+=p3>=p1;
            p2+=p2>=p1;
            
            int idx1 = first + p1;
            int idx2 = first + p2;
            int idx3 = first + p3;
            
            freeze(pos[idx1]);  
            freeze(pos[idx2]);
            freeze(pos[idx3]);  
            
            if (val[pos[idx2]]<val[pos[idx1]]) std::swap(p2,p1);
            if (val[pos[first + p3]]<val[pos[first+p2]]) std::swap(p3,p2);  
            if (val[pos[first + p2]]<val[pos[first+p1]]) std::swap(p2,p1);
            
            pivotIdx = first + p2;
        }
        
        freeze(pos[pivotIdx]);
        std::swap(pos[first], pos[pivotIdx]);
        
        first=first+1;
    }

    for (int i=first;i<last;i++) freeze(pos[i]);
}

void hackQuicksort(int pivotStrategy,int seed) {
    engine.seed(seed);
    
    pos.resize(N);
    val.assign(N,-1);
    nextVal = 0;
    
    for (int i=0;i<N;i++)  pos[i]=i;
    
    antiQuicksort(0,N,pivotStrategy);
    
    for (int i=0;i<N;++i) {
        if (i>0) std::cout<< " ";
        std::cout<<val[i];
    }
    std::cout<<std::endl;
}

int main() {
    int pivotStrategy, seed;
    std::cin>>pivotStrategy>>seed;
    
    hackQuicksort(pivotStrategy,seed);
    
    return 0;
}
