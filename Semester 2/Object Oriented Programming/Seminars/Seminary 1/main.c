#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
bool isPrime(unsigned int);

bool isPrime(unsigned int n)
{
    if (n<2)
        return false;
    for (int i=2; i<=sqrt(n); i++)
        if (n%i==0)
            return false;
    return true;
}

void sieve(unsigned int n, unsigned int arr[], unsigned int* nrPrimes) {
    bool* sieveArr = (bool*) malloc((n + 2)*sizeof(bool));
    sieveArr[0] = false;
    sieveArr[1] = false;
    for (int i = 2; i <= n; ++i) {
        sieveArr[i] = true;
    }
    unsigned p = 2;
    *nrPrimes=0;
    while (p<=n){
     if (sieveArr[p]==1){
         for (unsigned int i = p * 2; i <= n; i += p) {
             sieveArr[i] = 0;
    }
         *(arr+(*nrPrimes))=p;
         *nrPrimes=*nrPrimes+1;

    }p++;
    }
    free(sieveArr);



}


int main() {
    assert(isPrime(1)==false);
    assert(isPrime(4)==false);
    assert(!isPrime(8));
    assert(isPrime(7)==true);
    assert(isPrime(5));
    assert(isPrime(0)==false);
    assert(isPrime(25)==false);

    unsigned int n, result[1000],nrPrimes;
    //scanf("%u", &n);
    //isPrime(n)? printf("the number %u is prime", n):printf("the number %u is not prime", n);
    n=20;
    sieve(n,result,&nrPrimes);
    for (int i=0;i<nrPrimes;i++)
    {
        printf("%u ",result[i]);
    }
    return 0;
}
