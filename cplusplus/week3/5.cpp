#include <iostream>
#include <vector>
using namespace std;

class TreeNode{
    public:
        int val;
        vector<TreeNode*> children;
        TreeNode(int x) : val(x) {}
};

class Strategy{
    public:
        int p;
        
        int q;
        int k;
        
        Strategy(int p, int q, int k) : p(p), k(k), q(q) {}
        
        ~Strategy() = default;
        
        virtual int find(TreeNode* node) = 0;
    
};

class wang : public Strategy{
    public:
        wang(int p, int q, int k) : Strategy(p, q, k) {}
        int find(TreeNode* node) override{
            int sum = 0;
            if(node->val <= p){
                
            }else{
                sum += node->val;
                for(auto &tmp : node->children){
                    sum += find(tmp);
                }
            }
            return sum;
            
        }
        
    
};
class hu : public Strategy{
    public:
        hu(int p, int q, int k) : Strategy(p, q, k) {}
        int find(TreeNode* node) override{
            int sum = 0;
            sum += node->val;
            for(auto &tmp : node->children){
                sum += findExceptRoot(tmp, node->val);
            }
            return sum;
            
            
        }
        int findExceptRoot(TreeNode* node, int father_value){
            int sum = 0;
            if(node->val > q && node->val + father_value > k){
                sum += node->val;
                for(auto &tmp : node->children){
                    sum += findExceptRoot(tmp, node->val);
                }
            }
            return sum;
        }
    
};
class xie : public Strategy{
    public:
        xie(int p, int q, int k) : Strategy(p, q, k) {}
        int find(TreeNode* node) override{
            int sum = 0;
            sum += node->val;
            for(auto &tmp : node->children){
                sum += findExceptRoot(tmp);
            }
            return sum;
            
            
        }
        int findExceptRoot(TreeNode* node){
            int sum = 0;
            if(node->val % 2 == 0){
                sum += node->val;
                for(auto &tmp : node->children){
                    sum += findExceptRoot(tmp);
                }
            }
            return sum;
        }
    
};

int main(){
    int n, p, q, k;
    cin >> n >> p >> q >> k;
    vector<TreeNode*> tree(n);
    for(int i = 1; i <= n; i++){

       tree[i - 1] = new TreeNode(i);
    }
    for(int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        tree[x - 1]->children.push_back(tree[y - 1]);
    }
    for(int i = 0; i < n; i++){
        int value;
        cin >> value;
        tree[i]->val = value;
    }
    wang s1(p, q, k);
    hu s2(p, q, k);
    xie s3(p, q, k);
    cout << s1.find(tree[0]) << " " << s2.find(tree[0]) << " " << s3.find(tree[0]) << endl;
}