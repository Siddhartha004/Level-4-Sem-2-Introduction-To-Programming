/* SecureScoreAnalyser.c
   Practical 7, Part 2 (c)
   Siddhartha Lama Dong */

#include <stdio.h>
#include <stdbool.h>

#define MAX_STUDENTS   100
#define MIN_SCORE      0
#define MAX_SCORE      100


bool validateArrayParams(int *arr, int size) {
    if (arr == NULL) {
        printf("Error: Array pointer is NULL\n");
        return false;
    }
    if (size <= 0) {
        printf("Error: Invalid array size (%d)\n", size);
        return false;
    }
    if (size > MAX_STUDENTS) {
        printf("Error: Array size too large (%d > %d)\n",
               size, MAX_STUDENTS);
        return false;
    }
    return true;
}

bool validateScore(int score) {
    if (score < MIN_SCORE || score > MAX_SCORE) {
        printf("Error: Score %d is out of valid range [%d, %d]\n",
               score, MIN_SCORE, MAX_SCORE);
        return false;
    }
    return true;
}


bool secureCalculateSum(int *arr, int size, int *result) {
    if (result == NULL) {
        printf("Error: Result pointer is NULL\n");
        return false;
    }
    if (!validateArrayParams(arr, size)) return false;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
    }
    *result = sum;
    return true;
}

bool secureCalculateAverage(int *arr, int size, double *average) {
    if (average == NULL) {
        printf("Error: Average pointer is NULL\n");
        return false;
    }
    if (!validateArrayParams(arr, size)) return false;

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);
    }
    *average = (double)sum / size;
    return true;
}


bool secureFindMax(int *arr, int size, int *maxValue) {
    if (maxValue == NULL) {
        printf("Error: Max pointer is NULL\n");
        return false;
    }
    if (!validateArrayParams(arr, size)) return false;

    int max = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }
    *maxValue = max;
    return true;
}


bool secureFindMin(int *arr, int size, int *minValue) {
    if (minValue == NULL) {
        printf("Error: Min pointer is NULL\n");
        return false;
    }
    if (!validateArrayParams(arr, size)) return false;

    int min = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr + i) < min) {
            min = *(arr + i);
        }
    }
    *minValue = min;
    return true;
}


bool readScore(int studentNum, int *score) {
    if (score == NULL) {
        printf("Error: Score pointer is NULL\n");
        return false;
    }

    printf("  Enter score for student %d (0-100): ", studentNum);

   
    if (scanf("%d", score) != 1) {
        printf("  Error: Non-numeric input detected. Please enter a number.\n");
       
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        return false;
    }

    if (!validateScore(*score)) {
        return false;
    }

    return true;
}


bool readAllScores(int *arr, int size) {
    if (!validateArrayParams(arr, size)) return false;

    printf("Enter scores for %d students:\n", size);

    for (int i = 0; i < size; i++) {
        bool valid = false;
        while (!valid) {
            valid = readScore(i + 1, arr + i);  
            if (!valid) {
                printf("  Please try again.\n");
            }
        }
    }
    return true;
}



void displayScores(int *arr, int size) {
    if (!validateArrayParams(arr, size)) return;

    printf("\n--- Student Scores ---\n");
    for (int i = 0; i < size; i++) {
        printf("  Student %2d: %3d\n", i + 1, *(arr + i));
    }
}

void displayStatistics(int *arr, int size) {
    if (!validateArrayParams(arr, size)) return;

    int    sum = 0, maxScore = 0, minScore = 0;
    double average = 0.0;

    printf("\n--- Statistics ---\n");

    if (secureCalculateSum(arr, size, &sum))
        printf("  Total Score : %d\n", sum);

    if (secureCalculateAverage(arr, size, &average))
        printf("  Average     : %.2f\n", average);

    if (secureFindMax(arr, size, &maxScore))
        printf("  Highest     : %d\n", maxScore);

    if (secureFindMin(arr, size, &minScore))
        printf("  Lowest      : %d\n", minScore);
}




int main() {
    int numStudents;
    int scores[MAX_STUDENTS];

    printf("=== Secure Student Score Analyser ===\n\n");

   
    bool validCount = false;
    while (!validCount) {
        printf("How many students? (1-%d): ", MAX_STUDENTS);
        if (scanf("%d", &numStudents) != 1) {
            printf("Error: Please enter a valid number.\n");
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else if (numStudents < 1 || numStudents > MAX_STUDENTS) {
            printf("Error: Number must be between 1 and %d.\n",
                   MAX_STUDENTS);
        } else {
            validCount = true;
        }
    }

    
    if (!readAllScores(scores, numStudents)) {
        printf("Failed to read scores. Exiting.\n");
        return 1;
    }

   
    displayScores(scores, numStudents);
    displayStatistics(scores, numStudents);


    printf("\n=== Security Edge-Case Tests ===\n");

    int dummy;
    double avg;

    printf("Test - NULL pointer:   ");
    printf("%s\n", secureCalculateSum(NULL, numStudents, &dummy)
                   ? "FAIL" : "PASS (caught NULL)");

    printf("Test - Negative size:  ");
    printf("%s\n", secureCalculateSum(scores, -1, &dummy)
                   ? "FAIL" : "PASS (caught invalid size)");

    printf("Test - Zero size:      ");
    printf("%s\n", secureCalculateAverage(scores, 0, &avg)
                   ? "FAIL" : "PASS (caught zero size)");

    printf("Test - NULL result:    ");
    printf("%s\n", secureFindMax(scores, numStudents, NULL)
                   ? "FAIL" : "PASS (caught NULL result ptr)");

    printf("\nProgram completed securely.\n");
    return 0;
}