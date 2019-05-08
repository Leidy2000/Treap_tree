#include <cstdio>
#include<stdlib.h>  //Ҫ��
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
    cout<< "������Ҫִ�еĲ���:" <<endl;
    cout<< "����1-����ִ�����²���:" <<endl;
    cout<< "��1������3-����x,����x���ز���;" <<endl;
    cout<< "��2������4-����x,ɾ��x���ز���;" <<endl;
    cout<< "��3������5-��ǰTreap���Ŀ��ӻ�;" <<endl;
    cout<< "��4������0-��������;" <<endl;
    cout<< "����2-�Ա����ֽṹ��������" <<endl;
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
                    /*cout<<"������Ҫ���ɵ�ͼƬ�����ƣ�" <<endl;
                    string an;
                    cin>>an;*/
                    v.output("test");
                    printf("�����ɹ�\n");
                }
                else if(op == 0){
                    return 0;
                }
            }
        }
        else if(op == 2){
            int n;
            cout<< "��������������Ԫ�ظ�����(����0ʱ�������)" <<endl;

            while(cin>>n){
                if(n == 0) return 0;
                srand((int)time(0));
                int* a = new int [n + 1];
                for(int i = 1;i <= n;i++)
                    a[i] = (rand() % (12 * n)) * 10 + (i > 10 ? i : (i % 10));
                /*cout<< "������Ҫ���ɵ�ͼƬ������(�ֱ�Ϊ��������Treap���Լ����������)��" <<endl;
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
                printf("�����ɹ�\n");
            }
        }
    }
}
