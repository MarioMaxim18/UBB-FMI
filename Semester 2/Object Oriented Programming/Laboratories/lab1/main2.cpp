#include <iostream>

int main() {
    for(int i=3210;i<10000;i++){
        bool isok = true;
        int copy = i;
        int digits[4];
        for(int i = 0; i<4 ;i++) {
            digits[i] = copy%10;
            copy/=10;
        }
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                if(digits[i]==digits[j]&&i!=j){
                    isok = false;
                }
        if(isok&&digits[0]<digits[1]&&digits[1]<digits[2]&&digits[2]<digits[3]) {
            int sum = digits[0] + digits[1] + digits[2] + digits[3];
            if(sum==24)
                std::cout<<i<<std::endl;
        }

    }
    return 0;
}
