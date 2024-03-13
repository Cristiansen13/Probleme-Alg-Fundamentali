#include <iostream>
#include <vector>
#include <algorithm>

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> S[i];
    }

    std::vector<int> removedElements;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int sum = S[i] + S[j];
            if (isPrime(sum)) {
                if (std::find(removedElements.begin(), removedElements.end(), S[i]) == removedElements.end()) {
                    removedElements.push_back(S[i]);
                }
                if (std::find(removedElements.begin(), removedElements.end(), S[j]) == removedElements.end()) {
                    removedElements.push_back(S[j]);
                }
            }
        }
    }

    std::cout << removedElements.size() << std::endl;
    for (int element : removedElements) {
        std::cout << element << " ";
    }

    return 0;
}
