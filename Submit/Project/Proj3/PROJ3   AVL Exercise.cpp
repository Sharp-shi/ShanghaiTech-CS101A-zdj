#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
 
struct this_extra{
    int size;
    long long sum;
    this_extra():size(0),sum(0){}
    this_extra(int v):size(1),sum(v){}
};

struct this_operation{
    template<typename Node>
    static void update(Node *x,Node *l,Node *r){
        x->extra.size=l->extra.size+r->extra.size+1;
        x->extra.sum=x->s+l->extra.sum+r->extra.sum;
    }
};

template<typename Key,typename Extra,typename Operation>
class avl_tree{
    private:
    struct node{
        Key s;
        Extra extra;
        int height;
        node *parent,*left,*right;
        bool is_dummy;

        node(Key k,const Extra &e,node *dummy_ptr)
            :s(k),extra(e),height(1),parent(dummy_ptr),left(dummy_ptr),right(dummy_ptr),is_dummy(false){}
        node():height(0),parent(nullptr),left(this),right(this),is_dummy(true){
        }
    };

    node *root;
    node *dummy;

    int get_height(node *x) const{
        if(x->is_dummy) return 0;
        return x->height;
    }
    
    void update(node *x){
        if(x->is_dummy) return;
        x->height=std::max(get_height(x->left),get_height(x->right))+1;
        Operation::update(x,x->left,x->right);
    }

    void rotate_right(node *x){
        node *l=x->left,*p=x->parent;
        x->left=l->right;
        if(!l->right->is_dummy) l->right->parent=x;
        l->right=x;
        x->parent=l;
        l->parent=p;
        if(p->is_dummy) root=l;
        else {
            if(p->left==x) p->left=l;
            else p->right=l;
        }
        update(x);
        update(l);
    }

    void rotate_left(node *x){
        node *r=x->right,*p=x->parent;
        x->right=r->left;
        if(!r->left->is_dummy) r->left->parent=x;
        r->left=x;
        x->parent=r;
        r->parent=p;
        if(p->is_dummy) root=r;
        else{
            if(p->left==x) p->left=r;
            else p->right=r;
        } 
        update(x);
        update(r);
    }

    void balance(node *x){
        while(!x->is_dummy){
            update(x);
            int b=get_height(x->left)-get_height(x->right);
            if(b>1){
                if(get_height(x->left->left)<get_height(x->left->right)) rotate_left(x->left);
                rotate_right(x);
            }else if(b<-1){
                if(get_height(x->right->right)<get_height(x->right->left)) rotate_right(x->right);
                rotate_left(x);
            }
            x=x->parent;
        }
    }

    void insert(Key x){
        if(root->is_dummy){
            root=new node(x,Extra(x),dummy);
            return;
        }
        
        node *current=root;
        while(true){
            if(x<current->s){
                if(!current->left->is_dummy) current=current->left;
                else{
                    current->left=new node(x,Extra(x),dummy);
                    current->left->parent=current;
                    balance(current);
                    break;
                }
            }else{
                if(!current->right->is_dummy) current=current->right;
                else{
                    current->right=new node(x,Extra(x),dummy);
                    current->right->parent=current;
                    balance(current);
                    break;
                }
            }
        }
    }

    node *find(int x) const{
        if(root->is_dummy) return dummy;
        
        node *current = root;
        while(current != nullptr && !current->is_dummy) {
            if(current->s == x) return current;
            else if(x < current->s) current = current->left;
            else current = current->right;
        }
        return dummy;
    }

    node *get_min(node *x) const{
        while(!x->is_dummy&&!x->left->is_dummy) x=x->left;
        return x;
    }

    void erase(node *x){
        if(x->is_dummy) return;

        if(x->left->is_dummy&&x->right->is_dummy){
            node *p=x->parent;
            if(!p->is_dummy){
                (p->left==x ? p->left : p->right)=dummy;
                balance(p);
            }else{
                root=dummy;
            }
            delete x;
        }else if(x->left->is_dummy||x->right->is_dummy){
            node *child;
            if(!x->left->is_dummy) child=x->left;
            else child=x->right;
            child->parent=x->parent;

            if(!x->parent->is_dummy){
                if(x->parent->left==x) x->parent->left=child;
                else x->parent->right=child;
                balance(x->parent);
            }else root=child;
            delete x;
        }else{
            node *temp=get_min(x->right);
            x->s=temp->s;
            erase(temp);
        }
    } 

