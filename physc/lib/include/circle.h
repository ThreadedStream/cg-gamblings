#pragma once

#include <vector>

struct Point{
    union{
        SDL_Point sdl_pt;
        b2Vec2 box2d_pt;
    };
};


class Circle{
public:
    struct MidPointAlgorithm{
        // https://www.geeksforgeeks.org/mid-point-circle-drawing-algorithm/
        SDL_Point* operator () (int32_t x0, int32_t y0, int32_t rad) {
            // allocate points
            std::vector<SDL_Point> points;
            int32_t x = rad, y = 0;
            points.push_back({x + x0, y + y0});

            if (rad > 0) {
                points.push_back({x + x0, -y + y0});
                points.push_back({y + x0, x + y0});
                points.push_back({-y + x0, x + y0});
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

                points.push_back({x + x0, y + y0});
                points.push_back({-x + x0, y + y0});
                points.push_back({x + x0, -y + y0});
                points.push_back({-x + x0, -y + y0});

                if (x != y) {
                    points.push_back({y + x0, x + y0});
                    points.push_back({-y + x0, x + y0});
                    points.push_back({y + x0, -x + y0});
                    points.push_back({-y + x0, -x + y0});
                }
            }

            return static_cast<SDL_Point*>(points.data());
        }
    };

    explicit Circle(int32_t x0, int32_t y0, int32_t rad) :
    x0_{x0}, y0_{y0}, rad_{rad} {};

    [[nodiscard]] inline const SDL_Point* getVertices() const { return Circle::circle_points.data(); };

    template<class Algorithm = MidPointAlgorithm>
    SDL_Point* generate(int32_t x0, int32_t y0, int32_t rad ) {
        Algorithm algo;
        return algo.operator () (x0, y0, rad);
    };

private:
    int32_t rad_;
    int32_t x0_;
    int32_t y0_;

    // change it?
    std::vector<SDL_Point> circle_points;
};

