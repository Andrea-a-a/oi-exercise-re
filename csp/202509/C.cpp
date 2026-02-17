#include <bits/stdc++.h>
using namespace std;

const int MAXS = 70;
const int MAXD = 130;

pair<string, string> s[MAXS];
vector<pair<string, string>> d;
//pair<string, string> d[MAXD];

string dict[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};

struct Node {
    char data;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(char d) : data(d), left(nullptr), right(nullptr) {}
    Node() : data('\0'), left(nullptr), right(nullptr) {}
};

string huff;
int nd, ns, nn;

void quote(int index);
string getfirst(int index);
string decode(string s, shared_ptr<Node> root);
string huffdecode(string s, shared_ptr<Node> root);
int chartoint(char x);


shared_ptr<Node> rebuildHuffmanTree(const string& s, int& index) {
    if (index >= s.length()) return nullptr;

    if (s[index] == '1') {
        index++; // 跳过'1'
        char ch = s[index++]; // 读取字符
        return make_shared<Node>(ch);
    } else if (s[index] == '0') {
        index++; // 跳过'0'
        auto node = make_shared<Node>();
        node->left = rebuildHuffmanTree(s, index);
        node->right = rebuildHuffmanTree(s, index);
        return node;
    }
    return nullptr;
}

// 辅助函数：打印树结构（前序遍历）
void printTree(const shared_ptr<Node>& root, string prefix = "") {
    if (!root) return;

    if (root->data != '\0') {
        cout << prefix << "Leaf: " << root->data << endl;
    } else {
        cout << prefix << "Internal Node" << endl;
    }
    printTree(root->left, prefix + "  ");
    printTree(root->right, prefix + "  ");
}


int main(){
    cin >> ns>> nd;
    for(int i = 1; i <= ns; i++){
        cin >> s[i].first >> s[i].second;
    }
    cin >> huff;
    int index = 0;
    auto root = rebuildHuffmanTree(huff, index);
    cin >> nn;
    for(int o = 0; o < nn; o++){
        int opt, index;
        cin >> opt >> index;
        //引用
        if(opt == 1){
            quote(index);
        }
        
        else{
            string k, v;                
            if(index == 0){
                cin >> k >> v;
            }
            else{
                k = getfirst(index);
                cin >> v;
            }
            k = decode(k, root);
            v = decode(v, root);
            cout << k << ": " << v << endl;
            //字面量并索引指令
            if(opt == 2){
                d.insert(d.begin(), pair(k,v));
                if(d.size() > nd){
                    d.pop_back();
                }
                    
            }


        } 


    }

}



/*
int main(){
    cin >> huff;
    int ind = 0;
    auto root = rebuildHuffmanTree(huff, ind);
    //printTree(root);
    string s;
    cin >> s;
    cout << decode(s, root);

    return 0;
}
*/




void quote(int index){
    if(index<=ns){
        cout << s[index].first << ": " << s[index].second << endl;
    }
    else{
        cout << d[index-ns-1].first << ": " << d[index-ns-1].second << endl;
    }
}
    


string getfirst(int index){
    if(index<=ns){
       return s[index].first;
    }
    else if(index <= ns + nd){
        return d[index-ns-1].first;
    }
    else{
        return "error when get first";
    }
    
}


string decode(string q, shared_ptr<Node> root){
    if(q[0] != 'H' || q.length() <= 1){
        return q;
    }
    else if(q[0] == 'H' && q[1] == 'H'){
        q = q.substr(1);
        // string x = q[1];
        // for(int i = 2; i <q.length() ; i++){
        //     x = x+s[i];
        // }
        return q;
        //else：赫夫曼编码decode
        //return huffdecode(q, root);
        
    }
    cout << "error decoding";
    return " ";


}

string huffdecode(string q, shared_ptr<Node> root){
    string p;
    int len = q.length();
    for(int i = 0; i < len-2; i++){
        p = p + dict[chartoint(q[i])];
    }
    int wei = 0;
    wei = chartoint(q[len-2]) * 16 + chartoint(q[len-1]);
    //cout << "p:" << p << endl;

    int len2 = p.length();
    string r;

    auto nownode = root;
    
    
    for(int i = 0; i < len2-wei; i++){
        if (!nownode) {
            break; 
        }

        if(p[i] == '1'){
            //turn right
            nownode = nownode -> right;
        }
        else if(p[i] == '0'){
            //turn left
            nownode = nownode -> left;
        }
        //cout << "i=" << i << " data:" << nownode->data <<endl;
                    if (nownode->data != '\0') {
                r += nownode -> data;
                nownode = root;
        }

    }
    
    return r;

}



int chartoint(char x){
    if(x >= '0' && x <= '9'){
        return x - '0';
    }
    else if(x >= 'a' && x <= 'f') { 
        return x - 'a' + 10;
    }
    else if (x >= 'A' && x <= 'F') {
        return x - 'A' + 10;
    }
    return 0;
}

