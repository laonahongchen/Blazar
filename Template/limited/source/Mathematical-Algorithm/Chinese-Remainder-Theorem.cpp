bool solve(int n, std::pair<long long, long long> input[],
                  std::pair<long long, long long> &output) {
	output = std::make_pair(1, 1);
	for (int i = 0; i < n; ++i) {
		long long number, useless; // euclid(a, b, x, y)
		euclid(output.second, input[i].second, number, useless);
		long long divisor = std::__gcd(output.second, input[i].second);
		if ((input[i].first - output.first) % divisor) return false;
		number *= (input[i].first - output.first) / divisor;
		fix(number, input[i].second);
		output.first += output.second * number;
		output.second *= input[i].second / divisor;
		fix(output.first, output.second);
	}
	return true;
}
