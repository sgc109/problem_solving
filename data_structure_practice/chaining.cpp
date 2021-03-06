#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#define MAX_CNT 30000000

using namespace std;

struct Node{
    Node *nxt;
    int key, val;
};

Node nodes[MAX_CNT + 3];
int cnt_node = 0;
Node* get_node(int key, int val){
    Node* ret = &nodes[cnt_node++];
    ret->nxt = NULL;
    ret->key = key;
    ret->val = val;
    return ret;
}

Node* buck[MAX_CNT + 3];
int get_hash(int x){
    int tmp = x * 1217 + 71;
    tmp = tmp * 18217 + 13;
    tmp = tmp * 17 + 7;
    tmp = tmp * 11 + 3;
    return (tmp % MAX_CNT + MAX_CNT) % MAX_CNT;
}

void insert(int key, int val){
    Node* ins = get_node(key, val);
    int h = get_hash(key);
    Node* cur = buck[h];
    while(cur != NULL){
        if(cur->key == key) {
            cur->val = val;
            return;
        }
        cur = cur->nxt;
    }


    if(cur == NULL) {
        buck[h] = ins;
        return;
    }
    ins->nxt = buck[h];
    buck[h] = ins;
}

Node* find(int key){
    Node* ret = NULL;
    int h = get_hash(key);
    Node* cur = buck[h];
    while(cur != NULL && cur->key != key){
        cur = cur->nxt;
    }
    return cur == NULL ? NULL : cur;
}

void remove(int key){
    int h = get_hash(key);
    if(buck[h] == NULL) return;
    if(buck[h]->key == key) {
        buck[h] = NULL;
        return;
    }
    Node* prv = buck[h];
    Node* cur = prv->nxt;
    while(cur != NULL){
        if(cur->key == key){
            prv->nxt = cur->nxt;
            break;
        } 
        prv = cur;
        cur = cur->nxt;
    }
}

int main(){
    for(int i = 0; i < MAX_CNT; i++) buck[i] = NULL;
    srand(time(NULL));

    clock_t start = clock();
    for(int i = 0; i < 20000000; i++){
        insert(rand(), rand());
        find(rand());
        remove(rand());
    }

    clock_t end = clock();

    cout << "time consuming : " << double(end - start) / CLOCKS_PER_SEC << 's' << endl;
    return 0;
}
