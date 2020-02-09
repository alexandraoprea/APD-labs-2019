package BinarySearch;

public class BinarySearch {

    static int makeSearch(int v[], int l, int r, int x) {
        while(l <= r) {
            int m = l + (r - l)/2;
            if(v[m] == x) {
                return m;
            }
            else if (v[m] < x) {
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        return -1;
    }

    public static void main(String args[]) {
        int v[] = {1, 2, 3, 4, 5};
        int n = v.length;
        int x = 3;
        int res = makeSearch(v, 0, n-1, x);
        if(res != -1) {
            System.out.println("YES");
        }
        else {
            System.out.println("NO");
        }
    }
}
