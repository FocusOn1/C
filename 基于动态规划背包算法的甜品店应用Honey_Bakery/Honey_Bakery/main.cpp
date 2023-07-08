#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// 字体带颜色
void SetColorAndBackground(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

// 01背包
// 业务逻辑
int choose_max_1(vector<int> weight, vector<int> value, int bagWeight){
    // 创建二维数组
    vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));
    // 初始化二维数组
    for(int j = weight[0]; j <= bagWeight; j++) {
        dp[0][j] = value[0];
    }
    // 从物品开始遍历
    for(int i = 1; i < weight.size(); i++) {
        for(int j = 0; j <= bagWeight; j++) {
            if(j < weight[i]) {
                dp[i][j] = dp[i - 1][j];
            }else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
    }

    return dp[weight.size() - 1][bagWeight];
}

// 完全背包
// 先遍历物品，在遍历背包
int choose_max_2(vector<int> weight, vector<int> value, int bagWeight) {
    vector<int> dp(bagWeight + 1, 0);
    // 遍历物品
    for(int i = 0; i < weight.size(); i++) {
        // 遍历背包容量
        for(int j = weight[i]; j <= bagWeight; j++) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

// 面包店菜单
void menu(int &foodChoice) {
    SetColorAndBackground(6,0);
    cout << "================= HONEY BAKERY ================" << endl;
    cout << "             1.葡式蛋挞 重量:5 能量值: 7" << endl;
    cout << "             2.抹茶泡芙 重量:20 能量值: 15" << endl;
    cout << "             3.提拉米苏 重量:25 能量值: 20" << endl;
    cout << "             4.草莓甜甜圈 重量:30 能量值: 35" << endl;
    cout << "===============================================" << endl;
    SetColorAndBackground(0,7);
    cout << "请选择你想要的甜品：" << endl;
    cin >> foodChoice;
    cout << "\n" << endl;
}

//纸袋菜单
void bagMenu(int &bagChoice) {
    SetColorAndBackground(6,0);
    cout << "================= HONEY BAKERY ================" << endl;
    cout << "                 1.小号纸袋 容量:7" << endl;
    cout << "                 2.中号纸袋 容量:15" << endl;
    cout << "                 3.大号纸袋 容量:30" << endl;
    cout << "                 4.超大号纸袋 容量:50" << endl;
    cout << "===============================================" << endl;
    SetColorAndBackground(0,7); // 黑前景白背景
    cout << "请选择你想要的袋子："  << endl;
    cin >> bagChoice;
    cout << "\n" << endl;
}

// 用户对甜品的选择
int userFoodChoice(int foodChoice, vector<int> &w, vector<int> &v, int &buyAgainChoice) {
    vector<string> foodList= {"葡式蛋挞", "抹茶泡芙", "提拉米苏", "草莓甜甜圈"}; //记录甜品种类
    SetColorAndBackground(7,0);
    if(foodChoice == 1){ // 选择葡式蛋挞
        w.push_back(5);
        v.push_back(7);
    }else if(foodChoice == 2) { // 抹茶泡芙
        w.push_back(20);
        v.push_back(15);
    }else if(foodChoice == 3) { // 提拉米苏
        w.push_back(25);
        v.push_back(20);
    }else if(foodChoice == 4) { // 草莓甜甜圈
        w.push_back(30);
        v.push_back(35);
    }
    cout << "【老板】：好的，你选择了"<< foodList[foodChoice - 1] << "，还需要其它的吗？" << endl;
    cout << "【我】：1.嗯，我再看看。  \n      2.不用了，谢谢。 " << endl;
    SetColorAndBackground(0,7); // 黑前景白背景
    cout << "你选择：" << endl;
    cin >> buyAgainChoice;
    cout << "\n" << endl;
}

// 对袋子的选择
int userBagChoice(int bagChoice, int &bagW){
    switch(bagChoice) {
        case 1:
            bagW = 7;
            break;
        case 2:
            bagW = 15;
            break;
        case 3:
            bagW = 30;
            break;
        case 4:
            bagW = 50;
            break;
    }
    return 0;
}

//甜品存量是否充足随机
int foodNumRandom(){
    srand((unsigned)time(NULL));
    int a = rand() % 2; // 要取得[0,1]的随机整数
    return a;
}

// 主函数
int main() {
    int userChoice, foodChoice = 0, bagChoice, buyAgainChoice = 1;
    int count = 0, result, flag = 0; //flag表示货源是否充足，0：不充足，1：充足
    vector<int> foodRepeat = {}; // 当所有物品仅剩一件时，存储用户选过的foodChoice，防止重选
    vector<int> w = {}; // 依次存储用户所选甜品的weight
    vector<int> v = {}; // 依次存储用户所选甜品的value
    vector<string> foodList = {"葡式蛋挞", "抹茶泡芙", "提拉米苏", "草莓甜甜圈"}; //记录甜品种类
    int bagW = 0; // 用户所选纸袋的容量
    // 老板显示面包店菜单
    cout << "【老板】：欢迎光临Honey Bakery！请问您需要买什么吗？ " << endl;
    cout << "【我】：1.是的，我刚来这个城市，饿了一天了！ \n      2.不用了，我只是路过。。 " << endl;
    SetColorAndBackground(0, 7);
    cout << "你选择： " << endl;
    cin >> userChoice;
    cout << "\n" << endl;
    switch (userChoice) {
        case 1:
            // 甜品的选择
            // 随机甜品存货情况: 0:每个甜品仅存1件; 1:甜品存量充足
            if (foodNumRandom() == 0) {//货源不充足
                SetColorAndBackground(7, 0);
                cout << "【老板】:实在抱歉！今天生意太火了，目前店里所有甜品都仅剩最后一件了。" << endl;
                cout << "【我】:没关系！" << endl;
                cout << "【老板】:好的,请看一下我们的菜单。" << endl;
                while (buyAgainChoice != 2) {//甜品的w、v进行存储
                    count++;
                    menu(foodChoice);
                    // 如果第一次输入，那么直接进入甜品的选择
                    if (count < 2) {
                        userFoodChoice(foodChoice, w, v, buyAgainChoice);
                        foodRepeat.push_back(foodChoice);
                    } else {
                        for (int i = 0; i < foodRepeat.size(); i++) {
                            if (foodChoice == foodRepeat[i]) {
                                SetColorAndBackground(4,0);
                                cout << "[" << foodList[foodRepeat[i] - 1] << "]目前库存量：0，已无法再选择。" << endl;
                                break;
                            } else {
                                userFoodChoice(foodChoice, w, v, buyAgainChoice);
                                foodRepeat.push_back(foodChoice);
                            }
                        }
                    }
                }
            } else {//货源充足
                flag = 1;
                SetColorAndBackground(7, 0);
                cout << "【老板】:好的,请看下我们的菜单。" << endl;
                cout << "【我】:好的，谢谢。" << endl;
                while (buyAgainChoice != 2) {
                    menu(foodChoice);
                    userFoodChoice(foodChoice, w, v, buyAgainChoice);
                }
            }
            // 袋子的选择
            SetColorAndBackground(4,0);
            cout << "[甜品选购完毕]" << endl;
            SetColorAndBackground(7, 0);
            cout << "【老板】：好的，请选择一下袋子。" << endl;
            bagMenu(bagChoice);
            userBagChoice(bagChoice, bagW);
            // 结账
            // 完成购物
            SetColorAndBackground(7, 0);
            if (flag == 0) {
                result = choose_max_1(w, v, bagW);//算法调用
            } else {
                result = choose_max_2(w, v, bagW);
            }
            cout << "【老板】：谢谢您的惠顾。" << endl;
            cout << "【老板】：先生，您选择的容量为【" << bagW << "】的袋子能够装下物品的最大能量值是： " << result << endl;
            break;
        case 2:
            cout << "【老板】：没关系，有空常来看看啊。 " << endl;
            break;
    }
    return 0;
}
