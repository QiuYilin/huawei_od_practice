#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// 满减券计算
void manjian(int &price, int &coupon_count, int original_price, int available_a) {
    int max_coupons = min(original_price / 100, available_a);
    coupon_count = max_coupons;
    price = original_price - max_coupons * 10;
}

// 打折券计算
void dazhe(int &price, int &coupon_count, int original_price, int available_b) {
    if (available_b > 0) {//REVIEW 打折券可能为0
        coupon_count = 1;
        price = original_price * 0.92;  // 后面会向下取整
    } else {
        coupon_count = 0;
        price = original_price;
    }
}

// 无门槛券计算（找到最优使用数量）
void wumenkan(int &price, int &coupon_count, int original_price, int available_c) {
    int max_useful = min(original_price / 5, available_c); //REVIEW 无门槛可能溢出
    coupon_count = max_useful;
    price = original_price - 5 * max_useful;
    if (price < 0) price = 0;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    
    int n;
    cin >> n;
    
    vector<int> prices;
    for (int i = 0; i < n; i++) {
        int price;
        cin >> price;
        prices.push_back(price);
    }
    
    for (int i = 0; i < n; i++) {
        int original_price = prices[i];
        int min_price = original_price;  // 不使用优惠券的情况
        int min_coupons = 0;
        
        // REVIEW 只用了单种券也要考虑
        // 1. 单独使用满减券
        int price1, coupons1;
        manjian(price1, coupons1, original_price, a);
        price1 = max(0, price1);  // 价格不能为负
        if (price1 < min_price || (price1 == min_price && coupons1 < min_coupons)) {
            min_price = price1;
            min_coupons = coupons1;
        }
        
        // 2. 单独使用打折券
        int price2, coupons2;
        dazhe(price2, coupons2, original_price, b);
        price2 = max(0, (int)price2);  // 向下取整
        if (price2 < min_price || (price2 == min_price && coupons2 < min_coupons)) {
            min_price = price2;
            min_coupons = coupons2;
        }
        
        // 3. 单独使用无门槛券
        int price3, coupons3;
        wumenkan(price3, coupons3, original_price, c);
        price3 = max(0, price3);
        if (price3 < min_price || (price3 == min_price && coupons3 < min_coupons)) {
            min_price = price3;
            min_coupons = coupons3;
        }
        
        // 两种优惠券组合
        // 1. 满减 + 打折
        if (a > 0 && b > 0) {
            int temp_price1, temp_coupons1;
            manjian(temp_price1, temp_coupons1, original_price, a);
            
            int temp_price2, temp_coupons2;
            dazhe(temp_price2, temp_coupons2, temp_price1, b);
            temp_price2 = max(0, (int)temp_price2);
            
            int total_coupons = temp_coupons1 + temp_coupons2;
            if (temp_price2 < min_price || (temp_price2 == min_price && total_coupons < min_coupons)) {
                min_price = temp_price2;
                min_coupons = total_coupons;
            }
            
            // 另一种顺序：打折 + 满减
            int temp_price3, temp_coupons3;
            dazhe(temp_price3, temp_coupons3, original_price, b);
            
            int temp_price4, temp_coupons4;
            manjian(temp_price4, temp_coupons4, (int)temp_price3, a);
            temp_price4 = max(0, temp_price4);
            
            int total_coupons2 = temp_coupons3 + temp_coupons4;
            if (temp_price4 < min_price || (temp_price4 == min_price && total_coupons2 < min_coupons)) {
                min_price = temp_price4;
                min_coupons = total_coupons2;
            }
        }
        
        // 2. 满减 + 无门槛
        if (a > 0 && c > 0) {
            int temp_price1, temp_coupons1;
            manjian(temp_price1, temp_coupons1, original_price, a);
            
            int temp_price2, temp_coupons2;
            wumenkan(temp_price2, temp_coupons2, temp_price1, c);
            temp_price2 = max(0, temp_price2);
            
            int total_coupons = temp_coupons1 + temp_coupons2;
            if (temp_price2 < min_price || (temp_price2 == min_price && total_coupons < min_coupons)) {
                min_price = temp_price2;
                min_coupons = total_coupons;
            }
        }
        
        // 3. 打折 + 无门槛
        if (b > 0 && c > 0) {
            int temp_price1, temp_coupons1;
            dazhe(temp_price1, temp_coupons1, original_price, b);
            temp_price1 = max(0, (int)temp_price1);
            
            int temp_price2, temp_coupons2;
            wumenkan(temp_price2, temp_coupons2, temp_price1, c);
            temp_price2 = max(0, temp_price2);
            
            int total_coupons = temp_coupons1 + temp_coupons2;
            if (temp_price2 < min_price || (temp_price2 == min_price && total_coupons < min_coupons)) {
                min_price = temp_price2;
                min_coupons = total_coupons;
            }
        }
        
        cout << min_price << " " << min_coupons << endl;
    }
    
    return 0;
}