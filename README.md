# Vector Assignment Project

A comprehensive project demonstrating native C++ DLL development, P/Invoke interop with Unity, and practical game development using custom vector mathematics.

## Project Overview

This project consists of three main components:

1. **VectorAssignment** - A native C++ dynamic link library (DLL) implementing 2D and 3D vector mathematics operations
2. **TestOperations** - Unit test suite for validating the vector math library
3. **Pong** - A Unity game implementation that uses the vector math DLL via P/Invoke to handle game physics

## Project Structure

```
VectorAssignment/
├── VectorAssignment/          # Native C++ DLL project
│   ├── Vec3.h                # Vector math header with all function declarations
│   └── Vec3.cpp              # Implementation file
├── TestOperations/           # Test suite project
│   └── Vec3Tests.cpp         # Unit tests for vector operations
├── Pong/                     # Unity game project
│   └── Assets/
│       └── Scripts/
│           ├── PongVector.cs      # P/Invoke wrapper for DLL functions
│           ├── BallController.cs  # Ball physics and collision handling
│           ├── PaddleController.cs # Player paddle input handling
│           ├── PaddleAI.cs        # AI-controlled paddle
│           └── GameManager.cs     # Game state and scoring
└── bin/                      # Build output directory
```

## Components

### 1. VectorAssignment DLL

A Windows DLL (`VectorAssignment.dll`) that exports vector math functions for both 2D and 3D operations.

#### Vec2 Operations (2D Vectors)
- `v2_add(Vec2 a, Vec2 b)` - Vector addition
- `v2_subtract(Vec2 a, Vec2 b)` - Vector subtraction
- `v2_scale(Vec2 v, float s)` - Scalar multiplication
- `v2_magnitude(Vec2 v)` - Calculate vector magnitude
- `v2_normalize(Vec2 v)` - Normalize vector to unit length
- `v2_dot(Vec2 a, Vec2 b)` - Dot product
- `v2_reflect(Vec2 v, Vec2 normal)` - Reflect vector off a normal
- `v2_lerp(Vec2 a, Vec2 b, float t)` - Linear interpolation

#### Vec3 Operations (3D Vectors)
- `v3_add(Vec3 a, Vec3 b)` - Vector addition
- `v3_subtract(Vec3 a, Vec3 b)` - Vector subtraction
- `v3_scale(Vec3 v, float s)` - Scalar multiplication
- `v3_magnitude(Vec3 v)` - Calculate vector magnitude
- `v3_normalize(Vec3 v)` - Normalize vector to unit length
- `v3_dot(Vec3 a, Vec3 b)` - Dot product
- `v3_cross(Vec3 a, Vec3 b)` - Cross product
- `v3_distance(Vec3 a, Vec3 b)` - Distance between two points
- `v3_distance_sqr(Vec3 a, Vec3 b)` - Squared distance (optimized)
- `v3_angle_between(Vec3 a, Vec3 b)` - Angle between two vectors
- `v3_clamp_magnitude(Vec3 v, float maxLength)` - Clamp vector magnitude
- `v3_project(Vec3 a, Vec3 b)` - Project vector onto another
- `v3_lerp(Vec3 a, Vec3 b, float t)` - Linear interpolation

#### Data Structures
```cpp
struct Vec2 {
    float x, y;
};

struct Vec3 {
    float x, y, z;
};
```

### 2. TestOperations

A console application that runs comprehensive unit tests for all vector operations. The test suite validates:
- Basic arithmetic operations (add, subtract, scale)
- Vector properties (magnitude, normalization)
- Advanced operations (dot product, cross product, reflection)
- Edge cases (zero vectors, normalization of zero vectors)
- Mathematical correctness

**Running Tests:**
```bash
# Build and run TestOperations.exe
# Output shows [PASS]/[FAIL] for each test and a summary
```

### 3. Pong Unity Game

A complete Pong game implementation that demonstrates practical use of the vector math DLL in a game context.

#### Scripts

**PongVector.cs**
- P/Invoke wrapper class that bridges C# and the native DLL
- Defines `Vec2` struct matching the C++ structure
- Declares all DLL imports using `[DllImport("VectorAssignment")]`

**BallController.cs**
- Manages ball physics and movement using vector operations
- Implements collision detection with walls and paddles
- Uses `v2_add`, `v2_scale`, `v2_reflect`, and `v2_normalize` for physics
- Handles ball reset and scoring logic

