#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>

struct Node
{
    int val;
    Node* firstChild, * nextSibling;
    bool deleted = false;

    Node(int v) : val(v), firstChild(nullptr), nextSibling(nullptr) {};

    Node(Node& n) {
        this->val = n.val;
        this->firstChild = n.CopyChildren();
        this->nextSibling = nullptr;
    }

    ~Node() {
        if (firstChild != nullptr)
            delete firstChild;
        if (nextSibling != nullptr)
            delete nextSibling;
    }

    Node& operator=(Node& n) {
        this->val = n.val;
        this->firstChild = n.CopyChildren();
    }

    void AddChild(int val) {
        Node* n = new Node(val);
        if (this->firstChild == nullptr) {
            this->firstChild = n;
        } else {
            n->nextSibling = this->firstChild;
            this->firstChild = n;
        }
    }

    Node* CopyChildren() {
        if (firstChild != nullptr) {
            Node* n = new Node(firstChild->val);
            
            Node* _cursor = firstChild, * _cursor2 = n;
            if (_cursor) 
                n->firstChild = _cursor->CopyChildren();
            while (_cursor->nextSibling != nullptr) {
                _cursor = _cursor->nextSibling;

                _cursor2->nextSibling = new Node(_cursor->val);
                _cursor2 = _cursor2->nextSibling;
                _cursor2->firstChild = _cursor->CopyChildren();

            }

            return n;
        }
        return nullptr;
    }

    Node* MergeSiblings();
};

struct PHeap
{
    Node* root = nullptr;

    PHeap() {}

    PHeap(Node* n) {
        root = new Node(*n);
    }

    ~PHeap() {
        delete root;
    }

    void MinHeapify(Node* p_n) {
        int min_value = p_n->val;
        Node* min_value_node = p_n, * _cursor = p_n->firstChild;
        while (_cursor) {
            if (_cursor->val < min_value) {
                min_value = _cursor->val;
                min_value_node = _cursor;
            }

            _cursor = _cursor->nextSibling;
        }

        if (min_value_node != p_n) {
            int tmp = min_value_node->val;
            min_value_node->val = p_n->val;
            p_n->val = tmp;
        }

    }

    static PHeap& Build(std::vector<int> vals) {
        PHeap* p = new PHeap;
        if (!vals.empty()) {
            int m = vals[std::distance(vals.begin(), std::min_element(vals.begin(), vals.end()))];
            p->root = new Node(m);

            for (int i : vals) {
                if (i != m) {
                    p->root->AddChild(i);
                }
            }

        }

        return *p;
    }

    static PHeap& Merge(PHeap& p1, PHeap& p2) {
        PHeap* p = new PHeap;

        if (p1.root == NULL && p2.root != NULL) {
            p->root = new Node(*p2.root);
            return *p;
        }

        if (p2.root == NULL && p1.root != NULL) {
            p->root = new Node(*p1.root);
            return *p;
        }

        if (p1.root->val >= p2.root->val) {
            p->root = new Node(*p2.root);

            p->root->AddChild(p1.root->val);
            p->root->firstChild->firstChild = p1.root->CopyChildren();

        } else {
            p->root = new Node(*p1.root);

            p->root->AddChild(p2.root->val);
            p->root->firstChild->firstChild = p2.root->CopyChildren();
        }

        return *p;
    }

    void Insert(int val) {
        if (this->root) {
            PHeap p1(new Node(val));
            *this = PHeap::Merge(*this, p1);
        } else
            this->root = new Node(val);
    }

    int FindMin() {
        if (root) {
            return root->val;
        }
        throw std::exception("Empty tree");
    }

    int DeleteMin() {
        Node* n = root->firstChild->MergeSiblings(), * b = root;
        int a = root->val;

        b->firstChild = NULL;

        root = n;

        delete b;
        return a;
    }

    void Delete(int val) {
        // search for the value and mark its deleted to true
        std::queue<Node*> q;

        q.push(root);

        while (!q.empty()) {
            Node* p = q.front();
            q.pop();

            while (p) {
                if (p->val == val) {
                    p->deleted = true;
                }

                if (p->firstChild) {
                    q.push(p->firstChild);
                }

                p = p->nextSibling;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& output, PHeap& p) {
        std::queue<Node*> q;

        q.push(p.root);

        while (!q.empty()) {
            Node* p = q.front();
            q.pop();

            while (p) {
                output << p->val << " ";

                if (p->firstChild) {
                    q.push(p->firstChild);
                }

                p = p->nextSibling;
            }
        }

        return output;
    }
};

Node* Node::MergeSiblings() {
    if (nextSibling == NULL) {
        return this;
    } else {
        Node* next = nextSibling;
        nextSibling = NULL;

        Node* rightToMerge = next->MergeSiblings();
        PHeap p1(new Node(*this)), p2(new Node(*rightToMerge));
        PHeap r = PHeap::Merge(p1, p2);
        Node* result = new Node(*r.root);
        delete result->nextSibling;

        return result;
    }
}

int main() {
    //std::vector<int> v{27, 11, 23, 44, 3, 1, 0, -7, 141, -2000, 4573, 22, 21, 37};
    //PHeap& _p = PHeap::Build(v);

    PHeap _p;

    //Node* _cursor = _p.root;
    //std::cout << _p << " ";
    //std::cout << "\n";

    //std::cout << _p.DeleteMin() << "\n";

    //std::cout << _p << " ";
    //std::cout << "\n";


    std::ifstream f("date.in");
   
    int commands_nr;
    f >> commands_nr;

    int _command;
    int v;
    while (!f.eof()) {
        f >> _command;
        switch (_command) {
            case 1:
            f >> v;
            _p.Insert(v);
            break;

            case 2:
            f >> v;
            _p.Delete(v);
            break;

            case 3:
            std::cout << _p.FindMin() << "\n";
            break;

            case 4:
             _p.DeleteMin();
            break;
        }
    }

    return 0;
}
