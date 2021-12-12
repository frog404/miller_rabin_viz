#include <math.h>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

std::string uint64_to_string( uint64_t value ) {
    std::ostringstream os;
    os << value;
    return os.str();
}

std::string int64_to_string( int64_t value ) {
    std::ostringstream os;
    os << value;
    return os.str();
}

uint point_count = 0;
//std::string point_output = "set style line 1 lc rgbcolor \"#B3FF0000\" pt 5      # red square\nset style line 2 lc rgbcolor \"#B300FF00\" pt 7    # green circle\nset style line 3 lc rgbcolor \"#B30000FF\" pt 9     # blue triangle\nunset key\nplot ";
std::string point_pow_output = "";
std::string point_mult_output = "";
std::string point_div_output = "";
std::string lines_output = "";
std::string prev_point = "0 0";

/* example of valid line = <echo '1 2'"   with points ls 1, \  */

void gnu_point(int64_t a, int64_t b, int64_t col){
    std::string data_line = int64_to_string(a) + " " + int64_to_string(b) + "\n";
    if(col == 1) point_pow_output += data_line;
    else if(col == 2) point_mult_output += data_line;
    else if(col == 3) point_div_output += data_line;
    lines_output += prev_point + "\n" +  int64_to_string(a) + " " + int64_to_string(b) + "\n\n";
    prev_point = int64_to_string(a) + " " + int64_to_string(b);
    point_count++;
}

// power
uint64_t pow_mod(uint64_t x, uint64_t y, uint64_t mod){
    if (x == 0 && y == 0) {
        std::cout << "error: 0^0 undefined !";
        return -1;
    }
    else if (y == 0 ) return 1;

    uint64_t r = x % mod;
    for (y; y > 1; --y) {
    // multiplication
        gnu_point(r,x,2); // 1 = green
        r = (r * x) % mod;
    }
    gnu_point(x,y,1); // 1 = red
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
    for (uint64_t j=0; j <= m-1; j++){
        //std::cout << "result of test b: " << "a^((2^j)*d) = " << a << "^((2 ^ " << j << ")*" <<  d << ")= " << pow_mod(a, std::pow(2,j)*d, n) << "\n";
        // Power, multiplication
        uint64_t p2j = std::pow(2,j);
        gnu_point(2,j,1); // 1 = red
        uint64_t var = p2j * d;
        gnu_point(p2j,d,2); // 2 = green
        gnu_point(a,var,1); // 1 = red
        if (pow_mod(a,var, n) == n - 1) {
            test_b = true;
            break;
        }
    }  
    return test_b;
}

int main(){
    std::cout << "max uint64 = " << UINT64_MAX << "\n";
    printf("\n\nimplementation of the miller rabin test, \n inspired by numperphile video\n\n");
    std::cout << "please enter number to check for primality (must be odd)\n";
    uint64_t n;
    uint64_t m;
    uint64_t d;

    std::cin >> n;
    //uint64_t *star_witness; ==> it is impossible to get a ptr based array length without manually saving it 
    std::vector<uint> star_witness;
    if (n % 2 == 0){
        std::cout << "error, need odd number\n";
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
    bool composite = false;
    for (uint64_t a = 0; a < star_witness.size(); a++){
        //prepare n  2^m * d + 1
        // soustraction
        uint64_t even_n = n -1;
        d = even_n;
        m = 0;
        while( d % 2 == 0){
            m++;
            // division
            d /= 2;
            gnu_point(d,2,3); // 3 = blue
        }
        //debug 
        //std::cout << n << " = " << " 2^ " << m << " * " << d << " + 1 \n";
        bool va = verif_a(star_witness[a],d,n);
        bool vb = verif_b(star_witness[a],d,m,n);
        if( va || vb ){
            std::cout << "PASSED for a=" << star_witness[a] << ": test a = " << va << ", test b = "<< vb << "\n";
        } else {
            std::cout << "FAIL for a=" << star_witness[a] << " test a =" << va << ", test b = "<< vb << "\n";
            composite = true;
            break;
        }
    }
    if (!composite) std::cout << n << " is prime ! \n";
    else std::cout << n << " is NOT prime ! \n";
    

    std::ofstream myfile;
    myfile.open ("power_operations");
    myfile << point_pow_output;
    myfile.close();
    myfile.open ("multiplication_operations");
    myfile << point_mult_output;
    myfile.close();
    myfile.open ("division_operations");
    myfile << point_div_output;
    myfile.close();
    myfile.open ("order");
    myfile << lines_output;
    myfile.close();
    std::string cmd = "gnuplot -p -e \"graph_title = \'miller-rabin test visualisation for " + int64_to_string(n) + "\'\" cmd_gnu.txt";
    system(cmd.c_str());
    return 0; 
}