using UnityEngine;

public class PaddleAI : MonoBehaviour
{
    public Transform ball;           // assign Ball
    public float speed = 10f;        // AI paddle speed
    private PongVector.Vec2 position;
    private const float Y_LIMIT = 4.5f;

    void Awake()
    {
        position = new PongVector.Vec2
        {
            x = transform.position.x,
            y = transform.position.y
        };
    }

    void Update()
    {
        // Compute direction to move toward ball
        float direction = 0f;
        if (ball.position.y > transform.position.y + 0.1f)
            direction = 1f;
        else if (ball.position.y < transform.position.y - 0.1f)
            direction = -1f;

        // Compute movement
        PongVector.Vec2 move = new PongVector.Vec2
        {
            x = 0,
            y = direction * speed * Time.deltaTime
        };

        // Update position
        position = PongVector.v2_add(position, move);

        // Clamp
        if (position.y > Y_LIMIT) position.y = Y_LIMIT;
        if (position.y < -Y_LIMIT) position.y = -Y_LIMIT;

        // Apply to transform
        transform.position = new Vector3(position.x, position.y, 0f);
    }
}