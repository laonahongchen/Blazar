typedef complex<double> Complex;
const double pi = acos(-1);
void FFT(vector<Complex>&num, int len, int ty) {
    for(int i = 1, j = 0; i < len - 1; i++) {
        for(int k = len; j ^= k >>= 1, ~j & k;);
        if(i < j)
            swap(num[i], num[j]);
    }
    for(int h = 0; (1 << h) < len; h++) {
        int step = 1 << h, step2 = step << 1;
        Complex w0(cos(2.0 * pi / step2), ty * sin(2.0 * pi / step2));
        for(int i = 0; i < len; i += step2) {
            Complex w(1, 0);
            for(int j = 0; j < step; j++) {
                Complex &x = num[i + j + step];
                Complex &y = num[i + j];
                Complex d = w * x;
                x = y - d;
                y = y + d;
                w = w * w0;
            }
        }
    }
    if(ty == -1)
        for(int i = 0; i < len; i++)
            num[i] = Complex(num[i].real() / (double)len, num[i].imag());
}
vector<Complex> mul(vector<Complex>a, vector<Complex>b) {
    int len = a.size() + b.size();
    while((len & -len) != len) len++;
    while(a.size() < len) a.push_back(Complex(0, 0));
    while(b.size() < len) b.push_back(Complex(0, 0));
    FFT(a, len, 1);
    FFT(b, len, 1);
    vector<Complex> ans(len);
    for(int i = 0; i < len; i++)
        ans[i] = a[i] * b[i];
    FFT(ans, len, -1);
    return ans;
}
