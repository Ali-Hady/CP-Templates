bitset<N> notPrime;
void sieve() {
    notPrime[0] = notPrime[1] = 1;
    for(int i = 2; i*i < N; i++) {
        if(notPrime[i]) continue;

        for(int j = i*i; j < N; j+=i)
            notPrime[j] = 1;
    }
}

int add(int a, int b) {
    return (a%mod + b%mod)%mod;
}

int mult(long long a, int b) {
    return ((a%mod)*(b%mod))%mod;
}

int subt(int a, int b) {
    return (((a%mod)-(b%mod))%mod + mod)%mod;
}

int add(long long a, int b) {
    return (a + b + mod)%mod;
}

int mult(long long a, int b) {
    return (a*b)%mod;
}

int fastPower(int base, int power) {
    if(power == 0) return 1;

    int hp = fastPower(base, power/2);
    int fullPower = mult(hp, hp);

    if(power%2 != 0)
        fullPower = mult(fullPower, base);

    return fullPower;
}

int inv(int a) {
    return fastPower(a, mod-2);
}

int divi(int a, int b) {
    return mult(a, inv(b));
}

int fact[N];


int nPr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], fact[n-r]);
}

int nCr(int n, int r) {
    if(r > n) return 0;
    if(n < 0 || r < 0) return 0;
    return divi(fact[n], mult(fact[r], fact[n-r]));
}

int sNb(int n, int k) {
    return nCr(n+k-1, n);
}

void precalFactorial() {
    fact[0] = 1;

    for(int i =1 ; i < N; i++)
        fact[i] = mult(fact[i-1], i);
}

int spf[N];
void SPF() {
    for(int i = 1; i < N; i++)
        spf[i] = i;
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != i) continue;

        for(int j = i*i; j < N; j+=i)
            spf[j] = min(spf[j], i);
    }
}

while(x != 1) {
    int p = spf[x];
    cout <<p <<' ';
    x/=p;
}

short spf[N];
void SPF() {
    for(int i = 2; i*i < N; i++) {
        if(spf[i] != 0) continue;

        for(int j = i*i; j < N; j+=i) {
            if(spf[j] == 0)
                spf[j] = i;
        }
    }
}

while(x != 1) {
    int p = (spf[x] == 0) ? x : spf[x];
    cout <<p <<' ';
    // while(x%p == 0)
    x/=p;
}