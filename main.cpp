#include <cstdio>
#include<stdlib.h>  //要加
#include <time.h>
#include <stdio.h>
#include "binarySearchTree.h"
#include "treap.h"
using namespace std;

int* random(int* a, int n)
{
    srand((int)time(0));
    for(int i = 1; i <= n; i++ )
    {
        int s = 1 + rand() % (n);
        int m = a[i];
        a[i] = a[s];
        a[s] = m;
    }
    return a;
}

int main()
{
    cout<< "请输入要执行的操作:" <<endl;
    cout<< "输入1-可以执行以下操作:" <<endl;
    cout<< "（1）输入3-输入x,插入x返回层数;" <<endl;
    cout<< "（2）输入4-输入x,删除x返回层数;" <<endl;
    cout<< "（3）输入5-当前Treap树的可视化;" <<endl;
    cout<< "（4）输入0-结束程序;" <<endl;
    cout<< "输入2-对比三种结构插入结果；" <<endl;
    int op;
    if(scanf("%d", &op) != EOF){
        if(op == 1){
            treapTree v;
            while(scanf("%d", &op)){
                if(op == 3){
                    int x;
                    cin>>x;
                    v.insertx(x);
                    v.level();
                }
                else if(op == 4){
                    int x;
                    cin>>x;
                    v.deletex(x);
                    v.level();
                }
                else if(op == 5){
                    /*cout<<"请输入要生成的图片的名称：" <<endl;
                    string an;
                    cin>>an;*/
                    v.output("test");
                    printf("操作成功\n");
                }
                else if(op == 0){
                    return 0;
                }
            }
        }
        else if(op == 2){
            int n;
            cout<< "请输入插入的序列元素个数：(输入0时程序结束)" <<endl;

            while(cin>>n){
                if(n == 0) return 0;
                srand((int)time(0));
                int* a = new int [n + 1];
                for(int i = 1;i <= n;i++)
                    a[i] = (rand() % (12 * n)) * 10 + (i > 10 ? i : (i % 10));
                /*cout<< "请输入要生成的图片的名称(分别为二叉树、Treap树以及随机二叉树)：" <<endl;
                string o, p, q;
                cin>>o>>p>>q;*/
                binarySearchTree b;
                b.init(a, n);
                cout<<"size is "<<b.size()<<endl;
                b.output("binarySearchTree");
                cout<<"The height of the binarySearchTree b is: ";
                b.level();
                treapTree t;
                t.init(a, n);
                t.output("treapTree");
                cout<<"The height of the treapTree t is: ";
                t.level();
                random(a, n);
                binarySearchTree r;
                r.init(a, n);
                r.output("random_binarySearchTree");
                cout<<"The height of the binarySearchTree r is: ";
                r.level();
                printf("操作成功\n");
            }
        }
    }
}
