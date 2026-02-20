#include <iostream>
#include <cmath>
#include "Vec3.h"  

#define EPSILON 0.0001f

static int testsRun = 0;
static int testsPassed = 0;

bool float_equal(float a, float b) 
{
    return fabs(a - b) < EPSILON;
}

bool vec2_equal(Vec2 a, Vec2 b) 
{
    return float_equal(a.x, b.x) && float_equal(a.y, b.y);
}

bool vec3_equal(Vec3 a, Vec3 b) 
{
    return float_equal(a.x, b.x) &&
        float_equal(a.y, b.y) &&
        float_equal(a.z, b.z);
}

void print_result(const char* name, bool result) 
{
    testsRun++;
    if (result) {
        testsPassed++;
        std::cout << "[PASS] " << name << "\n";
    }
    else {
        std::cout << "[FAIL] " << name << "\n";
    }
}

void test_vec2() {

    Vec2 a = { 2, 3 };
    Vec2 b = { 4, 5 };

    print_result("Vec2 Add", vec2_equal(v2_add(a, b), { 6, 8 }));

    print_result("Vec2 Subtract", vec2_equal(v2_subtract(b, a), { 2, 2 }));

    print_result("Vec2 Scale", vec2_equal(v2_scale(a, 2.0f), { 4, 6 }));

    print_result("Vec2 Dot", float_equal(v2_dot(a, b), 23.0f));

    print_result("Vec2 Magnitude", float_equal(v2_magnitude({ 3, 4 }), 5.0f));

    print_result("Vec2 Normalize", vec2_equal(v2_normalize({ 0, 0 }), { 0, 0 })); 

    print_result("Vec2 Lerp", vec2_equal(v2_lerp({ 0,0 }, { 10,10 }, 0.5f), { 5,5 }));

    print_result("Vec2 Reflect", vec2_equal(v2_reflect({ 1, -1 }, { 0, 1 }), { 1, 1 }));
}

void test_vec3() {

    Vec3 a = { 1, 2, 3 };
    Vec3 b = { 4, 5, 6 };

    print_result("Vec3 Add", vec3_equal(v3_add(a, b), { 5, 7, 9 }));

    print_result("Vec3 Subtract", vec3_equal(v3_subtract(b, a), { 3, 3, 3 }));

    print_result("Vec3 Scale", vec3_equal(v3_scale(a, 2.0f), { 2, 4, 6 }));

    print_result("Vec3 Dot", float_equal(v3_dot(a, b), 32.0f));

    print_result("Vec3 Cross", vec3_equal(v3_cross({ 1,0,0 }, { 0,1,0 }), { 0,0,1 }));

    print_result("Vec3 Magnitude", float_equal(v3_magnitude({ 0,0,5 }), 5.0f));

    print_result("Vec3 Normalize Zero Edge Case", vec3_equal(v3_normalize({ 0,0,0 }), { 0,0,0 }));

    print_result("Vec3 Distance", float_equal(v3_distance({ 0,0,0 }, { 0,3,4 }), 5.0f));

    print_result("Vec3 Clamp Magnitude", float_equal(v3_magnitude(v3_clamp_magnitude({ 10,0,0 }, 5.0f)), 5.0f));

    print_result("Vec3 Project", vec3_equal(v3_project({ 2,0,0 }, { 1,0,0 }),{ 2,0,0 }));
}

int main() {

    std::cout << "VECTOR MATH TESTS\n\n";

    test_vec2();
    test_vec3();

    std::cout << "\n===========================\n";
    std::cout << "Tests Run:    " << testsRun << "\n";
    std::cout << "Tests Passed: " << testsPassed << "\n";
    std::cout << "Tests Failed: " << (testsRun - testsPassed) << "\n";

    if (testsRun == testsPassed)
        std::cout << "\nALL TESTS PASSED\n";
    else
        std::cout << "\nSOME TESTS FAILED\n";

    return 0;
}