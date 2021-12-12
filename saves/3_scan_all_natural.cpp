#include <math.h>
#include <iostream>
#include<vector>

uint64_t pow_mod(uint64_t x, uint64_t y, uint64_t mod){
    if (x == 0 && y == 0) {
        std::cout << "error: 0^0 undefined !";
        return -1;
    }
    else if (y == 0 ) return 1;

    uint64_t r = x% mod;
    for (y; y > 1; --y) {
        r = (r * x) % mod;
    }
    return r;
}

//verif A: a^d =1 (mod n) ?
bool verif_a(uint64_t a, uint64_t d, uint64_t n){
    bool test_a = false;
    int r = pow_mod(a, d, n);
    if ( r == 1) {
        test_a = true; 
    }
    //std::cout << "result of test a = " << r << "\n";
    return test_a;
}

//verif B: a^((2j)d) = -1 (mod n) pour un j tel que 0<=j<=m-1?
bool verif_b(uint64_t a, uint64_t d, uint64_t m, uint64_t n){
    bool test_b = false;
    for (int j=0; j <= m-1; j++){
        //std::cout << "result of test b: " << "a^((2^j)*d) = " << a << "^((2 ^ " << j << ")*" <<  d << ")= " << pow_mod(a, std::pow(2,j)*d, n) << "\n";
        if (pow_mod(a, std::pow(2,j)*d, n) == n - 1) {
            test_b = true;
            break;
        }
    }  
    return test_b;
}

int main(){
    printf("\n\nimplementation of the miller rabin test, \n inspired by numperphile video\n\n");
    uint primes_found = 0;
    for (uint n = 3; n < UINT64_MAX ; n += 2 ){
        uint64_t m;
        uint64_t d;
        std::vector<uint> star_witness;

        if (n == 0){
            std::cout << "error, need non zero uint";
            return 1;
        }else if(n < 1373653){
            star_witness = {2,3};
        }else if(n < 9080191){
            star_witness = {31,73};
        }else if(n < 25326001){
            star_witness = {2,3,5};
        }else if(n < 1122004669633){
            star_witness = {2,13,23,1662003};
        }else if(n < 2152302898747){
            star_witness = {2,3,5,7,11};
        }else{
            star_witness = {2,3,5,7,11,13,17,19,23,29,31,37};
        }
        //std::cout << "size of array = " << star_witness.size() << "first member is = " << star_witness[0] << "Third member is = " << star_witness[2] << "\n""\n";
        bool prime = true;
        for (uint64_t a = 0; a < star_witness.size(); a++){
            //prepare n  2^m * d + 1
            uint64_t even_n = n -1;
            d = even_n;
            m = 0;
            while( d % 2 == 0){
                m++;
                d /= 2;
            }
            //debug 
            //std::cout << n << " = " << " 2^ " << m << " * " << d << " + 1 \n";
            bool va = verif_a(star_witness[a],d,n);
            bool vb = verif_b(star_witness[a],d,m,n);
            if( va || vb ){
                //std::cout << "PASSED for a=" << star_witness[a] << ": test a = " << va << ", test b = "<< vb << "\n";
                ;
            } else { 
                prime = false;
                break;
            }
        }
        for(int i = 0; i < star_witness.size(); i++){} 
        if (prime) {
            primes_found ++;
            std::cout << n << " is prime !";
            std::cout << " Witness are: " ;
            for (uint64_t a = 0; a < star_witness.size(); a++){
                std::cout << star_witness[a] << " ";
            }
            std::cout << ". Primes found so far: " << primes_found << "\n";
        }

        //else std::cout << n << " is NOT prime ! \n";
    }    
    return 0; 
}