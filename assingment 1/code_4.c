#include <stdio.h>

int position_teller(int n) {
    if (n == 1)
        return 1;
    return (position_teller(n - 1) + 2) % n + 1;
}

int main() {
    int n;
    printf("Enter the number of citizens: ");
    scanf("%d", &n);

    printf("The last remaining citizen is at position: %d\n", position_teller(n));
    return 0;
}
