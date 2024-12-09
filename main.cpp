#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <cctype>

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
		std::vector<int> modded_row;

		bool decreasing = false;

		for (size_t orig_index = 0; orig_index < row.size(); orig_index++) {
			bool worked = true;
			modded_row = row;
			modded_row.erase(modded_row.begin() + orig_index);
            for (size_t i = 0; i < modded_row.size() - 1; i++) {
                if (modded_row[i] > modded_row[i + 1]) {
                    int distance = std::abs(modded_row[i] - modded_row[i + 1]);
                    if (distance > 3) {
                        worked = false;
                        break;
                    }
                }
                else {
                    worked = false;
                    break;
                }
            }

			if (worked) {
				decreasing = true;
				break;
			}
		}

		bool increasing = false;

        for (size_t orig_index = 0; orig_index < row.size(); orig_index++) {
            bool worked = true;
			modded_row = row;
			modded_row.erase(modded_row.begin() + orig_index);

            for (size_t i = 0; i < modded_row.size() - 1; i++) {
                if (modded_row[i] < modded_row[i + 1]) {
                    int distance = std::abs(modded_row[i] - modded_row[i + 1]);
                    if (distance > 3) {
                        worked = false;
                        break;
                    }
                }
                else {
                    worked = false;
                    break;
                }
            }

            if (worked) {
                increasing = true;
                break;
            }
        }

        if (decreasing || increasing) {
            ans++;
        }
    }

    std::cout << ans << std::endl;
}


void day3_1() {
	std::fstream file("inputs/day3.txt");
	if (!file.is_open()) {
		std::cout << "day 3 file not found" << std::endl;
		return;
	}
	std::vector<char> lines;
	std::string line;
	while (std::getline(file, line)) {
        for (const auto &c : line) {
			lines.push_back(c);
        }
	}
    std::vector<char> mul_v  = { 'm', 'u', 'l' };
    const std::boyer_moore_searcher searcher(mul_v.begin(), mul_v.end());
	auto start = lines.begin();


    int total = 0;
    while (true) {
        auto iter = std::search(start, lines.end(), searcher);
		if (iter == lines.end()) {
			break;
		}

		// std::cout << "Found at index " << std::distance(lines.begin(), iter) << std::endl;
		int num1 = 0;
		int num2 = 0;
        if (iter[3] == '(') {
			int i = 4;
            while (std::isdigit(iter[i])) {
				num1 = num1 * 10 + (iter[i] - '0');
				i++;
            }

			if (iter[i] == ',') {
				i++;
				while (std::isdigit(iter[i])) {
					num2 = num2 * 10 + (iter[i] - '0');
					i++;
				}

				if (iter[i] == ')') {
					total += num1 * num2;
				}
			}
		}

        
        start = std::next(iter);
    }
	std::cout << total << std::endl;

}


void day3_2() {
    std::fstream file("inputs/day3.txt");
    if (!file.is_open()) {
        std::cout << "day 3 file not found" << std::endl;
        return;
    }
    std::vector<char> lines;
    std::string line;
    while (std::getline(file, line)) {
        for (const auto& c : line) {
            lines.push_back(c);
        }
    }
    std::vector<char> mul_v = { 'm', 'u', 'l' };
    std::vector<char> do_v = { 'd', 'o', '(', ')' };
    std::vector<char> dont_v = { 'd', 'o', 'n', '\'', 't', '(', ')' };

    const std::boyer_moore_searcher  mul_searcher(mul_v.begin(),  mul_v.end());
    const std::boyer_moore_searcher   do_searcher(do_v.begin(),   do_v.end());
    const std::boyer_moore_searcher dont_searcher(dont_v.begin(), dont_v.end());

    auto start = lines.begin();

    int total = 0;
	bool dont = false;
    while (true) {
        auto iter = std::search(start, lines.end(), mul_searcher);
		auto do_iter = std::search(start, lines.end(), do_searcher);
		auto dont_iter = std::search(start, lines.end(), dont_searcher);
        if (iter == lines.end()) {
            break;
        }
		auto mul_distance = std::distance(lines.begin(), iter);
		auto do_distance = std::distance(lines.begin(), do_iter);
		auto dont_distance = std::distance(lines.begin(), dont_iter);

		auto smallest = std::min({ mul_distance, do_distance, dont_distance });
        if (smallest == mul_distance) {
        
        } else if (smallest == do_distance) {
            dont = false;
			start = std::next(do_iter);
			continue;
        } else if (smallest == dont_distance) {
			dont = true;
			start = std::next(dont_iter);
            continue;
		}

        // std::cout << "Found at index " << std::distance(lines.begin(), iter) << std::endl;
        int num1 = 0;
        int num2 = 0;
        if (iter[3] == '(') {
            int i = 4;
            while (std::isdigit(iter[i])) {
                num1 = num1 * 10 + (iter[i] - '0');
                i++;
            }

            if (iter[i] == ',') {
                i++;
                while (std::isdigit(iter[i])) {
                    num2 = num2 * 10 + (iter[i] - '0');
                    i++;
                }

                if (iter[i] == ')') {
                    if(!dont)
                        total += num1 * num2;
                }
            }
        }


        start = std::next(iter);
    }
    std::cout << total << std::endl;

}

int main() {
    std::cout << "day1" << std::endl;
    day1_1();
    day1_2();

    std::cout << "day2" << std::endl;
    day2_1();
    day2_2();

	std::cout << "day3" << std::endl;
    day3_1();
    day3_2();

    return 0;
}
