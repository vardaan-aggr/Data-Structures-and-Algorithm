#include <stdio.h>

int index_teller(int arr[],int target,int num_elements){
    int left=0;
    int right=num_elements-1;
    int result=-1;
    while (right>=left)
    {
        int mid=left+ (right-left)/2;
        if (arr[mid]==target)
        {   result=mid;
            return mid;
        }
        else if (arr[mid]>target)
        {
            right=mid-1;
        }
        else
        {
            left=mid + 1;
        }
        
    }
    return result;
    
}


int left_checker(int arr[],int index,int target){
    if (index==-1)
    {
        return -1;
    }
    if (arr[0]==target)
    {
        return 0;
    }
    
    
      int atmost_left=index;
      while (atmost_left >0 && arr[atmost_left-1]==target)
      {
        atmost_left--;
      }
      return atmost_left;
      
}

int right_checker(int arr[],int index,int target,int num_elements){
    if (index==-1)
    {
        return -1;
    }
    if (arr[num_elements-1]==target)
    {
        return num_elements-1;
    }
    
    
      int atmost_right =index;
      while (atmost_right < num_elements-1 && arr[atmost_right+1]==target)
      {
        atmost_right ++ ;
      }
      return atmost_right;
      
}

int main(){
    int max_in_scrool=100;
    int scroll[max_in_scrool];
    int num_elements=0;
    printf("enter the nums in scrolls if you want to break then enter -1 and press enter");
    printf("\nscroll  : ");
    for (int i = 0; i <max_in_scrool ; i++)
    {   int ele;
        scanf("%d",&ele);
        if (ele==-1 || num_elements>=100)
        {
            break;
        }
        num_elements++;
        scroll[i]=ele;
        

    }

    int target;
    printf("\nplease enter the target : ") ;
    scanf("%d",&target);

    int index=index_teller(scroll,target, num_elements);
    int left=left_checker(scroll,index,target);
    int right=right_checker(scroll,index,target,num_elements);
    printf("[ %d , %d ]",left,right);

    return 0;
}



