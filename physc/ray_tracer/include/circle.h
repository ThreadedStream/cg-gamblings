#pragma once

#include <vector>

struct MidPointAlgorithm;

class Circle{
public:
    // not necessary, but really fancy
    using self = Circle;

    explicit Circle(int32_t x0, int32_t y0, int32_t rad) :
            x0_{x0}, y0_{y0}, rad_{rad} {};


    [[nodiscard]] inline const std::vector<SDL_Point>& getVertices() const { return points; };

    template<class Algorithm = MidPointAlgorithm>
    void generate(){
        Algorithm algo;
        algo.operator () (*this);
    };


protected:
    friend struct MidPointAlgorithm;
    int32_t x0_;
    int32_t y0_;
    int32_t rad_;

    //TODO(threadedstream): roll my own lightweight vector implementation?
    std::vector<SDL_Point> points;
};


struct MidPointAlgorithm{
    // https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
    void operator () (Circle& circle) {
        int32_t x0 = circle.x0_;
        int32_t y0 = circle.y0_;
        int32_t rad = circle.rad_;

        // allocate points
        int32_t x = rad, y = 0;
        circle.points.push_back({x + x0, y + y0});

        if (likely(rad > 0)) {
            circle.points.push_back({x + x0, -y + y0});
            circle.points.push_back({y + x0, x + y0});
            circle.points.push_back({-y + x0, x + y0});
        }

        int32_t P = 1 - rad;
        while (x > y) {
            y++;

            if (P <= 0){
                P = P + 2*y + 1;
            }else{
                x--;
                P = P + 2*y - 2 * x + 1;
            }

            if (x < y)
                break;

            circle.points.push_back({x + x0, y + y0});
            circle.points.push_back({-x + x0, y + y0});
            circle.points.push_back({x + x0, -y + y0});
            circle.points.push_back({-x + x0, -y + y0});

            if (x != y) {
                circle.points.push_back({y + x0, x + y0});
                circle.points.push_back({-y + x0, x + y0});
                circle.points.push_back({y + x0, -x + y0});
                circle.points.push_back({-y + x0, -x + y0});
            }
        }
    }
};



