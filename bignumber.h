// due work: BigInt/BigInt, BigInt%BigInt, pow, sqrt, log, GCD, LCM is still to be written.


typedef std:: vector<int> BigInt;

BigInt big(std:: string s){
    if (s.length() == 0){
        return {};
    }
    BigInt res;
    std:: string temp="";
    for(int i=s.length();i%9;i++) temp += "0";
    s = temp+s;
    for (int i=0;i<s.length();i+=9){
        int val = 0;
        for (int j=i;j<i+9;j++){
                val = val*10+(s[j]-'0');
        }
        res.insert(res.begin(),val);
    }
    return res;
}

BigInt big(long long num){
    std:: string s = "";
    while (num > 0){
        s += char(num%10+'0');
        num /= 10;
    }
    reverse(s.begin(),s.end());
    return big(s);
}

BigInt big(int num) {
    return big((long long) num);
}

std::istream& operator >> (std:: istream &in, BigInt &a) {
    std:: string s;
    getline(std:: cin, s);
    a = big(s);
}

std::ostream& operator << (std:: ostream &out, BigInt a){
    if(a.size()==0) std:: cout<<"0";
    else for(int i=a.size()-1;i>=0;i--) std:: cout<<a[i];
}

bool operator < (BigInt a, BigInt b) {
    //Set(a);
    //Set(b);
    if (a.size() != b.size()) return (a.size() < b.size());
    for(int i=0;i<a.size();i++)
        if (a[i] != b[i]) return (a[i] < b[i]);
    return false;
}

bool operator > (BigInt a, BigInt b) {
    return (b < a);
}

bool operator == (BigInt a, BigInt b) {
    return !((a < b) || (b < a));
}

bool operator <= (BigInt a, BigInt b) {
    return (a < b and a == b);
}

bool operator >= (BigInt a, BigInt b) {
    return (b < a || b == a);
}

bool operator < (BigInt a, int b) {
    return (a < big(b));
}

bool operator > (BigInt a, int b) {
    return (a > big(b));
}

bool operator == (BigInt a, int b) {
    return (a == big(b));
}

bool operator >= (BigInt a, int b) {
    return (a >= big(b));
}

bool operator <= (BigInt a, int b) {
    return (a <= big(b));
}

BigInt max_big(BigInt a, BigInt b) {
    if (a > b) return a;
    return b;
}

BigInt min_big(BigInt a, BigInt b) {
    if (a < b) return a;
    return b;
}
BigInt operator + (BigInt a, BigInt b) {
    //Set(a);
    //Set(b);
    BigInt ans;
    int carry = 0,base=1e9;
    for(int i=0;i<=std:: max(a.size(), b.size())-1;i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        ans.push_back(carry%base);
        carry /= base;
    }
    if (carry) ans.push_back(carry);
    //Set(ans);
    return ans;
}

BigInt operator + (BigInt a, int b) {
    return a + big(b);
}

void operator ++ (BigInt &a) { // ++a
    a = a + 1;
    //return a;
}

void operator += (BigInt &a, BigInt b) {
    a = a + b;
}
void operator += (BigInt &a, int b) {
    a = a + b;
}

BigInt operator - (BigInt a, BigInt b) {
    if(b>a){
        BigInt temp;
        temp=a;
        a = b;
        b = temp;
    }
    BigInt ans;
    int carry = 0,base=1e9;
    for(int i=0;i<a.size();i++) {
        carry += a[i] - (i < b.size() ? b[i] : 0);
        if (carry < 0) ans.push_back(carry+base), carry = -1;
        else ans.push_back(carry), carry = 0;
    }
    ans[ans.size()-1] *= -1;
    return ans;
}

BigInt operator - (BigInt a, int b) {
    return a - big(b);
}

void operator -- (BigInt &a) { // --a
    a = a - 1;
}

void operator -= (BigInt &a, BigInt b) {
    a = a - b;
}

void operator -= (BigInt &a, int b) {
    a = a - b;
}

BigInt operator * (BigInt a, BigInt b) {
    BigInt ans;
    ans.resize(a.size()+b.size(), 0);
    for(int i=0;i<a.size();i++) {
        long long carry = 0ll;
        int base = 1e9;
        for (int j=0;j<b.size() || carry > 0;j++) {
            long long s = ans[i+j] + carry + (long long)a[i]*(j<b.size()?(long long)b[j]:0ll);
            ans[i+j] = s%base;
            carry = s/base;
        }
    }
    while (ans.size() > 1 && ans.back() == 0) ans.pop_back();
    return ans;
}

BigInt operator * (BigInt a, int b) {
    return a * big(b);
}

void operator *= (BigInt &a, BigInt b) {
    a = a * b;
}

void operator *= (BigInt &a, int b) {
    a = a * b;
}

BigInt operator / (BigInt a, int b) {
    BigInt ans;
    long long cur = 0ll, base=1e9;
    for(int i=a.size()-1;i>=0;i--) {
        cur = (cur*(long long)base + (long long)a[i]);
        ans.insert(ans.begin(),cur/b);
        cur %= b;
    }
    return ans;
}


void operator /= (BigInt &a, int b) {
    a = a / b;
}

int operator % (BigInt a, int b) {
    int base = 1e9;
    if (b == 0) return -1;
    int ans = 0;
    for(int i=a.size()-1;i>=0;i--)
        ans = (ans*(base%b) + a[i]%b)%b;
    return ans;
}

int operator %= (BigInt &a, int b) {
    return a % b;
}

