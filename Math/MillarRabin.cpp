long long LargeMulMod(long long lhs, long long rhs, long long mod) {
  long long ret = 0;
  while (rhs > 0) {
    if (rhs & 1) { ret = (ret + lhs) % mod; }
    rhs >>= 1;
    lhs = (lhs + lhs) % mod;
  }
  return ret;
}

long long powmod(long long base, long long power, long long mod) {
  long long ans = 1;
  if (mod < (1 << 30)) {
    while (power > 0) {
      if (power & 1) { ans = ans * base % mod; }
      power >>= 1;
      base = base * base % mod;
    }
  } else {
    while (power > 0) {
      if (power & 1) { ans = LargeMulMod(ans, base, mod); }
      power >>= 1;
      base = LargeMulMod(base, base, mod);
    }
  }
  return ans;
}

bool suspect(long long t, long long s, long long d, long long n) {
  long long x = powmod(t, d, n);
  if (x == 1) { return true; }
  while (s--) {
    if (x == n - 1) { return true; }
    if (n < (1 << 30)) {
      x = x * x % n;
    } else {
      x = LargeMulMod(x, x, n);
    }
  }
  return false;
}

bool isPrime(long long n) {
  if (n <= 1 || (n > 2 && !(n & 1))) { return false; }
  long long d = n - 1;
  long long s = 0;
  while (!(d & 1)) {
    s++;
    d >>= 1;
  }
  //long long test[4] = { 2, 7, 61, 1LL << 60 }; // is for n < 2^32
  long long test[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 1LL << 60 }; // is for n < 10^16 (at least)
  for (int i = 0; test[i] < n; i++) {
    if (!(suspect(test[i], s, d, n))) { return false; }
  }
  return true;
}

