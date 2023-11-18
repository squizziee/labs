#include <iostream>
using namespace std;

void task14() {
    long double W, H, x1, y1, x2, y2, w, h;
    cin >> W >> H >> x1 >> y1 >> x2 >> y2 >> w >> h;
    long double baseTableWidth = fabs(x1 - x2),
                baseTableHeight = fabs(y1 - y2),
                rightDist = W - x2,
                leftDist = x2 - baseTableWidth,
                upperDist = H - y2,
                lowerDist = y2 - baseTableHeight,
                widthDiff = fabs(baseTableWidth - w),
                heightDiff = fabs(baseTableHeight - h);
    if (W <= 0 || w <= 0 || H <= 0 || h <= 0 ||x1 < 0 ||
        x2 < 0 || y1 < 0 || y2 < 0 || w > W || h > H) {
        cout << -1;
        return;
    }
    if (rightDist >= w || leftDist >= w ||
            upperDist >= h || lowerDist >= h) {
        cout << 0;
    } else if (rightDist + leftDist < w &&
               upperDist + lowerDist < h) {
        cout << -1;
    } else if ((widthDiff <= rightDist || widthDiff <= leftDist > 0) && widthDiff > 0) {
        cout << widthDiff;
    } else if ((heightDiff <= upperDist || heightDiff <= lowerDist) && heightDiff > 0) {
        cout << heightDiff;
    }
}

int main() {
    task14();
    return 0;
}