**PaddleController.cs**
- Handles player input (W/S for Player 1, Arrow keys for Player 2)
- Uses vector addition for smooth paddle movement
- Maintains paddle position using `Vec2` structure

**PaddleAI.cs**
- AI-controlled paddle that tracks the ball
- Uses vector operations to compute movement direction
- Implements boundary clamping

**GameManager.cs**
- Manages game state and scoring
- Tracks player scores (first to 5 wins)
- Handles game over state and restart functionality
- Updates UI using TextMeshPro

## Building the Project

### Prerequisites
- **Visual Studio 2022** (or compatible IDE) with C++ development tools
- **Unity 6000.3.8f1** or compatible version
- **Windows SDK 10.0**

### Building the DLL

1. Open `VectorAssignment.sln` in Visual Studio
2. Set configuration to **Release x64** (or Debug for development)
3. Build the solution
4. The DLL will be output to `bin/x64/Release/VectorAssignment.dll`

### Building the Tests

1. Ensure VectorAssignment project is built first
2. Build TestOperations project
3. Run `TestOperations.exe` from the output directory

### Setting Up Unity Project

1. Copy `VectorAssignment.dll` to `Pong/Assets/Plugins/` directory (create if needed)
2. Open the Unity project in Unity Editor
3. Ensure all scripts are assigned to appropriate GameObjects:
   - `GameManager` on a GameObject with UI Canvas
   - `BallController` on the Ball GameObject
   - `PaddleController` on player paddle GameObjects
   - `PaddleAI` on AI-controlled paddle GameObject

## Usage

### Using the DLL in C#

```csharp
using System.Runtime.InteropServices;

// Define the struct matching C++ Vec2
[StructLayout(LayoutKind.Sequential)]
public struct Vec2 {
    public float x;
    public float y;
}

// Import DLL functions
[DllImport("VectorAssignment")]
public static extern Vec2 v2_add(Vec2 a, Vec2 b);

// Use the functions
Vec2 a = new Vec2 { x = 1.0f, y = 2.0f };
Vec2 b = new Vec2 { x = 3.0f, y = 4.0f };
Vec2 result = v2_add(a, b); // { x = 4.0f, y = 6.0f }
```

### Playing the Game

1. Launch the Unity game
2. **Player 1 Controls:**
   - `W` - Move paddle up
   - `S` - Move paddle down
3. **Player 2 Controls:**
   - `↑` - Move paddle up
   - `↓` - Move paddle down
4. First player to score 5 points wins
5. Press `R` to restart after game over

## Technical Details

### P/Invoke Interop

The project demonstrates proper P/Invoke interop between C# and C++:
- Struct layout matching using `[StructLayout(LayoutKind.Sequential)]`
- DLL function declarations with `[DllImport]`
- Proper marshalling of value types (structs and primitives)

### Vector Math Implementation

The vector library uses standard mathematical formulas:
- **Magnitude**: `√(x² + y²)` for 2D, `√(x² + y² + z²)` for 3D
- **Normalization**: Divide each component by magnitude
- **Dot Product**: `a·b = ax*bx + ay*by` (2D) or `ax*bx + ay*by + az*bz` (3D)
- **Reflection**: `v - 2(v·n)n` where `n` is the normalized normal

### Game Physics

The Pong game implements:
- Continuous collision detection using AABB (Axis-Aligned Bounding Box)
- Angle-based ball reflection based on paddle hit position
- Velocity normalization to maintain constant speed
- Boundary checking for walls and scoring zones

## Dependencies

### Unity Packages
- Unity Input System (1.18.0)
- TextMeshPro (via Unity UGUI)
- Universal Render Pipeline (17.3.0)

### C++ Dependencies
- Standard C++ math library (`<math.h>`)
- Windows API for DLL export (`__declspec(dllexport)`)

## Platform Support

- **Windows x64** - Primary platform
- DLL exports use Windows calling convention
- Unity project configured for Windows builds

## Future Enhancements

Potential improvements:
- Add more vector operations (rotation, matrix transformations)
- Implement 3D game example using Vec3 operations
- Add SIMD optimizations for vector operations
- Cross-platform support (Linux, macOS)
- Add more comprehensive unit tests
- Performance benchmarking

## License

This project is provided as-is for educational and demonstration purposes.

## Author

Vector Assignment Project - Demonstrating native DLL development and Unity interop.
