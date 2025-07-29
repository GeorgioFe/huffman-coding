#include "HCTree.hpp"
#include <iostream>
#include <stack>

void helperDelete(HCNode* node) {
    if (node == nullptr) {
        return;
    }

    helperDelete(node->c0);
    helperDelete(node->c1);
    delete node;
}

void HCTree::build(const vector<int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            leaves[i] = new HCNode(freqs[i], i);
            pq.push(leaves[i]);
        }
    }
    
    while (pq.size() > 1) {
        // Removing children nodes from priority_queue
        HCNode* left = pq.top();
        pq.pop();
        HCNode* right = pq.top();
        pq.pop();

        // Creating Parent Node and assigning children to it.
        int sumFreq = left->count + right->count;
        HCNode* parent = new HCNode(sumFreq, left->symbol);
        parent->c0 = left;
        parent->c1 = right;
        left->p = parent;
        right->p = parent;

        //Adding new tree into priority_queue
        pq.push(parent);
    }

    this->root = pq.top();
}

void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const {
    HCNode* symbolNode = leaves[symbol];
    HCNode* curr = symbolNode;
    stack<int> bits;
    
    while (curr->p != nullptr) {
        if (curr == curr->p->c0) {
            bits.push(0);
            curr = curr->p;
        }
        else {
            bits.push(1);
            curr = curr->p;
        }
    }

    while (!(bits.empty())) {
        out.write_bit(bits.top());
        bits.pop();
    }
}

unsigned char HCTree::decode(FancyInputStream & in) const {
    HCNode* curr = root;
    int bit;
    unsigned char symbol;
    
    while(curr->c0 != 0 || curr->c1 != 0) {
        bit = in.read_bit();

        if (bit == -1) {
            return 0;
        }

        if (bit == 1) {
            curr = curr->c1; 
        }
        else {
            curr = curr->c0;
        }
    }

    symbol = curr->symbol;

    return symbol;    

 }

HCTree::~HCTree() {
    helperDelete(root);
}
