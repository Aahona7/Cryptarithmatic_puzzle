#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char op1[10], op2[10], sum[10];
int used_digits[10];
int map[26]; // mapping from character to digits
int len;

void input();
void solve(int pos, int carry);
int evaluate();
void call_findsolution();

int solution_count = 0;

void input() {
    int i;
    printf("\nEnter the operands and sum character-wise.\n");
    printf("When you are finished entering each number, press Enter key.\n\n");

    printf("Enter Operand 1: ");
    for (i = 0;; i++) {
        scanf("%c", &op1[i]);
        if (op1[i] == '\n') {
            op1[i] = '\0';
            len = i;
            break;
        }
    }

    printf("\nEnter Operand 2: ");
    for (i = 0;; i++) {
        scanf("%c", &op2[i]);
        if (op2[i] == '\n') {
            op2[i] = '\0';
            break;
        }
    }

    printf("\nEnter Sum: ");
    for (i = 0;; i++) {
        scanf("%c", &sum[i]);
        if (sum[i] == '\n') {
            sum[i] = '\0';
            break;
        }
    }
}

void print_solution() {
    printf("\nSolution found:\n");
    printf("\nOperand 1: ");
    for (int i = 0; i < len; i++)
        printf("%d", map[op1[i] - 'A']);
    printf("\nOperand 2: ");
    for (int i = 0; i < len; i++)
        printf("%d", map[op2[i] - 'A']);
    printf("\nSum: ");
    for (int i = 0; i < len; i++)
        printf("%d", map[sum[i] - 'A']);
}

void solve(int pos, int carry) {
    if (pos == -1) {
        if (carry == 0) {
            print_solution();
            solution_count++;
            call_findsolution();
        }
        return;
    }

    int a = op1[pos] - 'A';
    int b = op2[pos] - 'A';
    int c = sum[pos] - 'A';

    int va = map[a];
    int vb = map[b];
    int vc = map[c];

    for (int da = (va == -1 ? 0 : va); da <= (va == -1 ? 9 : va); da++) {
        if (va == -1 && used_digits[da]) continue;
        for (int db = (vb == -1 ? 0 : vb); db <= (vb == -1 ? 9 : vb); db++) {
            if (vb == -1 && used_digits[db]) continue;

            int sum_ab = da + db + carry;
            int dc = sum_ab % 10;
            int new_carry = sum_ab / 10;

            if (vc != -1 && vc != dc) continue;
            if (vc == -1 && used_digits[dc]) continue;

            // Check leading zeros
            if (pos == 0) {
                if ((op1[0] && da == 0) || (op2[0] && db == 0) || (sum[0] && dc == 0))
                    continue;
            }

            int undo_a = 0, undo_b = 0, undo_c = 0;

            if (va == -1) { map[a] = da; used_digits[da] = 1; undo_a = 1; }
            if (vb == -1) { map[b] = db; used_digits[db] = 1; undo_b = 1; }
            if (vc == -1) { map[c] = dc; used_digits[dc] = 1; undo_c = 1; }

            solve(pos - 1, new_carry);

            if (undo_a) { used_digits[da] = 0; map[a] = -1; }
            if (undo_b) { used_digits[db] = 0; map[b] = -1; }
            if (undo_c) { used_digits[dc] = 0; map[c] = -1; }
        }
    }
}

void call_findsolution() {
    char ques;
    printf("\n\nDo you want another solution if it exists (y/Y)? : ");
    scanf(" %c", &ques);
    if (ques == 'y' || ques == 'Y') {
        return; // continue searching
    } else {
        exit(0);
    }
}

int main() {
    memset(map, -1, sizeof(map));
    memset(used_digits, 0, sizeof(used_digits));

    input();
    solve(len - 1, 0);

    if (solution_count == 0) {
        printf("\nNo solution exists.\n");
    }
    return 0;
}
