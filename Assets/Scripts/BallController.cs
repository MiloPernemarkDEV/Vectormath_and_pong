using UnityEngine;

public class BallController : MonoBehaviour
{
    public float speed = 8f;
    public float radius = 0.25f; // ball radius
    public Transform paddle1; // assign left paddle
    public Transform paddle2; // assign right paddle
    public float maxBounceAngle = 75f; // degrees

    private PongVector.Vec2 position;
    private PongVector.Vec2 velocity;

    void Start()
    {
        ResetBall();
    }

    void Update()
    {
        // Move ball
        position = PongVector.v2_add(position,
            PongVector.v2_scale(velocity, Time.deltaTime));

        // Check collisions
        CheckWallCollision();
        CheckPaddleCollision(paddle1, true);
        CheckPaddleCollision(paddle2, false);

        // Update transform
        transform.position = new Vector3(position.x, position.y, 0);
    }

    void CheckWallCollision()
    {
        if (position.y + radius > 4.5f || position.y - radius < -4.5f)
        {
            PongVector.Vec2 normal;
            normal.x = 0;
            normal.y = position.y > 0 ? -1 : 1;

            velocity = PongVector.v2_reflect(velocity, normal);
        }

        if (position.x - radius > 9f)
        {
            GameManager.Instance.Player1Score();
            ResetBall();
        }
        else if (position.x + radius < -9f)
        {
            GameManager.Instance.Player2Score();
            ResetBall();
        }
    }

    void CheckPaddleCollision(Transform paddle, bool isLeft)
    {
        float paddleX = paddle.position.x;
        float paddleY = paddle.position.y;
        float paddleWidth = paddle.localScale.x;
        float paddleHeight = paddle.localScale.y;

        // Compute paddle edges
        float left = paddleX - paddleWidth / 2f;
        float right = paddleX + paddleWidth / 2f;
        float top = paddleY + paddleHeight / 2f;
        float bottom = paddleY - paddleHeight / 2f;

        // AABB collision check
        if (position.x + radius >= left && position.x - radius <= right &&
            position.y + radius >= bottom && position.y - radius <= top)
        {
            // Snap ball outside paddle
            if (isLeft)
                position.x = right + radius;
            else
                position.x = left - radius;

            // Compute hit factor (-1 at bottom, 0 center, 1 top)
            float hitFactor = (position.y - paddleY) / (paddleHeight / 2f);

            // Convert to radians
            float angle = hitFactor * maxBounceAngle * Mathf.Deg2Rad;

            // Determine new velocity
            float direction = isLeft ? 1f : -1f;
            velocity.x = Mathf.Cos(angle) * direction;
            velocity.y = Mathf.Sin(angle);

            // Normalize and scale
            velocity = PongVector.v2_normalize(velocity);
            velocity = PongVector.v2_scale(velocity, speed);
        }
    }

    void ResetBall()
    {
        position.x = 0;
        position.y = 0;

        velocity.x = Random.value > 0.5f ? 1 : -1;
        velocity.y = Random.Range(-0.5f, 0.5f);

        velocity = PongVector.v2_normalize(velocity);
        velocity = PongVector.v2_scale(velocity, speed);
    }
}