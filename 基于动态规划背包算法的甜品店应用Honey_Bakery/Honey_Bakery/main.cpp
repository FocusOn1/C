#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

// �������ɫ
void SetColorAndBackground(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

// 01����
// ҵ���߼�
int choose_max_1(vector<int> weight, vector<int> value, int bagWeight){
    // ������ά����
    vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));
    // ��ʼ����ά����
    for(int j = weight[0]; j <= bagWeight; j++) {
        dp[0][j] = value[0];
    }
    // ����Ʒ��ʼ����
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

// ��ȫ����
// �ȱ�����Ʒ���ڱ�������
int choose_max_2(vector<int> weight, vector<int> value, int bagWeight) {
    vector<int> dp(bagWeight + 1, 0);
    // ������Ʒ
    for(int i = 0; i < weight.size(); i++) {
        // ������������
        for(int j = weight[i]; j <= bagWeight; j++) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[bagWeight];
}

// �����˵�
void menu(int &foodChoice) {
    SetColorAndBackground(6,0);
    cout << "================= HONEY BAKERY ================" << endl;
    cout << "             1.��ʽ��̢ ����:5 ����ֵ: 7" << endl;
    cout << "             2.Ĩ����ܽ ����:20 ����ֵ: 15" << endl;
    cout << "             3.�������� ����:25 ����ֵ: 20" << endl;
    cout << "             4.��ݮ����Ȧ ����:30 ����ֵ: 35" << endl;
    cout << "===============================================" << endl;
    SetColorAndBackground(0,7);
    cout << "��ѡ������Ҫ����Ʒ��" << endl;
    cin >> foodChoice;
    cout << "\n" << endl;
}

//ֽ���˵�
void bagMenu(int &bagChoice) {
    SetColorAndBackground(6,0);
    cout << "================= HONEY BAKERY ================" << endl;
    cout << "                 1.С��ֽ�� ����:7" << endl;
    cout << "                 2.�к�ֽ�� ����:15" << endl;
    cout << "                 3.���ֽ�� ����:30" << endl;
    cout << "                 4.�����ֽ�� ����:50" << endl;
    cout << "===============================================" << endl;
    SetColorAndBackground(0,7); // ��ǰ���ױ���
    cout << "��ѡ������Ҫ�Ĵ��ӣ�"  << endl;
    cin >> bagChoice;
    cout << "\n" << endl;
}

// �û�����Ʒ��ѡ��
int userFoodChoice(int foodChoice, vector<int> &w, vector<int> &v, int &buyAgainChoice) {
    vector<string> foodList= {"��ʽ��̢", "Ĩ����ܽ", "��������", "��ݮ����Ȧ"}; //��¼��Ʒ����
    SetColorAndBackground(7,0);
    if(foodChoice == 1){ // ѡ����ʽ��̢
        w.push_back(5);
        v.push_back(7);
    }else if(foodChoice == 2) { // Ĩ����ܽ
        w.push_back(20);
        v.push_back(15);
    }else if(foodChoice == 3) { // ��������
        w.push_back(25);
        v.push_back(20);
    }else if(foodChoice == 4) { // ��ݮ����Ȧ
        w.push_back(30);
        v.push_back(35);
    }
    cout << "���ϰ塿���õģ���ѡ����"<< foodList[foodChoice - 1] << "������Ҫ��������" << endl;
    cout << "���ҡ���1.�ţ����ٿ�����  \n      2.�����ˣ�лл�� " << endl;
    SetColorAndBackground(0,7); // ��ǰ���ױ���
    cout << "��ѡ��" << endl;
    cin >> buyAgainChoice;
    cout << "\n" << endl;
}

// �Դ��ӵ�ѡ��
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

//��Ʒ�����Ƿ�������
int foodNumRandom(){
    srand((unsigned)time(NULL));
    int a = rand() % 2; // Ҫȡ��[0,1]���������
    return a;
}

// ������
int main() {
    int userChoice, foodChoice = 0, bagChoice, buyAgainChoice = 1;
    int count = 0, result, flag = 0; //flag��ʾ��Դ�Ƿ���㣬0�������㣬1������
    vector<int> foodRepeat = {}; // ��������Ʒ��ʣһ��ʱ���洢�û�ѡ����foodChoice����ֹ��ѡ
    vector<int> w = {}; // ���δ洢�û���ѡ��Ʒ��weight
    vector<int> v = {}; // ���δ洢�û���ѡ��Ʒ��value
    vector<string> foodList = {"��ʽ��̢", "Ĩ����ܽ", "��������", "��ݮ����Ȧ"}; //��¼��Ʒ����
    int bagW = 0; // �û���ѡֽ��������
    // �ϰ���ʾ�����˵�
    cout << "���ϰ塿����ӭ����Honey Bakery����������Ҫ��ʲô�� " << endl;
    cout << "���ҡ���1.�ǵģ��Ҹ���������У�����һ���ˣ� \n      2.�����ˣ���ֻ��·������ " << endl;
    SetColorAndBackground(0, 7);
    cout << "��ѡ�� " << endl;
    cin >> userChoice;
    cout << "\n" << endl;
    switch (userChoice) {
        case 1:
            // ��Ʒ��ѡ��
            // �����Ʒ������: 0:ÿ����Ʒ����1��; 1:��Ʒ��������
            if (foodNumRandom() == 0) {//��Դ������
                SetColorAndBackground(7, 0);
                cout << "���ϰ塿:ʵ�ڱ�Ǹ����������̫���ˣ�Ŀǰ����������Ʒ����ʣ���һ���ˡ�" << endl;
                cout << "���ҡ�:û��ϵ��" << endl;
                cout << "���ϰ塿:�õ�,�뿴һ�����ǵĲ˵���" << endl;
                while (buyAgainChoice != 2) {//��Ʒ��w��v���д洢
                    count++;
                    menu(foodChoice);
                    // �����һ�����룬��ôֱ�ӽ�����Ʒ��ѡ��
                    if (count < 2) {
                        userFoodChoice(foodChoice, w, v, buyAgainChoice);
                        foodRepeat.push_back(foodChoice);
                    } else {
                        for (int i = 0; i < foodRepeat.size(); i++) {
                            if (foodChoice == foodRepeat[i]) {
                                SetColorAndBackground(4,0);
                                cout << "[" << foodList[foodRepeat[i] - 1] << "]Ŀǰ�������0�����޷���ѡ��" << endl;
                                break;
                            } else {
                                userFoodChoice(foodChoice, w, v, buyAgainChoice);
                                foodRepeat.push_back(foodChoice);
                            }
                        }
                    }
                }
            } else {//��Դ����
                flag = 1;
                SetColorAndBackground(7, 0);
                cout << "���ϰ塿:�õ�,�뿴�����ǵĲ˵���" << endl;
                cout << "���ҡ�:�õģ�лл��" << endl;
                while (buyAgainChoice != 2) {
                    menu(foodChoice);
                    userFoodChoice(foodChoice, w, v, buyAgainChoice);
                }
            }
            // ���ӵ�ѡ��
            SetColorAndBackground(4,0);
            cout << "[��Ʒѡ�����]" << endl;
            SetColorAndBackground(7, 0);
            cout << "���ϰ塿���õģ���ѡ��һ�´��ӡ�" << endl;
            bagMenu(bagChoice);
            userBagChoice(bagChoice, bagW);
            // ����
            // ��ɹ���
            SetColorAndBackground(7, 0);
            if (flag == 0) {
                result = choose_max_1(w, v, bagW);//�㷨����
            } else {
                result = choose_max_2(w, v, bagW);
            }
            cout << "���ϰ塿��лл���Ļݹˡ�" << endl;
            cout << "���ϰ塿����������ѡ�������Ϊ��" << bagW << "���Ĵ����ܹ�װ����Ʒ���������ֵ�ǣ� " << result << endl;
            break;
        case 2:
            cout << "���ϰ塿��û��ϵ���пճ����������� " << endl;
            break;
    }
    return 0;
}
