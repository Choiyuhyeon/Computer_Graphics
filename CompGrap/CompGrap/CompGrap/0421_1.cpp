#include <iostream>
#include <vector>
#include <cmath>
#include <GL/glut.h>

struct Point2D {
    float x;
    float y;
};

class BezierCurve2D {
private:
    std::vector<Point2D> controlPoints;

public:
    BezierCurve2D(const std::vector<Point2D>& pts) : controlPoints(pts) {}

    Point2D Evaluate(float t) const {
        // De Casteljau's algorithm
        std::vector<Point2D> tempPts = controlPoints;
        int n = tempPts.size();
        
        for (int r = 1; r <= n; ++r) {
            for (int i = 0; i < n - r; ++i) {
                tempPts[i].x = (1 - t) * tempPts[i].x + t * tempPts[i + 1].x;
                tempPts[i].y = (1 - t) * tempPts[i].y + t * tempPts[i + 1].y;
            }
        }
        
        return tempPts[0];
    }

    // Calculate the slope (y-derivative/x-derivative) at t
    float SlopeAt(float t) const {
        Point2D dp = DerivativeAt(t);
        return dp.y / dp.x;
    }

    // Calculate the derivative at t
    Point2D DerivativeAt(float t) const {
        std::vector<Point2D> tempPts = controlPoints;
        int n = tempPts.size() - 1;
        
        for (int i = 0; i < n; ++i) {
            tempPts[i].x = n * (tempPts[i + 1].x - tempPts[i].x);
            tempPts[i].y = n * (tempPts[i + 1].y - tempPts[i].y);
        }

        return Evaluate(t, tempPts);
    }

private:
    Point2D Evaluate(float t, const std::vector<Point2D>& pts) const {
        // De Casteljau's algorithm
        std::vector<Point2D> tempPts = pts;
        int n = tempPts.size();
        
        for (int r = 1; r <= n; ++r) {
            for (int i = 0; i < n - r; ++i) {
                tempPts[i].x = (1 - t) * tempPts[i].x + t * tempPts[i + 1].x;
                tempPts[i].y = (1 - t) * tempPts[i].y + t * tempPts[i + 1].y;
            }
        }
        
        return tempPts[0];
    }
};

int main(int argc, char** argv) {
    std::vector<Point2D> ctrlPts = { {100, 100}, {200, 300}, {400, 200}, {500, 400} };
    
    BezierCurve2D curve(ctrlPts);

    std::vector<float> slopes;

    for (int i = 0; i <= 100; ++i) {
        float t = i / 100.0;
        float slope = curve.SlopeAt(t);
        slopes.push_back(slope);
    }

    // Find monotonic regions
    int prevSign = 0; // 0: not set, 1: increasing, -1: decreasing
    int startIdx = 0;
    for (int i = 1; i < slopes.size(); ++i) {
        int sign = (slopes[i] > slopes[i - 1]) ? 1 : (slopes[i] < slopes[i - 1]) ? -1 : 0;

        if (sign != prevSign && prevSign != 0) {
            // End of monotonic region
            std::cout << "Monotonic region: " << startIdx << " to " << i - 1 << ", ";
            std::cout << (prevSign == 1 ? "Increasing" : "Decreasing") << std::endl;
            startIdx = i;
        }

        prevSign = sign;
    }

    // End of last monotonic region
    std::cout << "Monotonic region: " << startIdx << " to " << slopes.size() - 1 << ", ";
    std::cout << (prevSign == 1 ? "Increasing" : "Decreasing") << std::endl;

    return 0;
}
