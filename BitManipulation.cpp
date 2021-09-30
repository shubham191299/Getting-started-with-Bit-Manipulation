#include<bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define ll long long int

//Unique number
//Given a list of numbers where every no. occurs twice except one. find that no.
int UniqueNum(int n){

    vi v;
    int ans=0;
    int no;
    for(int i = 0; i<n ; i++){
        cin>>no;
        ans ^= v[i];  //Bitwise XOR.
    }
    return ans;
}

bool isOdd(int n){
    return (n&1);
}

//Find the ith bit.
int getBit(int n, int i){
    int mask = 1<<i;
    int bit = (n & mask)>0?1:0;
    return bit;
}

//Set ith bit. (Sets 1 at ith position.
int setBit(int n,int i){
    int mask = 1<<i;
    int ans = n | mask;
    return ans;
}

//Clear ith bit
void clearBit(int &n, int i){
    int mask = ~(1<<i); //0101 clear i=2
    n &=mask;           //&1011 -> 0001 (1<<i will give 0100 then we flip bits
                        //using ~ then we will get 1011.
}

// update value v at position i;
void updateBit(int &n, int i , int v){

    int mask = ~(1<<i);
    int clear_bit = mask & n;  // We don't know which bit is present at i so we clear it first.
    n = clear_bit | (v<<i);
}

void clearLastIBits(int &n,int i){
    int mask = -1<<i;  // -1 = 11111111,  ~0 = 11111111.
    n &= mask;    // from position i+1 to 0; and i is our no. of bits.
}

int clearRangeItoJ(int n, int i, int j){
    int a = (1<<(j-i+1)) -1;  // for(n=31 , i=1, j=3) we get 8-1=7 here.
    int mask = ~(a<<i);   //here i get mask as 17 = ~14.
    return mask & n;
    /*
            OR
     int ones = ~0;
     int a = ones<<(j+1);
     int b = (1<<i) -1;
     int mask = a | b;
     return n & mask;

     */
}

// Given 2 no. N, M replace bits from i to j in N by M.
int replaceBitsInRange(int n,int m,int i, int j){
    int ones = ~0;
    int a = ones<<(j+1);
    int b = (1<<i) -1;
    int mask = a | b;
    int cleared_bit_no = n & mask;   //cleared bits from I to J.
    int replaced_bits = cleared_bit_no | (m<<i);
    return replaced_bits;
}

// Find no. of set bits in n. TC= O(logn).
int countSetBits(int n){
    int ones = 0;
    while(n){
        ones += n & 1;
        n=n>>1;
    }
    return ones;
}

int countSetBitsFast(int n){  // TC = O(No. of Ones/set bits).
    int ones = 0;
    while(n){
        n = n & (n-1);
        ones++;
    }
    return ones;
}

int countSetBitsUsingInbuiltFunc(int n){
    return __builtin_popcount(n);
}

void decimalToBinaryRecursion(int n){
    int last_bit = n&1;
    if(n){
        decimalToBinaryRecursion(n>>1);
        cout<<last_bit<<" ";
    }
}

int decimalToBinary(int n){
    int ans =0;
    int power = 1;
    while (n){
        int last_bit = n&1;
        ans+= power*last_bit;
        power *=10;
        n = n>>1;
    }
    return ans;
}

// Find two unique no. in an array in which every no. is repeated twice.
void findTwoUniqueNo(){
    int n;
    cin>>n;
    vi v(n);
    int Xor = 0;
    for(int i = 0;i<n; i++){
        int a;
        cin>>a;
        v[i]=a;
        Xor^=a;
    }
    // Xor = a^b
    int temp = Xor;
    int pos =0;
    while(!(temp&1)){ //temp&1 is the last bit.
        pos++;
        temp = temp>>1;
    }  // It will give the position of first 1 from LHS in Xor.
    int mask = 1<<pos;

    // find those numbers which contain set bit at position pos.
    int a=0;
    int b=0;
    for(int i =0; i<n; i++){
        if((mask&v[i])>0){
            a = a^v[i];  // Here we'll get our a.
        }
    }
    b = Xor^a;  // using the property of Xor i.e, xor = a^b => a^xor=b.
    cout<<min(a,b)<<" "<<max(a,b)<<endl;

}

