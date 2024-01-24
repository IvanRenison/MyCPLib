static random_device rd;
static mt19937_64 gen(rd());
uniform_int_distribution<ull> dis(0, n - 1);
ull r = dis(gen);