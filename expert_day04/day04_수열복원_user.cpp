/*
 * day04_수열복원_user.cpp
 *
 *  Created on: 2022. 12. 8.
 *      Author: bw
 */

///===== user.cpp =====
extern int orderCheck(int left, int right);

int mydat[100000 + 100];

void mergeSort(int *arr, int s, int e) {

  if (s <= e) {
    return;
  }

  int m = (s + e) / 2;
  mergeSort(arr, s, m);
  mergeSort(arr, m + 1, e);

  int left = s;
  int right = m + 1;
  int k = left;

  while (left <= m && right <= e) {
//    if (arr[left] <= arr[right])
    if (orderCheck(arr[left], arr[right]))
      mydat[k++] = arr[left++];
    else
      mydat[k++] = arr[right++];
  }
  while (left <= m)
    mydat[k++] = arr[left++];
  while (right <= e)
    mydat[k++] = arr[right++];

  for (int nn = s; nn <= e; nn++) {
    arr[nn] = mydat[nn];
  }
}

void array_restore(int arrCount, int dat[]) {
// implement here
  for (int nn = 1; nn <= arrCount; nn++) {
    mydat[nn] = nn - 1;
  }
  mergeSort(mydat, 1, arrCount);
  for (int nn = 1; nn <= arrCount; nn++) {
    dat[mydat[nn]] = nn;
  }

}
