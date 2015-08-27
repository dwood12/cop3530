#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

void lin_search(int n, int s, int arr[], int lookup[]);
void bin_search(int n, int s, int arr[], int lookup[]);
void bin_search(int key, int arr[], int low, int high);

//global variables


int main()
{
    int n;
    int s;
    cin >> n >> s;
    int arr[n];
    int lookup[s];

    for(int i = 0 ; i < n; i++)
        cin>> arr[i];

    for(int i = 0 ; i < s; i++)
        cin>> lookup[i];

    cout << "Linear Search:\n";
    lin_search(n,s,arr,lookup);
    cout << "Binary Search:\n";
    bin_search(n,s,arr,lookup);
    return 0;
}

void lin_search(int n, int s, int arr[], int lookup[])
{
    //clock stuff
    clock_t t;
    double elapsed_time;

    t = clock();
    bool value;
    for(int i = 0; i < s; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(arr[j] == lookup[i])
            {
                value = true;
                break;
            }
            else
            {
                value = false;
            }
        }
        if(value)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    t = clock() - t;
    elapsed_time = (double)t;
    cout << elapsed_time << endl;
}

void bin_search(int n, int s, int arr[], int lookup[])
{
    std::sort(arr, arr + n);
    clock_t t;
    double elapsed_time;

    t = clock();
    for(int i = 0; i < s; i++)
    {
        bin_search(lookup[i], arr, 0, n-1);
    }
    t = clock() - t;
    elapsed_time = (double)t;
    cout << elapsed_time << endl;
}

void bin_search(int key, int arr[], int low, int high)
{
    int mid = (low + high)/2;
    if(arr[mid] == key)
        cout << "Yes" << endl;
    else if(low > high)
    {
        cout << "No" << endl;
        return;
    }
    else if(arr[mid] < key)
        bin_search(key,arr,mid+1, high);
    else
        bin_search(key,arr,low,mid-1);
}
