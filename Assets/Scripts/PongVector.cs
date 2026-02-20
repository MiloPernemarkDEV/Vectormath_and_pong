using System.Runtime.InteropServices;

public static class PongVector
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec2
    {
        public float x;
        public float y;
    }

    [DllImport("VectorAssignment")]
    public static extern Vec2 v2_add(Vec2 a, Vec2 b);

    [DllImport("VectorAssignment")]
    public static extern Vec2 v2_subtract(Vec2 a, Vec2 b);

    [DllImport("VectorAssignment")]
    public static extern Vec2 v2_scale(Vec2 v, float s);

    [DllImport("VectorAssignment")]
    public static extern float v2_dot(Vec2 a, Vec2 b);

    [DllImport("VectorAssignment")]
    public static extern Vec2 v2_reflect(Vec2 v, Vec2 normal);

    [DllImport("VectorAssignment")]
    public static extern Vec2 v2_normalize(Vec2 v);

    [DllImport("VectorAssignment")]
    public static extern float v2_magnitude(Vec2 v);
}