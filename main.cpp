#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

void day1_1() {
    std::fstream file("inputs/day1.txt");

    std::vector<int> nums1;
    std::vector<int> nums2;

    int num;
    while (file >> num) {
        nums1.push_back(num);
        file >> num;
        nums2.push_back(num);
    }

    std::ranges::sort(nums1);
    std::ranges::sort(nums2);
    int ans = 0;
    for (auto [n1, n2] : std::views::zip(nums1, nums2)) {
        ans += std::abs(n1 - n2);
    }

    std::cout << ans << std::endl;
}

void day1_2() {
    std::fstream file("inputs/day1.txt");

    std::vector<int> nums1;
    std::vector<int> nums2;

    int num;
    while (file >> num) {
        nums1.push_back(num);
        file >> num;
        nums2.push_back(num);
    }

    std::ranges::sort(nums1);
    std::map<int, int> m;

    int ans = 0;
    for (auto [n1, n2] : std::views::zip(nums1, nums2)) {
        m[n2]++;
    }

    for (auto [n1, n2] : std::views::zip(nums1, nums2)) {
        ans += std::abs(n1 * m[n1]);
    }

    std::cout << ans << std::endl;
}

void day2_1() {
    std::fstream file("inputs/day2.txt");

    std::vector<std::vector<int>> nums;

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            row.push_back(num);
        }
        nums.push_back(row);
    }

    int ans = 0;

    for (auto &row : nums) {
        int decreasing = 0;
        for (int i = 0; i < row.size() - 1; i++) {
            if (row[i] > row[i + 1]) {
                int distance = std::abs(row[i] - row[i + 1]);
                std::bitset<1000> b(0b1110);
                if (b[distance] == 0) {
                    decreasing += 1;
                }
            } else {
                decreasing += 1;
            }
        }

        int increasing = 0;

        for (int i = 0; i < row.size() - 1; i++) {
            if (row[i] < row[i + 1]) {
                int distance = std::abs(row[i] - row[i + 1]);
                std::bitset<1000> b(0b1110);
                if (b[distance] == 0) {
                    increasing += 1;
                }
            } else {
                increasing += 1;
            }
        }

        if (decreasing == 0 || increasing == 0) {
            ans++;
        }
    }

    std::cout << ans << std::endl;
}

void day2_2() {
    std::fstream file("inputs/day2.txt");

    std::vector<std::vector<int>> nums;

    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            row.push_back(num);
        }
        nums.push_back(row);
    }

    int ans = 0;

    for (auto &row : nums) {
        bool decreasing = true;
        int offset = 0;
        bool fucked_up = false;

        for (int i = 0; i < row.size() - 1; i++) {
            if (row[i - offset] > row[i + 1]) {
                int distance = std::abs(row[i - offset] - row[i + 1]);
                if (distance > 3) {
                    if (fucked_up) {
                        decreasing = false;
                        break;
                    }
                    offset = 1;
                    fucked_up = true;
                } else {
                    offset = 0;
                }
            } else {
                if (fucked_up) {
                    decreasing = false;
                    break;
                }
                offset = 1;
                fucked_up = true;
            }
        }

        bool increasing = true;
        offset = 0;
        fucked_up = false;
        for (int i = 0; i < row.size() - 1; i++) {
            if (row[i - offset] < row[i + 1]) {
                int distance = std::abs(row[i - offset] - row[i + 1]);
                if (distance > 3) {
                    if (fucked_up) {
                        increasing = false;
                        break;
                    }
                    offset = 1;
                    fucked_up = true;
                } else {
                    offset = 0;
                }
            } else {
                if (fucked_up) {
                    increasing = false;
                    break;
                }
                offset = 1;
                fucked_up = true;
            }
        }

        if (decreasing || increasing) {
            ans++;
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    std::cout << "day1" << std::endl;
    day1_1();
    day1_2();

    std::cout << "day2" << std::endl;
    day2_1();
    day2_2();

    return 0;
}