    void preorder(node *x) const{
        if (x->is_dummy) return;

        int pp=0,pl=0,pr=0;
        if(!x->parent->is_dummy) pp=x->parent->s;
        if(!x->left->is_dummy) pl=x->left->s;
        if(!x->right->is_dummy) pr=x->right->s;
        std::printf("%d %d %d %d\n",x->s,pp,pl,pr);

        preorder(x->left);
        preorder(x->right);

    }

    node *kth(int k) const{
        if(k<1||k>root->extra.size) return dummy;

        node *current=root;
        while(!current->is_dummy){
            int ls=current->left->extra.size;
            if(k==ls+1) return current;
            else if(k<=ls) current=current->left;
            else{
                k-=ls+1;
                current=current->right;
            }
        }
        return dummy;
    }

    long long weighted_query(int k) const{
        if(root->is_dummy) return -1;

        long long total_sum=root->extra.sum,min=-1;
        bool flag=false;

        helper(root,k,total_sum,0,0,min,flag);

        if(flag) return min;
        return -1;
    }

    void helper(node *x,int k,long long total_sum,long long left_sum,long long left_k_sum,long long &min,bool &flag) const{
        if(x->is_dummy) return;

        helper(x->left,k,total_sum,left_sum,left_k_sum,min,flag);

        long long cur_left_sum=left_sum+x->left->extra.sum+x->s;
        long long cur_left_k_sum=left_k_sum+k*x->left->extra.sum+k*(long long)x->s;
        long long cur_right_sum=total_sum-cur_left_sum;

        long long value=cur_left_k_sum-cur_right_sum;

        if(value>=0){
            if(value<min||!flag){
                min=value;
                flag=true;
            }
        }

        helper(x->right,k,total_sum,cur_left_sum,cur_left_k_sum,min,flag);
    }

    public:
    class iterator{
        private:
        node *current;
        node *dummy;
        public:
        iterator(node *c,node *d):current(c),dummy(d){}

        bool operator!=(const iterator &other) const{
            return current!=other.current;
        }
        bool operator==(const iterator &other) const{
            return current==other.current;
        }
        Key &operator*(){
            return current->s;
        }
        node *getNode(){
            return current;
        }

        iterator &operator++(){ 
            if(current->is_dummy) return *this;

            if(!current->right->is_dummy){
                current=current->right;
                while(!current->left->is_dummy) current=current->left;
            }else{
                node *p=current->parent;
                while(!p->is_dummy&&current==p->right){
                    current=p;
                    p=p->parent;
                }
                current=p;
            }
            return *this;
        }
    };
    
    avl_tree(){
        dummy=new node();
        dummy->left=dummy->right=dummy;
        dummy->parent=dummy;
        root=dummy;
    }

    ~avl_tree(){
        clear(root);
        delete dummy;
    }

    void clear(node *x){
        if(x->is_dummy) return;

        clear(x->left);
        clear(x->right);
        delete x;
    }
    void insert_node(Key x){
        insert(x);
    }

    void erase_node(Key x){
        node *temp=find(x);
        if(!temp->is_dummy) erase(temp);
    }

    void print_tree() const{
        preorder(root);
    }

    int get_kth(int k) const{
        node *temp=kth(k);
        if(temp->is_dummy) return -1;
        return temp->s;
    }

    int get_query(Key x) const{
        node *temp=find(x);
        if(temp->is_dummy) return -1;
        return temp->height - 1;
    }

    long long get_weighted_query(int k) const{
        return weighted_query(k);
    }

    iterator begin() const{
        node *current=root;
        if(current->is_dummy) return end();
        while(!current->left->is_dummy) current=current->left;
        return iterator(current,dummy);
    }

    iterator end() const{
        return iterator(dummy,dummy);
    }
};

int main(){
    avl_tree <int,this_extra,this_operation> tree;

    int n;
    if(std::scanf("%d",&n)!=1) return 0;

    for(int i=1;i<=n;i++){
        int opt,x;
        std::scanf("%d %d",&opt,&x);
        std::printf("----------#%d: %d %d----------\n",i,opt,x);

        if(opt==1){
            tree.insert_node(x);
            tree.print_tree();
        }else if(opt==2){
            int depth=tree.get_query(x);
            if(depth==-1) std::printf("Not found!\n");
            else std::printf("%d\n",depth);
        }else if(opt==3){
            tree.erase_node(x);
            tree.print_tree();
        }else if(opt==4){
            int ans=tree.get_kth(x);
            if(ans==-1) std::printf("Invalid query!\n");
            else std::printf("%d\n",ans);
        }else if(opt==5){
            long long ans=tree.get_weighted_query(x);
            if(ans==-1) std::printf("Invalid query!\n");
            else std::printf("%lld\n",ans);
        }
    }

    return 0;
}