// Find a unique no. in an array in which each no. is occurring thrice.(3N+1)
void findOneUniqueNo(){
    int count[64]={0}; // 64 because we can have maximum 64 bits. (O(1) coz constant array.)
    int n;
    cin>>n;
    vi v(n);
    for(int i = 0;i<n; i++){
        int a;
        cin>>a;
        v[i]=a;
        // Update the count array by extracting bits.
        int j=0;
        while(a){
            int last_bit = (a&1);
            count[j++]+=last_bit;
            a= a>>1;
        }
    }
    //Iterate over the array and reduce every no to %3 coz the sum of last bit will always be
    // 3N or 3N+1(in case of unique no.)
    //then form the ans by converting 0s and 1s into a number.
    int pow = 1;
    int ans = 0;
    for (int i = 0; i < 64; ++i) {
        count[i]%=3;
        ans += pow*count[i];
        pow = pow<<1; // OR pow*2.
    }
    cout<<ans;
}

void power_optimized(int a,int n){
    // We'll have to find a^n.  TC = O(logn).
    int ans =1;

    while(n){
        int last_bit = (n&1);
        if(last_bit){
            ans*=a;
        }
        a*=a;  // Square up
        n = n>>1;  // Discard the last bit of a.
    }
    cout<<ans;
}

void filterChars(int n , char a[]){  // Ex. n=5=101, a = {'a','b','c'} then filter will
                                     // print a,c. means character in place of set bits
    int j =0 ;
    while(n){
        int last_bit = n&1;
        if(last_bit){
            cout<<a[j];
        }
        j++;
        n = n>>1;
    }
    cout<<"\n";
}

//To print subsets of a string.
void printSubset(char a[]){
    int n = strlen(a);
    for(int i =0; i<(1<<n); i++){
        filterChars(i,a);
    }
}

// Find how many numbers are there in n which are divisible by all primes less then 20.
void inclusionExclusion(){
    ll t;
    cin>>t;
    ll primes[]={2,3,5,7,11,13,17,19};
    while(t--){
        ll n;
        cin>>n;
        ll subsets = 1<<8; // 8 primes which are less then 20.
        ll ans =0;
        for(ll i =1 ; i<subsets; i++){  // Iteration over all subsets. (i =1 coz we don't want to include null)
            ll denominator = 1ll; // 1ll means 1 of type long long.
            ll setBits = __builtin_popcount(i);
            for(ll j =0; j<8;j++){
                if(i&(1<<j)){
                    denominator*=primes[j];
                }
            }
            if(setBits&1){     // if setBits&1 is odd then add otherwise sub from ans.
                ans+=n/denominator;
            }
            else {
                ans-=n/denominator;
            }
        }
        cout<<ans<<endl;
    }


}

// Square of a number w/o using pow , / , *.  TC = O(Logn)
int squareUsingBitManRec(int n){
    /*
     * square(n) = 0 if n == 0
      if n is even
         square(n) = 4*square(n/2)
      if n is odd
         square(n) = 4*square(floor(n/2)) + 4*floor(n/2) + 1

    Examples
      square(6) = 4*square(3)
      square(3) = 4*(square(1)) + 4*1 + 1 = 9
      square(7) = 4*square(3) + 4*3 + 1 = 4*9 + 4*3 + 1 = 49

      How it works is -->
      If n is even, it can be written as
      n = 2*x
      n2 = (2*x)2 = 4*x2
      If n is odd, it can be written as
      n = 2*x + 1
      n2 = (2*x + 1)2 = 4*x2 + 4*x + 1
     */
    if(n<0){
        n = -n;  //To avoid negative numbers.
    }
    if(n==0) return 0;
    int x = n>>1; // x = n/2;

    if (n & 1)  return (squareUsingBitManRec(x) << 2) + (x<<2) +1;
    else // if even
    return (squareUsingBitManRec(x)<<2);

}

int squareUsingBitMan(int n){
    /*
     * For a given number `num` we get square of it by multiplying number as `num * num`.
    Now write one of `num` in square `num * num` in terms of power of `2`. Check below examples.

    Eg: num = 10, square(num) = 10 * 10
                              = 10 * (8 + 2) = (10 * 8) + (10 * 2)
        num = 15, square(num) = 15 * 15
                              = 15 * (8 + 4 + 2 + 1) = (15 * 8) + (15 * 4) + (15 * 2) + (15 * 1)

    Multiplication with power of 2's can be done by left shift bitwise operator.
     */
    if(n<0) n = -n;
    int res = 0, times =n;
    while(times >0){
        int presentShift =0 , currShift = 1;
        while ((currShift<<1)<=times){
            currShift<<=1;      //For n=15 , currShift contains 8,4,2,1
            presentShift++;     // presentShift contains 3,2,1,0
        }
        times -=currShift;      // times contains 7,3,1,0
        res +=(n<<presentShift);// res = 120+60+30+15=225
    }
    return res;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif

    std::ios::sync_with_stdio(false);
    cout<<squareUsingBitMan(15);
}