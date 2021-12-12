#include <math.h>
#include <iostream>

uint pow_mod(uint x, uint y, uint mod){
    if (x == 0 && y == 0) {
        std::cout << "error: 0^0 undefined !";
        return -1;
    }
    else if (y == 0 ) return 1;

    uint r = x;
    for (y; y > 1; --y) {
        r = (r * x) % mod;
    }
    return r;
}

//verif A: a^d =1 (mod n) ?
bool verif_a(uint a, uint d, uint n){
    bool test_a = false;
    int r = pow_mod(a, d, n);
    if ( r == 1) {
        test_a = true; 
    }
    std::cout << "result of test a = " << r << "\n";
    return test_a;
}

//verif B: a^((2j)d) = -1 (mod n) pour un j tel que 0<=j<=m-1?
bool verif_b(uint a, uint d, uint m, uint n){
    bool test_b = false;
    for (int j=0; j <= m-1; j++){
        std::cout << "result of test b: " << "a^((2^j)*d) = " << a << "^((2 ^ " << j << ")*" <<  d << ")= " << pow_mod(a, std::pow(2,j)*d, n) << "\n";
        if (pow_mod(a, std::pow(2,j)*d, n) == n - 1) {
            test_b = true;
            break;
        }
    }  
    return test_b;
}

int main(){
    printf("\n\nimplementation of the miller rabin test, \n inspired by numperphile video\n\n");
    std::cout << "please enter number to check for primality\n";
    uint n;
    uint m;
    uint d;
    uint a;

    std::cin >> n;
    std::cout << "please enter witness number\n";
    std::cin >> a;
    
    //prepare n  2^m * d + 1
    uint even_n = n -1;
    d = even_n;
    m = 0;
    while( d % 2 == 0){
        m++;
        d /= 2;
    }
    //debug 
    std::cout << n << " = " << " 2^ " << m << " * " << d << " + 1 \n";

    if(verif_a(a,d,n) || verif_b(a,d,m,n)){
        std::cout << "PASSED \n";
    } else std::cout << "FAIL \n";
    return 0; 
}