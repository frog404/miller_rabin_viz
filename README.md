# miller_rabin_viz

n being the number we want to test for primality (obvioulsy has to be odd and > 2. (for some reason 3 is not being detected as a prime but im to lazy to fix this problem, so we need to start the test at 5).
preparer n sous la forme 2^m * d + 1

take a "witness" number between 1 & n-1
verify if
  a^d =1 (mod n)
  or
  a^((2j)d) = -1 (mod n)
  for j 0<=j<=m-1

if yes test is a PASS
a prime number pass this test for any a

list of super witness needed for the naturals:
2,3 pour                              n < 1 373 653

31, 73 pour                           n < 9 080 191

2,3,5 pour                            n < 25 326 001

2, 13, 23, 1 662 003 pour             n < 1 122 004 669 633

2, 3, 5, 7, 11 pour                   n < 2 152 302 898 747

max uint 64 =                             18 446 744 073 709 551 615

2,3,5,7,11,13,17,19,23,29,31,37 pour  n < 318 665 857 834 031 151 167 461 



to build:

g++ main.cpp -o mr_test_app
./mr_test_app

ressources:
https://www.youtube.com/watch?v=_MscGSN5J6o
https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test
https://mathworld.wolfram.com/Rabin-MillerStrongPseudoprimeTest.html
man g++
