#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

const int p = pow(10,9) + 7;

class Matrix{
    public:
        int edge;
        vector<vector<long long>> content;
    
    Matrix (int n) : edge(n), content(n, vector<long long>(n, 0)) {}
    
};

Matrix mul(Matrix a, Matrix b, int n){
    Matrix c = Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                long long tmp = (a.content[i][k] % p * b.content[k][j] % p) % p;
                c.content[i][j] = (c.content[i][j] % p + tmp) % p;
            }
        }
    }
    return c;
    
}

int main(){
    int n, p;
    cin >> n >> p;
    Matrix tmp = Matrix(n);
    Matrix ans = Matrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            long long num;
            cin >> num;
            tmp.content[i][j] = num;
            if(i == j){
                ans.content[i][j] = 1;
            }else{
                ans.content[i][j] = 0;
            }
        }
        
        
    }
    while(p){
        if(p & 1){
            ans = mul(ans, tmp, n);
        }
        tmp = mul(tmp, tmp, n);
        p >>= 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << ans.content[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}